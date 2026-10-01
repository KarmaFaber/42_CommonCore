#pragma once

#include "LocationConfig.hpp"
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>

class ServerConfig
{
	private:
		std::string								_host_ip;
		int										_port;
		std::vector<std::string>				_server_names;
		size_t									_client_max_body_size;
		std::string								_root;
		std::vector<std::string>				_index;
		std::map<int, std::string>				_error_pages;
		int										_autoindex;
		std::string								_upload_path;
		std::vector<std::string>				_allowed_methods;
		std::pair<int, std::string>				_return_url;
		std::vector<LocationConfig>				_locations;

	public:
		void propagateErrorsToLocations();
		ServerConfig();
		~ServerConfig();

		//getters
		std::vector<LocationConfig>&			getLocationsRef();
		const std::vector<std::string>&			getServerNames() const;
		const std::vector<std::string>&			getIndex() const;
		const std::map<int, std::string>&		getErrorPages() const;
		const std::vector<LocationConfig>&		getLocations() const;
		std::string								getHost() const;
		int										getPort() const;
		size_t									getClientMaxBodySize() const;
		std::string								getRoot() const;
		int										getAutoindex() const;
		std::string								getUploadPath() const;
		const std::pair<int, std::string>&		getReturnUrl() const;
		std::vector<std::string>				getAllowedMethods() const;
		bool									isMethodAllowed(const std::string &method_str) const;

		//setters
		void									setHost(const std::string& host);
		void									setPort(int port);
		void									setClientMaxBodySize(size_t size);
		void									setRoot(const std::string& root);
		void									setAutoindex(int autoindex);
		void									setUploadPath(const std::string& path);
		void									setReturnUrl(int code, const std::string& url);
		void									setAllowedMethods(const std::vector<std::string>& methods);
		void									addServerName(const std::string& name);
		void									addIndex(const std::string& index);
		void 									addErrorPage(int code, const std::string& path);
		void									addAllowedMethod(const std::string& method);
		void									addLocation(const LocationConfig& location);

		//printer
		std::string								toStringPrint() const;
};
