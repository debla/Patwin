/*

#include <iostream>



namespace http = boost::network::http;

struct handler;
typedef http::server<handler> http_server;

using namespace std;

struct handler
{
    void operator() (http_server::request const& request,
                     http_server::response& response)
    {
        std::string const ip = request.source;
        std::string const dest = request.destination;


        std::cout << "Ip: " << ip << "\nDestination: " << dest << endl << endl;

        response = http_server::response::stock_reply(
            http_server::response::ok, "Hello, world!");
    }

    void log(http_server::string_type const &info)
    {
        std::cerr << "ERROR: " << info << '\n';
    }
};

*/


#include "Config.hpp"
#include "Log.hpp"
#include "Patwin.hpp"

int main(int argc, char* argv[])
{
    sLog.outInfo("Patwin - (c) 2013 Denis Blank");
    if (!sConfig.Load(argc, argv))
        return EXIT_FAILURE;

    /*

    handler handler_;
    http_server server_("0.0.0.0", "8000", handler_);
    server_.run();
    */

    return EXIT_SUCCESS;
}
