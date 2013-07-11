
/*
    Copyright (C) 2013 Denis Blank

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <sstream>
#include <fstream>
#include <boost/mime.hpp>
#include <boost/network/protocol/http/server.hpp>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include <iterator>
#include "Patwin.hpp"

namespace http = boost::network::http;

struct handler;
typedef http::server<handler> http_server;

using namespace std;

struct handler
{
    void operator() (http_server::request const& request,
                     http_server::response& response)
    {
        if (request.destination == "/")
            request.destination = "/index.html";

        sLog.outDebug("IP: %s requested file \"%s\".",
                      request.source.c_str(),
                      request.destination.c_str());

        std::string const rFile = sConfig.getStringConfig(Config::PATH) +
                                  sConfig.getStringConfig(Config::WORKING_DIR) +
                                  request.destination;

        std::ostringstream ss;
        std::ifstream file((char const*)rFile.c_str(), std::ios::binary);
        if (!file.is_open())
        {
            sLog.outDebug("Didn't find File \"%s\"", rFile.c_str());
            ss << "404 - File not found";
        }
        else
        {
            sLog.outDebug("Found File \"%s\"", rFile.c_str());

            copy(istreambuf_iterator<char>(file),
                 istreambuf_iterator<char>(),
                 ostreambuf_iterator<char>(ss));

            file.close();
        }

        response = http_server::response::stock_reply(
            http_server::response::ok, ss.str());
    }

    void log(http_server::string_type const &info)
    {
        sLog.outError("%s", info.c_str());
    }
};

int Patwin::run()
{
    handler _handler;
    http_server _server(sConfig.getStringConfig(Config::BOUNDING),
        boost::lexical_cast<std::string>(sConfig.getIntConfig(Config::PORT)), _handler);

    sLog.outDebug("Using Logfile: %s",
        sConfig.getStringConfig(Config::PATWIN_LOG).c_str());
    sLog.outDebug("Using Working Dir: %s",
        sConfig.getStringConfig(Config::WORKING_DIR).c_str());
    sLog.outDebug("Current Path is %s",
        sConfig.getStringConfig(Config::PATH).c_str());
    sLog.outInfo("Patwin is listen on %s:%i now.\n",
        sConfig.getStringConfig(Config::BOUNDING).c_str(),
            sConfig.getIntConfig(Config::PORT));

    _server.run();
    return EXIT_SUCCESS;
}
