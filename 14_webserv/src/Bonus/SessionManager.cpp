#include "SessionManager.hpp"
#include <sstream>

std::string SessionManager::_generateSessionId() {
    std::stringstream ss;

    ss << std::hex
        << std::time(NULL)
        << std::rand()
        << _counter++;

    std::string sessionId = ss.str();
    while (_sessions.find(sessionId) != _sessions.end()) {
        ss.str(""); //flush output
        ss.sync();
        ss << std::hex
            << std::time(NULL)
            << std::rand()
            << _counter++;

        std::string sessionId = ss.str();
    }

    return sessionId;
}

std::string SessionManager::registerSession(Session session) {
    std::string id = _generateSessionId();
    session.setSessionId(id);
    _sessions.insert(std::make_pair(id, session)); //could add session expiry date as well

    if (_sessions.size() > _maxSessionCount) { //delete oldest session
        time_t oldestTime = session.getCreatedAt();
        std::string oldestSession = session.getSessionId();
        for (std::map<std::string, Session>::const_iterator it = _sessions.begin(); it != _sessions.end(); it++) {
            if (it->second.getCreatedAt() < oldestTime) {
                oldestTime = it->second.getCreatedAt();
                oldestSession = it->first;
            }
        }
        _sessions.erase(oldestSession);
    }
    return id;
}

Session *SessionManager::getSession(std::string id) {
    std::map<std::string, Session>::iterator it = _sessions.find(id);
    if (it == _sessions.end())
        return NULL;
    return &(it->second);
}

bool SessionManager::deleteSession(std::string id) {
    std::map<std::string, Session>::iterator it = _sessions.find(id);
    if (it == _sessions.end())
        return false;
    _sessions.erase(it);
    return true;
}
