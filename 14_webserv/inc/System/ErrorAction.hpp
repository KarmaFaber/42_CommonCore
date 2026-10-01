#pragma once

#include "Action.hpp"
#include <sstream>
#include <fstream>
#include <sys/stat.h>

class ErrorAction: public Action {
	private:
        std::string _findErrorPagePath(int status, std::string &outRoot) const;
        const HTTPStatus _status;
        const std::string _statusMessage;
        const HttpVersion _version;
        const bool _keep_alive;

    public:
        ErrorAction(const HttpError &err);
        Response exec(void);
};
