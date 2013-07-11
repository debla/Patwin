
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

#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include "Log.hpp"
#include "Config.hpp"

#ifdef WIN32
    #include <Windows.h>
#else
    #include <boost/lexical_cast.hpp>
#endif

using namespace std;
using namespace boost::posix_time;

#ifndef WIN32
    enum LinuxColors
    {
        FG_BLACK = 30,
        FG_RED,
        FG_GREEN,
        FG_BROWN,
        FG_BLUE,
        FG_MAGENTA,
        FG_CYAN,
        FG_WHITE,
        FG_YELLOW
    };
#endif

uint32 const Log::ColorList[LOG_MAX_LOGLEVEL] =
{
#ifdef WIN32
    // Windows
    // INFO
    FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    // ERROR
    FOREGROUND_RED   | FOREGROUND_INTENSITY,    
    // WARNING
    FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    // FATAL
    FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    // DEBUG
    FOREGROUND_RED   | FOREGROUND_GREEN
#else
    // Unix
    // INFO
    FG_CYAN,
    // ERROR
    FG_RED,
    // WARNING
    FG_YELLOW,
    // FATAL
    FG_BROWN,
    // DEBUG
    FG_MAGENTA
#endif
};

std::string const Log::NameForLogLevel[] =
{
    "INFO   ",
    "ERROR  ",
    "WARNING",
    "FATAL  ",
    "DEBUG  "
};

void Log::SetColorForLoglevel(Level level)
{
    if (curColorLevel == level)
        return;

    #ifdef WIN32
        HANDLE hConsole = GetStdHandle(IsErrorLevel(level) ? STD_ERROR_HANDLE : STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, ColorList[level]);
    #else
        std::string const fmt = "\x1b[" + boost::lexical_cast<std::string>(ColorList[level]) + "m";
        if (IsErrorLevel(level))
            std::cout << fmt;
        else
            std::cerr << fmt;
    #endif

    curColorLevel = level;
}

void Log::Reset()
{
    #ifdef WIN32
        SetColorForLoglevel(LOG_INFO);
    #else
        std::cout << "\x1b[0m";
        std::cerr << "\x1b[0m";
    #endif
}

bool Log::NeedsConsoleLog(Level level)
{
    return (level == LOG_INFO) ||
        (level <= sConfig.getIntConfig(Config::CONSOLE_LOGLEVEL));
}

bool Log::NeedsFileLog(Level level)
{
    return (level == LOG_INFO) ||
        (level <= sConfig.getIntConfig(Config::FILE_LOGLEVEL));
}

void Log::LogMessage(Level level, char* msg)
{
    if (NeedsConsoleLog(level))
    {
        SetColorForLoglevel(level);
        if (IsErrorLevel(level))
            std::cerr << msg << std::endl;
        else
            std::cout << msg << std::endl;
    }

    if (NeedsFileLog(level))
    {
        std::string const logfile = sConfig.getStringConfig(Config::PATWIN_LOG);
        if (!logfile.empty())
        {
            std::ofstream file((char const*)logfile.c_str(), std::ios::app);
            if (!file.is_open())
            {
                SetColorForLoglevel(LOG_ERROR);
                std::cerr << "Could't open logfile \"" << logfile << "\" for writing." << std::endl;
                return;
            }

            // Builds our current date/timestamp
            std::stringstream ss;
            time_facet* facet = new time_facet("%Y-%m-%d - %H:%M:%S ");
            ss.imbue(locale(cout.getloc(), facet));
            ss << second_clock::local_time();

            file << ss.str() << NameForLogLevel[level] << ": " << msg << std::endl;
            file.close();
        }
    }
}
