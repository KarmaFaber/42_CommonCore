#include "ConfigException.hpp"

ConfigException::ConfigException(const std::string& message) throw()
	: _message("ConfigError: " + message) {}

const char* ConfigException::what() const throw()
{
	return (_message.c_str());
}

ConfigException::~ConfigException() throw() {}
