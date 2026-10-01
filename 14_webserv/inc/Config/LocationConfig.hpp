#pragma once

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <iostream>

class LocationConfig
{
	private:
		std::string								_path_match;
		std::string								_root;
		std::vector<std::string>				_index;
		std::vector<std::string>				_allowed_methods;
		std::map<std::string, std::string>		_cgis;
		size_t									_client_max_body_size;
		int										_autoindex;
		std::string								_upload_path;
		std::pair<int, std::string>				_return_url;
		std::map<int, std::string>				_loc_error_pages;

	public:
		LocationConfig();
		~LocationConfig();
		
		//getters location
		std::string									getPathMatch() const;
		std::string									getRoot() const;
		const std::vector<std::string>&				getIndex() const;
		std::vector<std::string>					getAllowedMethods() const;
		bool										isMethodAllowed(const std::string &method_str) const;
		const std::map<std::string, std::string>&	getCgis() const;
		size_t										getClientMaxBodySize() const;
		int											getAutoindex() const;
		std::string									getUploadPath() const;
		const std::pair<int, std::string>&			getReturnUrl() const;
		const std::map<int, std::string>&			getErrorPages() const;
		
		//setters location
		void										addIndex(const std::string& index);
		void										setPathMatch(const std::string& path);
		void										setRoot(const std::string& root);
		void										setAllowedMethods(const std::vector<std::string>& methods);
		void										addAllowedMethod(const std::string& method);
		void										addCgi(const std::string& ext, const std::string& path);
		void										setClientMaxBodySize(size_t size);
		void										setAutoindex(int autoindex);
		void										setUploadPath(const std::string& upload_path);
		void										setReturnUrl(int code, const std::string& url);
		void										addLocErrorPage(int status, const std::string& path);

		//printer
		std::string									toStringPrint() const;
};
