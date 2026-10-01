#pragma once
#include <string>
#include <ctime>
#include <netinet/in.h>
#include "NetworkMessage.hpp"

class Client
{
public:
    Client(int fd, const struct sockaddr_in &addr, short listenPort);
    ~Client();

    NetworkMessage *recv();

    void queueResponse(const std::string &data);
    bool shouldCloseAfterWrite() const;
    void setCloseAfterWrite(bool closeAfterWrite);

    bool send();

    bool hasDataToWrite() const;

    short getSockPort() const;
    std::string getIp() const;
    int getFd() const;
    time_t getConnectedAt() const;
    bool isFirstRequest() const;
    void markRequestSeen();
    void resetTimeout();

    class ClientException : public std::exception
    {
    public:
        explicit ClientException(const char *msg) : _msg(msg) {}
        const char *what() const throw() { return _msg; }

    private:
        const char *_msg;
    };

private:
    int _fd;
    struct sockaddr_in _addr;
    short _listenPort;
    time_t _connectedAt;
    std::string _readBuf;
    std::string _writeBuf;
    std::size_t _writeOffset;
    bool _closeAfterWrite;
    bool _firstRequest;

    bool _headersComplete() const;
    bool _requestComplete() const;
    std::size_t _getContentLength() const;
    bool _isChunked() const;

    Client(const Client &);
    Client &operator=(const Client &);

    static const std::size_t MAX_REQUEST_SIZE = 10 * 1024 * 1024;
    static const int READ_CHUNK = 4096;
};
