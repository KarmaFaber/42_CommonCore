#pragma once
#include <stdexcept>
#include "Client.hpp"

class ConnectionSocket {
public:
    explicit ConnectionSocket(short port);
    ~ConnectionSocket();

    Client *acceptConnection();

    int   getFd()   const;
    short getPort() const;

    class ConnectionSocketException : public std::exception {
    public:
        explicit ConnectionSocketException(const char *msg) : _msg(msg) {}
        const char *what() const throw() { return _msg; }
    private:
        const char *_msg;
    };

private:
    int   _fd;
    short _port;

    ConnectionSocket(const ConnectionSocket &);
    ConnectionSocket &operator=(const ConnectionSocket &);
};
