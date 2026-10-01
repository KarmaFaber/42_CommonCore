#include "ConnectionSocket.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

ConnectionSocket::ConnectionSocket(short port) : _fd(-1), _port(port) {
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_fd < 0)
        throw ConnectionSocketException("socket() failed");

    int opt = 1;
    setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    fcntl(_fd, F_SETFL, O_NONBLOCK);

    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(port);

    if (bind(_fd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) < 0)
        throw ConnectionSocketException("bind() failed");

    if (listen(_fd, 128) < 0)
        throw ConnectionSocketException("listen() failed");
}

ConnectionSocket::~ConnectionSocket() {
    if (_fd >= 0)
        close(_fd);
}

int   ConnectionSocket::getFd()   const { return _fd; }
short ConnectionSocket::getPort() const { return _port; }

Client *ConnectionSocket::acceptConnection() {
    struct sockaddr_in addr;
    socklen_t          len = sizeof(addr);

    int clientFd = accept(_fd, reinterpret_cast<struct sockaddr *>(&addr), &len);
    if (clientFd < 0)
        return NULL;

    fcntl(clientFd, F_SETFL, O_NONBLOCK);
    return new Client(clientFd, addr, _port);
}
