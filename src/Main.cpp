
#include <boost/mime.hpp>
#include <boost/network/protocol/http/server.hpp>

#include <iostream>

#include "Log.hpp"

namespace http = boost::network::http;

struct handler;
typedef http::server<handler> http_server;

struct handler
{
    void operator() (http_server::request const& request,
                     http_server::response& response)
    {
        response = http_server::response::stock_reply(
            http_server::response::ok, "Hello, world!");
    }

    void log(http_server::string_type const &info)
    {
        std::cerr << "ERROR: " << info << '\n';
    }
};


int main(int arg, char* argv[])
{
    sLog.outInfo("Patwin - (c) 2013 Denis Blank");

    handler handler_;
    http_server server_("0.0.0.0", "8000", handler_);
    server_.run();
}
