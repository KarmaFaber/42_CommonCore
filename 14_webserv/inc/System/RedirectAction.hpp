#pragma once

#include "Action.hpp"

class RedirectAction: public Action {
	private:
        const HTTPStatus _status;
        const std::string _location_hdr;
		const HttpVersion _version;
		const bool _keepAlive;

    public:
        RedirectAction(const std::pair<short, std::string> pair, HttpVersion ver, bool keepAlive);
        Response exec(void);
};
