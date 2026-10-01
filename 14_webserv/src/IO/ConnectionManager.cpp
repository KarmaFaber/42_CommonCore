#include "ConnectionManager.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Action.hpp"
#include "ErrorAction.hpp"
#include "HttpError.hpp"
#include "Logger.hpp"
#include <memory>
#include <poll.h>
#include <iostream>
#include <sstream>
#include <ctime>

static std::string intToString(int n) {
    std::ostringstream oss;
    oss << n;
    return oss.str();
}

ConnectionManager::ConnectionManager(const ConfigParser &config) : _config(config) {
    const std::vector<ServerConfig> &servers = config.getServers();

    for (std::size_t i = 0; i < servers.size(); ++i) {
        short port = static_cast<short>(servers[i].getPort());

        bool alreadyBound = false;
        for (std::size_t j = 0; j < _listenSockets.size(); ++j) {
            if (_listenSockets[j]->getPort() == port) {
                alreadyBound = true;
                break;
            }
        }
        if (alreadyBound)
            continue;

        _listenSockets.push_back(new ConnectionSocket(port));
        Logger::printStartupMessage(servers[i].getHost(), port);
    }

    _buildPollFds();
}

ConnectionManager::~ConnectionManager() {
    for (std::size_t i = 0; i < _clients.size(); ++i)
        delete _clients[i];
    for (std::size_t i = 0; i < _listenSockets.size(); ++i)
        delete _listenSockets[i];
}

void ConnectionManager::_buildPollFds() {
    _pfds.clear();

    for (std::size_t i = 0; i < _listenSockets.size(); ++i) {
        struct pollfd pfd;
        pfd.fd      = _listenSockets[i]->getFd();
        pfd.events  = POLLIN;
        pfd.revents = 0;
        _pfds.push_back(pfd);
    }

    for (std::size_t i = 0; i < _clients.size(); ++i) {
        struct pollfd pfd;
        pfd.fd      = _clients[i]->getFd();
        pfd.events  = POLLIN;
        pfd.revents = 0;
        _pfds.push_back(pfd);
    }
}

void ConnectionManager::run(volatile bool &signalExit) {
    const std::size_t nListeners = _listenSockets.size();

    while (!signalExit) {
        int ret = poll(&_pfds[0], static_cast<nfds_t>(_pfds.size()), 200);

        if (ret < 0) {
            if (signalExit)
                break;
            std::cerr << "poll() error" << std::endl;
            continue;
        }

        _checkTimeouts();

        if (ret == 0)
            continue;

        for (std::size_t i = 0; i < nListeners; ++i) {
            if (_pfds[i].revents & POLLIN)
                _acceptNewClients(i);
        }

        for (std::size_t i = _pfds.size(); i-- > nListeners;) {
            const short rev = _pfds[i].revents;

            if (rev & (POLLHUP | POLLERR)) {
                _removeClient(i);
                continue;
            }
            if (rev & POLLOUT)
                _handleWrite(i);
            if (i < _pfds.size() && (_pfds[i].revents & POLLIN))
                _handleRead(i);
        }
    }

    std::cout << "\nKeyboard interrupt received, exiting." << std::endl;
}

void ConnectionManager::_acceptNewClients(std::size_t socketIdx) {
    while (true) {
        Client *client = _listenSockets[socketIdx]->acceptConnection();
        if (client == NULL)
            break;

        _clients.push_back(client);

        struct pollfd pfd;
        pfd.fd      = client->getFd();
        pfd.events  = POLLIN;
        pfd.revents = 0;
        _pfds.push_back(pfd);
    }
}

void ConnectionManager::_handleRead(std::size_t pfdIdx) {
    std::size_t clientIdx = pfdIdx - _listenSockets.size();
    Client     *client    = _clients[clientIdx];

    NetworkMessage *msg = NULL;
    try {
        msg = client->recv();
    }
    catch (const Client::ClientException &) {
        _removeClient(pfdIdx);
        return;
    }

    if (msg == NULL)
        return;
    //client->getFd

    if (client->isFirstRequest()) {
        Logger::printConnectionLog(client->getIp(), intToString(client->getSockPort()));
        client->markRequestSeen();
    }

    _buildAndQueueResponse(client, msg->getMsg());
    delete msg;

    _pfds[pfdIdx].events = POLLOUT;
}

