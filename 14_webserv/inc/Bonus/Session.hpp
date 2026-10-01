#pragma once
#include <string>

class Session {
    private:
        std::string _session_id;
        const std::string _username;
        const std::string _email;
        const time_t _createdAt;
    
    public:
        Session(const std::string &username, const std::string &email): _username(username), _email(email), _createdAt(time(NULL)) {};

        void setSessionId(const std::string &id) {_session_id = id;};
        const std::string &getSessionId() const {return _session_id;};
        const std::string &getUsername() const {return _username;};
        const std::string &getEmail() const {return _email;};
        const time_t &getCreatedAt() const {return _createdAt;};
};
