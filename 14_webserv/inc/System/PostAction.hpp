#pragma once

#include <vector>
#include "Action.hpp"

class PostAction: public Action {
	private:
        const std::string _body;
		Response _createFile(const bool isNewFile);

    public:
        PostAction(const Request &req): Action(req), _body(req.getBody()) {};
        Response exec(void);
};
