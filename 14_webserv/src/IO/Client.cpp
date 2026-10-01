#include "Client.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <cstdlib>
#include <cctype>

Client::Client(int fd, const struct sockaddr_in &addr, short listenPort)
    : _fd(fd), _addr(addr), _listenPort(listenPort),
      _connectedAt(std::time(NULL)), _writeOffset(0), _closeAfterWrite(false), _firstRequest(true) {}

Client::~Client()
{
    if (_fd >= 0)
        close(_fd);
}

int Client::getFd() const { return _fd; }
short Client::getSockPort() const { return _listenPort; }
time_t Client::getConnectedAt() const { return _connectedAt; }
bool Client::hasDataToWrite() const { return _writeOffset < _writeBuf.size(); }
bool Client::isFirstRequest() const { return _firstRequest; }
void Client::markRequestSeen() { _firstRequest = false; }

std::string Client::getIp() const
{
    return std::string(inet_ntoa(_addr.sin_addr));
}

bool Client::_headersComplete() const
{
    return _readBuf.find("\r\n\r\n") != std::string::npos;
}

std::size_t Client::_getContentLength() const
{
    std::size_t headerEnd = _readBuf.find("\r\n\r\n");
    if (headerEnd == std::string::npos)
        return 0;

    const std::string headers = _readBuf.substr(0, headerEnd);
    std::string lower;
    lower.reserve(headers.size());
    for (std::size_t i = 0; i < headers.size(); ++i)
        lower += static_cast<char>(std::tolower(static_cast<unsigned char>(headers[i])));

    std::size_t pos = lower.find("content-length:");
    if (pos == std::string::npos)
        return 0;

    pos += 15;
    while (pos < lower.size() && lower[pos] == ' ')
        ++pos;

    return static_cast<std::size_t>(std::atol(headers.c_str() + pos));
}

bool Client::_isChunked() const
{
    std::size_t headerEnd = _readBuf.find("\r\n\r\n");
    if (headerEnd == std::string::npos)
        return false;

    const std::string headers = _readBuf.substr(0, headerEnd);
    std::string lower;
    lower.reserve(headers.size());
    for (std::size_t i = 0; i < headers.size(); ++i)
        lower += static_cast<char>(std::tolower(static_cast<unsigned char>(headers[i])));

    return lower.find("\r\ntransfer-encoding: chunked\r\n") != std::string::npos;
}

bool Client::_requestComplete() const
{
    if (!_headersComplete())
        return false;

    std::size_t headerEnd = _readBuf.find("\r\n\r\n") + 4;

    if (_isChunked())
        return _readBuf.find("0\r\n\r\n", headerEnd) != std::string::npos;

    std::size_t contentLength = _getContentLength();
    std::size_t bodyReceived = _readBuf.size() - headerEnd;
    return bodyReceived >= contentLength;
}

NetworkMessage *Client::recv()
{
    char buf[READ_CHUNK];
    ssize_t n = ::recv(_fd, buf, sizeof(buf), 0);
    if (n < 0)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return NULL;
        if (errno == EINTR)
            return NULL;
        throw ClientException("recv() failed");
    }
    if (n == 0)
        throw ClientException("connection closed by client");

    _readBuf.append(buf, static_cast<std::size_t>(n));

    if (_readBuf.size() > MAX_REQUEST_SIZE) //todo this will trigger empty response against valid requests that are too big
        throw ClientException("request exceeds maximum allowed size");

    if (!_requestComplete())
        return NULL;

    NetworkMessage *msg = new NetworkMessage(_readBuf, *this);
    _readBuf.clear();
    return msg;
}

void Client::queueResponse(const std::string &data)
{
    _writeBuf = data;
    _writeOffset = 0;
}

bool Client::shouldCloseAfterWrite() const
{
    return _closeAfterWrite;
}

void Client::setCloseAfterWrite(bool closeAfterWrite)
{
    _closeAfterWrite = closeAfterWrite;
}

bool Client::send()
{
    const char *ptr = _writeBuf.c_str() + _writeOffset;
    std::size_t left = _writeBuf.size() - _writeOffset;

    ssize_t n = ::send(_fd, ptr, left, 0);

    if (n < 0)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
            return false;
        throw ClientException("send() failed");
    }
    _writeOffset += static_cast<std::size_t>(n);
    return _writeOffset >= _writeBuf.size();
}

void Client::resetTimeout()
{
    _connectedAt = std::time(NULL);
}
