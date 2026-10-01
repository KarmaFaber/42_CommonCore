#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <exception>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "ServerConfig.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "HttpStatusEnum.hpp"
#include "HttpError.hpp"

class Action {
	protected:
        static const std::map<std::string, std::string> _filetypeMap;
        static const std::string _defaultFiletype;

        const Request *_req;
        const ServerConfig *_config;
        const LocationConfig *_location;
        const Session *_session;
        std::string _targetPath;
        const std::string _rawPath;
        

    public:
        Action(void): _req(NULL), _config(NULL), _location(NULL), _session(NULL), _targetPath(""), _rawPath("") {}; //empty builder for redirect action
        Action(const ServerConfig *config, const LocationConfig *loc): _req(NULL), _config(config), _location(loc), _session(NULL), _targetPath(""), _rawPath("") {};
        Action(const Request &req);

        virtual Response exec(void) = 0;

        virtual ~Action(void) {};

        static const std::string &getFiletype(const std::string &extension);
        static std::string pathConcatenate(const std::string &path1, const std::string &path2);
};

Action *buildAction(const Request &req);
