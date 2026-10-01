#pragma once

/* Defines */
#define CR "\r"
#define LF "\n"
#define CRLF "\r\n"
#define CRED   "\033[0;31m"
#define CGREEN "\033[0;32m"
#define CRESET "\033[0m"

#include <string>
#include <iostream>
#include <ctime>
#include "../../inc/Parser/Response.hpp"

class Logger
{
	private:
		Logger();
		Logger(const Logger&);
		Logger& operator=(const Logger&);
		~Logger();

	public:
		static void printStartupMessage(const std::string& host, int port);
		static std::string getLogDate();
		static void printAccessLog(const std::string& clientIp, const std::string& port, const std::string& method, const std::string& path, const std::string& httpVersion, int statusCode);
		static void printAccessLogErr(const std::string& clientIp, const std::string& port, int statusCode, const std::string& rawMsg);
		static void printConnectionLog(const std::string& clientIp, const std::string& port);
		static void printTimeoutLog(const std::string &ip, const std::string &port);
};
