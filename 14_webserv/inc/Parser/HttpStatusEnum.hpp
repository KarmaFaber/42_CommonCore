#pragma once

//enum con todos los status code usados
enum HTTPStatus {
    HTTP_OK = 200,
    HTTP_CREATED = 201,
    HTTP_NOCONTENT = 204,
    HTTP_REDIRECTION = 301, //300 is multiple choices, not a generic redirect
    HTTP_FOUND = 302,
    HTTP_CLIENT_ERROR = 400,
    HTTP_FORBIDDEN = 403,
    HTTP_NOTFOUND = 404,
    HTTP_INVALID_METHOD = 405,
    HTTP_CONTENT_TOO_LARGE = 413,
    HTTP_UNSUPPORTED_TYPE = 415,
    HTTP_SERVER_ERROR = 500,
    HTTP_NOT_IMPLEMENTED = 501,
    HTTP_VERSION_NOT_SUPPORTED = 505
};
