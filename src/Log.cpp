
#include "Log.hpp"

#include <string>
#include <iostream>
#include <memory>

#ifdef WIN32
    #include <Windows.h>
#else

#endif

using namespace std;

uint32 const Log::ColorList[LOG_MAX_LOGLEVEL] =
{
#ifdef WIN32
    // Windows
    // INFO
    FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    // WARNING
    FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    // ERROR
    FOREGROUND_RED   | FOREGROUND_INTENSITY,
    // FATAL
    FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    // DEBUG
    FOREGROUND_RED   | FOREGROUND_GREEN
#else
    // Unix
    // INFO
    0,
    // WARNING
    0,
    // ERROR
    0,
    // FATAL
    0,
    // DEBUG
    0
#endif
};

void Log::SetColorForLoglevel(Level level)
{
    if (curColorLevel == level)
        return;

    #ifdef WIN32
        HANDLE hConsole = GetStdHandle(IsErrorLevel(level) ? STD_ERROR_HANDLE : STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, ColorList[level]);
        curColorLevel = level;
    #else

    #endif
}

ostream& Log::GetDirectOStreamForLogLevel(Level level)
{
    SetColorForLoglevel(level);
    return IsErrorLevel(level) ? cerr : cout;
}
