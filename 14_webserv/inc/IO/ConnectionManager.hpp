#pragma once
#include <vector>
#include <poll.h>
#include "ConnectionSocket.hpp"
#include "Client.hpp"
#include "ConfigParser.hpp"
#include "SessionManager.hpp"

class ConnectionManager {
public:
    explicit ConnectionManager(const ConfigParser &config);
    ~ConnectionManager();

    void run(volatile bool &signalExit);

private:
    std::vector<ConnectionSocket *> _listenSockets;
    std::vector<Client *>           _clients;
    std::vector<struct pollfd>      _pfds;
    const ConfigParser             &_config;
    SessionManager            _session_mng;

    static const int TIMEOUT_SECS = 30;

    void _buildPollFds();
    void _acceptNewClients(std::size_t socketIdx);
    void _handleRead(std::size_t pfdIdx);
    void _handleWrite(std::size_t pfdIdx);
    void _removeClient(std::size_t pfdIdx);
    void _checkTimeouts();
    void _buildAndQueueResponse(Client *client, const std::string &rawRequest);

    static const ServerConfig &_getRequestConfig(const ConfigParser &config,
                                                  const Client &client);

    ConnectionManager(const ConnectionManager &);
    ConnectionManager &operator=(const ConnectionManager &);
};
