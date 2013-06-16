
#include "Log.hpp"

#include <string>
#include <iostream>
#include <memory>
#include "Config.hpp"

#ifdef WIN32
    #include <Windows.h>
#else
    #include <boost/lexical_cast.hpp>
#endif

using namespace std;

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
    FG_BLUE
#endif
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

ostream& Log::GetDirectOStreamForLogLevel(Level level)
{
    SetColorForLoglevel(level);
    return IsErrorLevel(level) ? cerr : cout;
}

bool Log::NeedsLog(Level level)
{
    return (level == LOG_INFO) || (level <= sConfig.getIntConfig(Config::LOGLEVEL));
}
