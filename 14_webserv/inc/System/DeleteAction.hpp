#pragma once

#include "Action.hpp"

class DeleteAction: public Action {
	private:

    public:
        DeleteAction(const Request &req): Action(req) {};
        Response exec(void);
};
