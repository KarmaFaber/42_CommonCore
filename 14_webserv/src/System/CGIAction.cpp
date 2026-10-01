#include "CGIAction.hpp"
#include <unistd.h>
#include <sys/wait.h>
#include <poll.h>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <cctype>
#include <signal.h>

class Action;

const std::string CGIAction::_gatewayInterface = "CGI/1.1";
const std::string CGIAction::_redirectStatus = "200";

static std::string toString(long n)
{
	std::ostringstream oss;

	oss << n;
	return (oss.str());
}

static std::string toEnvKey(const std::string &header)
{
	std::string key;
	size_t      i;

	key = "HTTP_";
	i = 0;
	while (i < header.size())
	{
		char c = header[i];
		if (c == '-')
			key += '_';
		else
			key += std::toupper(c);
		i++;
	}
	return (key);
}

void CGIAction::_buildEnv(const Request &req)
{
	const std::multimap<std::string, std::string> &reqHeaders = req.getHeaders();
	const ServerConfig *serverConf = req.getConfig();

	if (serverConf == NULL)
		throw HttpError(HTTP_SERVER_ERROR, "CGI: missing server config").withRequest(req);

	_env["GATEWAY_INTERFACE"] = _gatewayInterface;
	_env["SERVER_PROTOCOL"]   = Message::versionToString(_req->getVersion());
	_env["SERVER_SOFTWARE"]   = Response::webservName;
	_env["REQUEST_METHOD"]    = req.methodToString(req.getMethod());
	_env["REQUEST_URI"]       = _rawPath;
	_env["SCRIPT_FILENAME"]   = _targetPath;
	_env["SCRIPT_NAME"]       = _rawPath;
	_env["PATH_INFO"]         = _pathInfo;

	if (_pathInfo.length() > 0)
		_env["PATH_TRANSLATED"]   = pathConcatenate(serverConf->getRoot(), _pathInfo); //if no path_info, leave this env var unset

	_env["QUERY_STRING"]      = _queryString;
	_env["DOCUMENT_ROOT"]     = serverConf->getRoot();

	const std::vector<std::string> &names = serverConf->getServerNames();
	_env["SERVER_NAME"] = (names.empty()) ? "localhost" : names[0];

	_env["SERVER_PORT"]       = toString(serverConf->getPort());
	_env["REMOTE_ADDR"]       = "";
	_env["REDIRECT_STATUS"]   = _redirectStatus; //required by cgi standard

	if (_reqBody.length() > 0) {//only set if body is present
		_env["CONTENT_LENGTH"] = toString(static_cast<long>(_reqBody.size()));

		std::map<std::string, std::string>::const_iterator ct = reqHeaders.find("content-type");
		if (ct != reqHeaders.end())
			_env["CONTENT_TYPE"] = ct->second;
		else
			_env["CONTENT_TYPE"] = getFiletype(_targetPath); //if not set by request, try to guess
	}

	if (_location != NULL && !_location->getUploadPath().empty())
		_env["UPLOAD_DIR"] = _location->getUploadPath();
	else if (!serverConf->getUploadPath().empty())
		_env["UPLOAD_DIR"] = serverConf->getUploadPath();
	//leave unset otherwise

	if (_session != NULL) {
		_env["BONUS_SESSION"] = _session->getSessionId();
		_env["BONUS_USERNAME"] = _session->getUsername();
		_env["BONUS_EMAIL"] = _session->getEmail();
	}

	std::multimap<std::string, std::string>::const_iterator it = reqHeaders.begin();
	while (it != reqHeaders.end())
	{
		if (it->first != "content-type" && it->first != "content-length")
			_env[toEnvKey(it->first)] = it->second;
		++it;
	}
}

char **CGIAction::_envToArray() const
{
	std::map<std::string, std::string>::const_iterator it;
	char                                              **env;
	size_t                                              i;

	env = new char *[_env.size() + 1];
	i = 0;
	it = _env.begin();
	while (it != _env.end())
	{
		std::string entry = it->first + "=" + it->second;
		env[i] = new char[entry.size() + 1];
		std::strcpy(env[i], entry.c_str());
		++it;
		++i;
	}
	env[i] = NULL;
	return (env);
}

