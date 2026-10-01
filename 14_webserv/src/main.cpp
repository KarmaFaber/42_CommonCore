#include <iostream>
#include <cstring>
#include <signal.h>
#include <memory>
#include "ConfigParser.hpp"
#include "ConnectionManager.hpp"

volatile bool signalExit = false;

void mainExit(int)
{
	signalExit = true;
}

int main(int argc, const char *argv[])
{
	std::string configPath;
	if (argc != 2) {
		if (argc > 2) {
			std::cerr << "Usage: webserv <path/to/file.conf>" << std::endl;
			return 1;
		}
		configPath = "./Config/default.conf";
	} else {
		configPath = argv[1];
	}

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = mainExit;
	sigfillset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	std::auto_ptr<ConfigParser> config;

	try {
		config.reset(new ConfigParser(configPath));
		ConnectionManager manager(*config);
		manager.run(signalExit);
	}
	catch (const ConfigException &e) {
		std::cerr << "Error while trying to read config: " << e.what() << std::endl;
		return 1;
	} 
	catch (const ConnectionSocket::ConnectionSocketException &e) {
		std::cerr << "Fatal socket error: " << e.what() << std::endl;
		return 1;
	} 
	catch (const std::exception &e) {
		std::cerr << "Fatal error: " << e.what() << std::endl;
		return 1;
	} 
	catch (...) {
		std::cerr << "UNKNOWN: Uncaught exception of unknown type." << std::endl;
		return 1;
	}
	return 0;
}
