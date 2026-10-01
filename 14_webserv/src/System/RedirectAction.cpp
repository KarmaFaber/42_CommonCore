#include "RedirectAction.hpp"

class Action;

//const HTTPStatus RedirectAction::_redir_status = HTTP_REDIRECTION;

RedirectAction::RedirectAction(const std::pair<short, std::string> pair, HttpVersion ver, bool keepAlive): _status(static_cast<HTTPStatus>(pair.first)), _location_hdr(pair.second), _version(ver), _keepAlive(keepAlive) {
}

Response RedirectAction::exec() {
	Response resp(_status);
	resp.addHeader("Location", _location_hdr);
	resp.addHeader("Content-Length", "0");
	resp.setVersion(_version);
	resp.setKeepAlive(_keepAlive);
	return resp;
}