static void freeArray(char **arr)
{
    if (!arr) return;
    for (int i = 0; arr[i] != NULL; ++i)
        delete[] arr[i];
    delete[] arr;
}

static const std::string getQueryString(const std::string &path_leftover) {
	std::string::size_type it = path_leftover.find('?');
	if (it == std::string::npos)
		return "";
	return path_leftover.substr(it + 1);
}

static const std::string getPathInfo(const std::string &path_leftover) {
	std::string::size_type it = path_leftover.find('?');
	return path_leftover.substr(0, it);
}

CGIAction::CGIAction(const Request &req, const std::string &cgiPath,
	const std::string &path_leftover): Action(req), 
			_cgiPath(cgiPath), _pathInfo(getPathInfo(path_leftover)),
			_queryString(getQueryString(path_leftover)), _reqBody(req.getBody()),
			_method(req.getMethod()) {
	_buildEnv(req);
}

static void killProcess(pid_t pid, int pipefd) {
	kill(pid, SIGKILL);
	waitpid(pid, NULL, 0);
	close(pipefd);
}

static void _cgi_sendBody(pid_t pid, int stdin_pipe[2], int stdout_pipe[2], const std::string &body, const Request &req) {
	struct pollfd		wfd;
	wfd.fd = stdin_pipe[1];
	wfd.events = POLLOUT;

	size_t written = 0;
	while (written < body.size()) {
		int ret = poll(&wfd, 1, CGIPOLLTIMEOUT);
		if (ret < 0) {
			killProcess(pid, stdout_pipe[0]);
			close(stdin_pipe[1]);
			throw HttpError(HTTP_SERVER_ERROR, "CGI: poll() failed writing stdin").withRequest(req);
		}
		if (ret == 0) {
			killProcess(pid, stdout_pipe[0]);
			close(stdin_pipe[1]);
			throw HttpError(HTTP_SERVER_ERROR, "CGI: timed out writing request body").withRequest(req);
		}
		if (wfd.revents & (POLLERR | POLLNVAL)) {
			killProcess(pid, stdout_pipe[0]);
			close(stdin_pipe[1]);
			throw HttpError(HTTP_SERVER_ERROR, "CGI: poll() failed writing to stdin").withRequest(req);
		}
		if (wfd.revents & POLLHUP) {
			killProcess(pid, stdout_pipe[0]);
			close(stdin_pipe[1]);
			throw HttpError(HTTP_SERVER_ERROR, "CGI: stdin pipe closed prematurely").withRequest(req);
		}
		if (wfd.revents & POLLOUT) {
			ssize_t n = write(stdin_pipe[1], body.c_str() + written, body.size() - written);
			if (n < 0) {
				killProcess(pid, stdout_pipe[0]);
				close(stdin_pipe[1]);
				throw HttpError(HTTP_SERVER_ERROR, "CGI: write error:\t" + std::string(strerror(errno))).withRequest(req);
			}
			written += static_cast<size_t>(n);
		}
	}
}

