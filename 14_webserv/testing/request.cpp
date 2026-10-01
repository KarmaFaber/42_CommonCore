#include "catch.hpp"
#include "Client.hpp"
#include "Request.hpp"
#include <memory.h>

TEST_CASE("Request: basic request", "[success]") {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    Client cli(0, addr, 4242);
    std::string req_test = "GET / HTTP/1.0\r\n\r\n";
    Request req(req_test, cli);
    CHECK(req.getMethod() == GET);
    CHECK(req.getPath() == "/");
    CHECK(req.getHeaders().empty());
    CHECK(req.getBody().empty());
    CHECK(req.getVersion() == HTTP_1_0);

    req_test = "GET / HTTP/1.0\r\n\r\n\r\n\r\n"; //doesnt matter how many empty lines there are, it should still be accepted
    Request req2(req_test, cli);
    CHECK(req2.getMethod() == GET);
    CHECK(req2.getPath() == "/");
    CHECK(req2.getHeaders().empty());
    CHECK(req2.getBody().empty());
    CHECK(req2.getVersion() == HTTP_1_0);

    req_test = "GET / HTTP/1.0\r\n\r\n\r\n\r\nfiafoafiwaafva<clclms1931\r\n"; //garbage bytes after request end, still valid
    Request req3(req_test, cli);
    CHECK(req3.getMethod() == GET);
    CHECK(req3.getPath() == "/");
    CHECK(req3.getHeaders().empty());
    CHECK(req3.getBody().empty());
    CHECK(req3.getVersion() == HTTP_1_0);

    //todo move to another category for body or config checks? also add tests for chunked bodies, with and without extensions
    req_test = "POST / HTTP/1.0\r\nContent-Length: 1\r\n\r\na";
    Request req4(req_test, cli);
    ConfigParser conf("testing/config_file/http/default.conf");
    req4.verifyConfig(conf);
    req4.parseBody(req_test);
    CHECK(req4.getMethod() == POST);
    CHECK(req4.getPath() == "/");
    CHECK(req4.getHeaders().size() == 1);
    CHECK(req4.getBody() == "a");
    CHECK(req4.getVersion() == HTTP_1_0);
}

TEST_CASE("Request: keep-alive", "[success]") {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    Client cli(0, addr, 4242);
    std::string req_test = "GET / HTTP/1.0\r\n\r\n";
    Request req(req_test, cli);
    CHECK_FALSE(req.getKeepAlive()); //default to false in 1.0

    req_test = "GET / HTTP/1.1\r\nHost: placeholder\r\n\r\n";
    Request req2(req_test, cli); //todo make = constructor for faster testing
    CHECK(req2.getKeepAlive()); //default to true in 1.1

    //connection header overwrites version default
    req_test = "GET / HTTP/1.0\r\nConnection: keep-alive\r\n\r\n";
    Request req3(req_test, cli);
    CHECK(req3.getKeepAlive());

    req_test = "GET / HTTP/1.1\r\nHost: placeholder\r\nConnection: close\r\n\r\n";
    Request req4(req_test, cli);
    CHECK_FALSE(req4.getKeepAlive());

    //close value always overwrites everything else
    req_test = "GET / HTTP/1.0\r\nConnection: close, keep-alive\r\n\r\n";
    Request req5(req_test, cli);
    CHECK_FALSE(req5.getKeepAlive());

    req_test = "GET / HTTP/1.0\r\nConnection: close\r\nConnection: keep-alive\r\n\r\n"; //separate headers should have the same effect
    Request req6(req_test, cli);
    CHECK_FALSE(req6.getKeepAlive());

    req_test = "GET / HTTP/1.0\r\nConnection: keep-alive\r\nConnection: close\r\n\r\n"; //order shouldnt matter
    Request req7(req_test, cli);
    CHECK_FALSE(req7.getKeepAlive());

    req_test = "GET / HTTP/1.0\r\nConnection: keep-alive, upgrade\r\n\r\n"; //unknown values get ignored
    Request req8(req_test, cli);
    CHECK(req8.getKeepAlive());
}

TEST_CASE("Request: basic wrong requests", "[fail]") {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    Client cli(0, addr, 4242);
    std::string req_test = "GET / HTTP/1.2\r\n\r\n";
    CHECK_THROWS_WITH(
        Request(req_test, cli),
        "505 HTTP Version Not Supported"
    );

    req_test = "HEAD / HTTP/1.0\r\n\r\n";
    CHECK_THROWS_WITH(
        Request(req_test, cli),
        "501 Not Implemented"
    );

    req_test = "GET wrong/path HTTP/1.0\r\n\r\n"; //should always start with slash
    CHECK_THROWS_WITH(
        Request(req_test, cli),
        "400 Bad Request"
    );

    req_test = "GET /relative/./path HTTP/1.0\r\n\r\n";
    CHECK_THROWS_WITH(
        Request(req_test, cli),
        "400 Bad Request"
    );

    req_test = "GET /relative/path/.. HTTP/1.0\r\n\r\n";
    CHECK_THROWS_WITH(
        Request(req_test, cli),
        "400 Bad Request"
    );

    req_test = "GET / HTTP/1.1\r\n\r\n"; //HTTP/1.1 must always have Host header
    CHECK_THROWS_WITH(
        Request(req_test, cli),
        "400 Bad Request"
    );

    //todo move this test to different category, since it is enforcing config checks, not just basic syntax
    req_test = "GET / HTTP/1.0\r\nContent-Length: 1\r\n\r\na";
    Request req(req_test, cli);
    ConfigParser conf("testing/config_file/http/no_uploads.conf");
    req.verifyConfig(conf);
    CHECK_THROWS_WITH(
        req.parseBody(req_test),
        "413 Content Too Large"
    );

    req_test = "POST / HTTP/1.0\r\n\r\n";
    Request req5(req_test, cli);
    conf = ConfigParser("testing/config_file/http/no_methods.conf");
    CHECK_THROWS_WITH(
        req5.verifyConfig(conf),
        "405 Unsupported method"
    );

    req_test = "GET /upload HTTP/1.0\r\n\r\n";
    Request req6(req_test, cli);
    conf = ConfigParser("testing/config_file/http/no_methods.conf");
    CHECK_THROWS_WITH(
        req6.verifyConfig(conf),
        "405 Unsupported method"
    );
}