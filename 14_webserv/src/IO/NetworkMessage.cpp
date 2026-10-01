#include "NetworkMessage.hpp"

NetworkMessage::NetworkMessage(const std::string &msg, const Client &client)
    : _msg(msg), _client(client) {}

const std::string &NetworkMessage::getMsg() const { return _msg; }
const Client      &NetworkMessage::getClient() const { return _client; }
