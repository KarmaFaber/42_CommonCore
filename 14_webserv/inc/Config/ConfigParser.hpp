#pragma once

#include "ServerConfig.hpp"
#include "LocationConfig.hpp"
#include "ConfigValidatorData.hpp"
#include "ConfigException.hpp"
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cerrno>
#include <cstdlib>
#include <limits>

class ConfigParser
{
	private:
		std::string							_configFilePath;
		std::string							_file_content;
		std::vector<ServerConfig>			_servers;
		size_t								_nb_server;
		bool 								_server_data;

		//initDirectiveMap.cpp
		typedef void	(ConfigParser::*ServerParserFunc)(ServerConfig&, std::string::iterator&);
		std::map<std::string, ServerParserFunc>	_serverDirectives;
		void			initServerMap();

		//ConfigParserWrapper.cpp 
		void						parseServerNameWrapper(ServerConfig& conf, std::string::iterator& it);
		void						parseIndexWrapper(ServerConfig& conf, std::string::iterator& it);
		void						parseUploadWrapper(ServerConfig& conf, std::string::iterator& it);
		void						parseReturnWrapper(ServerConfig& conf, std::string::iterator& it);
		void						parseAutoindexWrapper(ServerConfig& conf, std::string::iterator& it);
		void						parseRootWrapper(ServerConfig& config, std::string::iterator& it);
		void						parseAllowedMethodsWrapper(ServerConfig& config, std::string::iterator& it);

		//parsersUtils.cpp
		void						skipWhitespaceAndComments(std::string::iterator& it);

		//parsersUtilsStr.cpp
		std::string					getNextToken(std::string::iterator& it);

		//parsersUtilsVector.cpp
		std::vector<std::string>	getMultiToken(std::string::iterator& it);
		bool						isKeyword(const std::string& word);
		bool						isValidDomainChar(char c);
		bool						isValidPathChar(char c);

		//parserListen.cpp
		void						parseListen(ServerConfig& currentServer, std::string::iterator& it);
		void						parsePort(std::string token, ServerConfig& currentServer);
		void						parseHost(std::string token, ServerConfig& currentServer);
		void						validateOctet(std::stringstream& stream_str_var, std::string& octet_var, int& count_var);
		void						splitHostPort(std::string token, ServerConfig& currentServer);

		//parseVectorDirective.cpp
		typedef void				(ServerConfig::*SetterFunc)(const std::string&);
		void						parseVectorDirective(ServerConfig& conf, std::string::iterator& it, SetterFunc setter, std::string directiveName);

		//parserBodySize.cpp
		char						extractSuffix(const std::string& token, std::string& num_part);
		size_t						getMultiplier(char suffix);
		bool						isValidSuffix(char c);

		//parserErrorPage.cpp
		void						parseErrorPage(ServerConfig& currentServer, std::string::iterator& it);
		void						checkUri(std::string uri);

		// --- TEMPLATES ---
		template <typename T>
		void parseAutoindex(T& config, std::string::iterator& it);

		template <typename T>
		void parseReturn(T& config, std::string::iterator& it);

		template <typename T>
		void parseBodySize(T& config, std::string::iterator& it);

		template <typename T>
		void parseBodySizeValue(T& config, std::string token);

		template <typename T>
		void parseRoot(T& config, std::string::iterator& it);

		template <typename T>
		void parseAllowedMethods(T& config, std::string::iterator& it);

	public:
		ConfigParser(const std::string& path);
		~ConfigParser();

		//getters
		const std::vector<ServerConfig>&	getServers(void) const;
		size_t								getServNum (void) const;
		std::string							getFileContent(void) const;

		//parserMainMethods.cpp
		void								parseConfigFile(const std::string& path);
		void								parseFileContentVar(void);
		void								parseServerBlock(std::string::iterator& it);
		void								finalizeConfig(void);
		
		//parserLocation.cpp
		void								parseLocationBlock(ServerConfig& currentServer, std::string::iterator& it);
		void								parseLocationPath(LocationConfig& loc, std::string::iterator& it);
		void								parseLocationBody(LocationConfig& loc, std::string::iterator& it);
		void								parseLocationDirective(LocationConfig& loc,std::string& directive, std::string::iterator& it);
		
		//parserLocationUtils.cpp
		void								parseLocationIndex(LocationConfig& loc, std::string::iterator& it);
		void								parseAllowedMethods(LocationConfig& location, std::string::iterator& it);
		void								parseCgiPass(LocationConfig& loc, std::string::iterator& it);

		//printer
		void								printDebug() const;
};

#include "ConfigParser.tpp"
