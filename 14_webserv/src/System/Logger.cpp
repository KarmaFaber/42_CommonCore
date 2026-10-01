#include "../../inc/System/Logger.hpp"

Logger::Logger() {}

Logger::Logger(const Logger& other) {
	(void)other;
}

Logger& Logger::operator=(const Logger& other) {
	(void)other;
	return *this;
}

Logger::~Logger() {}

void Logger::printStartupMessage(const std::string& host, int port)
{
	std::string ip = (host == "0.0.0.0" || host.empty()) ? "127.0.0.1" : host;

	std::cout << "\n=======================================================" << std::endl;
	std::cout << "[" << getLogDate() << "] [notice] " << Response::webservName << " started successfully" << std::endl;
	std::cout << "[" << getLogDate() << "] [notice] Listening on http://" << host << ":" << port << std::endl;
	std::cout << "[" << getLogDate() << "] [notice] Local access: http://" << ip << ":" << port << "/" << std::endl;
	std::cout << "=======================================================\n" << std::endl;
}

std::string Logger::getLogDate()
{
	char buf[64];
	std::time_t t = std::time(NULL);
	std::tm *now = std::localtime(&t);
	std::strftime(buf, sizeof(buf), "%d/%b/%Y %H:%M:%S", now);
	return std::string(buf);
}

void Logger::printAccessLog(const std::string& clientIp, const std::string& port, const std::string& method, const std::string& path, const std::string& httpVersion, int statusCode)
{
	// Imprime: IP:PORT - - [Fecha] "GET /ruta HTTP/1.x" 200 -
	std::cout << clientIp << ":" << port << " - - [" << getLogDate() << "] "
			  << "\"" << method << " " << path << " " << httpVersion << "\" "
			  << statusCode << " -" << std::endl;
}


void Logger::printAccessLogErr(const std::string& clientIp, const std::string& port, int statusCode, const std::string& rawMsg)
{
    std::string reqLine = rawMsg.substr(0, rawMsg.find("\r\n"));
    if (reqLine.empty()) {
        reqLine = "-";
    }

    std::cout << clientIp << ":" << port << " - - [" << getLogDate() << "] "
              << "\"" << reqLine << "\" "
              << statusCode << " -" << std::endl;
}
void Logger::printConnectionLog(const std::string& clientIp, const std::string& port)
{
	std::cout << CGREEN << clientIp << ":" << port << " - - [" << getLogDate() << "] CONNECTED"<< CRESET << std::endl;
}

void Logger::printTimeoutLog(const std::string &ip, const std::string &port) {
    std::cout << CRED << ip << ":" << port
              << " - - [" << getLogDate() << "] TIMED OUT" << CRESET << std::endl;
}