void ConnectionManager::_handleWrite(std::size_t pfdIdx) {
    std::size_t clientIdx = pfdIdx - _listenSockets.size();
    Client     *client    = _clients[clientIdx];

    bool done = false;
    try {
        done = client->send();
    }
    catch (const Client::ClientException &) {
        _removeClient(pfdIdx);
        return;
    }

    if (!done)
        return;

    if (client->shouldCloseAfterWrite()) {
        _removeClient(pfdIdx);
    } else {
        _pfds[pfdIdx].events = POLLIN;
        client->resetTimeout();
    }
}

void ConnectionManager::_buildAndQueueResponse(Client *client, const std::string &rawRequest) {
    std::string respStr;
    std::string clientIp = client->getIp();

    bool keepAlive = true;
    try {
        Request req(rawRequest, *client);

        req.verifyConfig(this->_config);
        req.parseBody(rawRequest);

        req.verifySession(_session_mng);
        
        std::auto_ptr<Action> act(buildAction(req));
        Response resp = act->exec();
        resp.verifySession(_session_mng);
        respStr = resp.toString();
        keepAlive = resp.getKeepAlive();

        Logger::printAccessLog(clientIp, intToString(client->getSockPort()), 
            Request::methodToString(req.getMethod()), req.getPath(), Message::versionToString(req.getVersion()), 
            static_cast<int>(resp.getStatus()));
    }
    catch (const HttpError &e) {
        ErrorAction eAct(e);
        Response resp = eAct.exec();
        respStr = resp.toString();
        keepAlive = resp.getKeepAlive();
        //Logger::printAccessLogErr(clientIp, e.getStatus(), rawRequest);
        Logger::printAccessLogErr(clientIp, intToString(client->getSockPort()), e.getStatus(), rawRequest);
    }
    catch (const std::exception &e) {
        std::cerr << "CRITICAL: " << e.what() << std::endl;
        respStr = "HTTP/1.0 500 Internal Server Error\r\nConnection: close\r\n\r\n";
        keepAlive = false;
    }
    catch (...) {
        std::cerr << "UNKNOWN: uncaught exception" << std::endl;
        respStr = "HTTP/1.0 500 Internal Server Error\r\nConnection: close\r\n\r\n";
        keepAlive = false;
    }

    client->queueResponse(respStr);
    client->setCloseAfterWrite(!keepAlive);
}

void ConnectionManager::_checkTimeouts() {
    time_t now = std::time(NULL);
    std::size_t nListeners = _listenSockets.size();

    for (std::size_t i = _pfds.size(); i-- > nListeners;) {
        std::size_t clientIdx = i - nListeners;
        if (now - _clients[clientIdx]->getConnectedAt() > TIMEOUT_SECS) {
            Logger::printTimeoutLog(
                _clients[clientIdx]->getIp(),
                intToString(_clients[clientIdx]->getSockPort())
            );
            _removeClient(i);
        }
    }
}

void ConnectionManager::_removeClient(std::size_t pfdIdx) {
    std::size_t clientIdx = pfdIdx - _listenSockets.size();

    delete _clients[clientIdx];

    _clients[clientIdx] = _clients.back();
    _clients.pop_back();

    _pfds[pfdIdx] = _pfds.back();
    _pfds.pop_back();
}

const ServerConfig &ConnectionManager::_getRequestConfig(const ConfigParser &config,
                                                          const Client &client) {
    const std::vector<ServerConfig> &servers = config.getServers();
    short reqPort = client.getSockPort();

    for (std::size_t i = 0; i < servers.size(); ++i) {
        if (static_cast<short>(servers[i].getPort()) == reqPort)
            return servers[i];
    }
    return servers[0];
}
