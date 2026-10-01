#pragma once
#include <string>

class Client;

class NetworkMessage {
public:
    NetworkMessage(const std::string &msg, const Client &client);

    const std::string &getMsg() const;
    const Client      &getClient() const;

private:
    std::string   _msg;
    const Client &_client;
};