std::string CGIAction::_cgi_execute()
{ //todo hace falta hardening a nivel de php-cgi, principalmente deshabilitar acceso a carpetas no permitidas y a comandos peligrosos
	std::string			output;
	char				buffer[8196];
	ssize_t				n;
	int					stdin_pipe[2];
	int					stdout_pipe[2];
	int					wstatus;
	pid_t				pid;

	if (access(_cgiPath.c_str(), X_OK) != 0)
		throw HttpError(HTTP_SERVER_ERROR, "CGI: executable not reachable").withRequest(*_req);

	if (pipe(stdin_pipe) < 0)
		throw HttpError(HTTP_SERVER_ERROR, "CGI: pipe() failed for stdin").withRequest(*_req);
	if (pipe(stdout_pipe) < 0)
	{
		close(stdin_pipe[0]);
		close(stdin_pipe[1]);
		throw HttpError(HTTP_SERVER_ERROR, "CGI: pipe() failed for stdout").withRequest(*_req);
	}

	pid = fork();
	if (pid < 0)
	{
		close(stdin_pipe[0]);
		close(stdin_pipe[1]);
		close(stdout_pipe[0]);
		close(stdout_pipe[1]);
		throw HttpError(HTTP_SERVER_ERROR, "CGI: fork() failed").withRequest(*_req);
	}

	if (pid == 0)
	{
		close(stdin_pipe[1]);
		close(stdout_pipe[0]);

		if (dup2(stdin_pipe[0], STDIN_FILENO) < 0)
			exit(1);
		if (dup2(stdout_pipe[1], STDOUT_FILENO) < 0)
			exit(1);

		close(stdin_pipe[0]);
		close(stdout_pipe[1]);

		//argv = _buildArgv();
		char *argv[3];
		argv[0] = strdup(_cgiPath.c_str());
		argv[1] = strdup(_targetPath.c_str());
		argv[2] = NULL;
		char **env  = _envToArray();

		execve(_cgiPath.c_str(), argv, env);

		//only reach here in case of error
		freeArray(argv);
		freeArray(env);
		exit(1);
	}

	close(stdin_pipe[0]);
	close(stdout_pipe[1]);

	if (!_reqBody.empty()) //write body to cgi stdin
		_cgi_sendBody(pid, stdin_pipe, stdout_pipe, _reqBody, *_req);
	close(stdin_pipe[1]);

	struct pollfd		rfd;
	rfd.fd = stdout_pipe[0];
	rfd.events = POLLIN;
	bool done = false;
	time_t startTime = time(NULL);
	while (!done)
	{
		if (time(NULL) - startTime > CGITOTALTIMEOUT) {
			killProcess(pid, stdout_pipe[0]);
			throw HttpError(HTTP_SERVER_ERROR, "CGI: CGI process timeout").withRequest(*_req);
		}

		int ret = poll(&rfd, 1, CGIPOLLTIMEOUT);
		if (ret < 0)
		{
			killProcess(pid, stdout_pipe[0]);
			throw HttpError(HTTP_SERVER_ERROR, "CGI: poll() failed reading stdout").withRequest(*_req);
		}
		if (ret == 0)
		{
			killProcess(pid, stdout_pipe[0]);
			throw HttpError(HTTP_SERVER_ERROR, "CGI: script timed out").withRequest(*_req);
		}
		if (rfd.events & (POLLERR | POLLNVAL)) {
			killProcess(pid, stdout_pipe[0]);
			throw HttpError(HTTP_SERVER_ERROR, "CGI: poll() failed reading stdout").withRequest(*_req);
		}
		if (rfd.revents & (POLLIN | POLLHUP))
		{
			n = read(stdout_pipe[0], buffer, sizeof(buffer));
			if (n > 0) {
				output.append(buffer, static_cast<size_t>(n));
				if (output.size() > _cgiMaxResponseSize) {
					killProcess(pid, stdout_pipe[0]);
					throw HttpError(HTTP_SERVER_ERROR, "CGI: response body overflow").withRequest(*_req);
				}
			}
			else
				done = true;
		}
		else
			done = true;
	}
	close(stdout_pipe[0]);

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 0)
		throw HttpError(HTTP_SERVER_ERROR, "CGI: script exited with non-zero status").withRequest(*_req);

	return output;
}

Response CGIAction::exec() {
    struct stat filestat;
    if (stat(_targetPath.c_str(), &filestat) != 0)
        throw HttpError(HTTP_NOTFOUND, "Resource " + _rawPath + " not found").withRequest(*_req); //use raw path from the request in response to not reveal internal data
    
    if (S_ISDIR(filestat.st_mode)) //target is a directory
        throw HttpError(HTTP_NOTFOUND, "Resource " + _rawPath + " not found").withRequest(*_req); //using a folder in cgi does not make sense

    if (access(_targetPath.c_str(), X_OK) != 0)
		throw HttpError(HTTP_FORBIDDEN, "Resource " + _rawPath + " not executable").withRequest(*_req);

	Response resp(_cgi_execute());
	resp.setVersion(_req->getVersion());
    resp.setKeepAlive(_req->getKeepAlive());
	return resp;
}
