#pragma once

#include <dirent.h>
#include "Action.hpp"

class GetAction: public Action {
	private:
        Response _generateAutoIndex();
        const std::string _getIndexPath() const;

    public:
        GetAction(const Request &req): Action(req) {};
        Response exec(void);
};
