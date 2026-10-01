#pragma once
#include <string>
#include <map>
#include <ctime>
#include <cstdlib>
#include "Session.hpp"

class SessionManager {
    private:
        static const int _maxSessionCount = 1000; //maximum number of active sessions
        std::map<std::string, Session> _sessions;
        unsigned long _counter;

        std::string _generateSessionId(void);
    
    public:
        SessionManager(void): _counter(0) {std::srand(std::time(NULL));}
        std::string registerSession(Session session);
        Session *getSession(std::string id);
        bool deleteSession(std::string id);
};
