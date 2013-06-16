
#ifndef Log_h
#define Log_h

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "Singleton.hpp"
#include "Includes.hpp"
#include <cstdarg>
#include <cstdio>
#include <memory>
#include <iostream>

#define DefineLogLevel(NAME, LOGLEVEL) \
    void NAME (std::string const& str, ...) \
    { \
        if (!Log::NeedsLog( LOGLEVEL )) \
            return; \
        va_list append; \
        va_start(append, str); \
        logMsg<LOGLEVEL>(str, append); \
        va_end(append); \
    }

class Log : public Singleton<Log>
{
public:
    enum Level
    {
        LOG_INFO,
        LOG_ERROR,
        LOG_WARNING,
        LOG_FATAL,
        LOG_DEBUG,
        LOG_MAX_LOGLEVEL
    };

    Log() : curColorLevel(LOG_MAX_LOGLEVEL) {}
    ~Log() { Reset(); }

    DefineLogLevel(outInfo    , LOG_INFO    );
    DefineLogLevel(outError   , LOG_ERROR   );
    DefineLogLevel(outWarning , LOG_WARNING );
    DefineLogLevel(outFatal   , LOG_FATAL   );
    DefineLogLevel(outDebug   , LOG_DEBUG   );

    std::ostream& GetDirectOStreamForLogLevel(Level level);

    void Reset();

private:
    template <Level LOGLEVEL>
    void logMsg(std::string const& str, va_list const& append)
    {
        uint32 const size = 4096;
        char* msg = new char[4096];

#ifdef WIN32
        vsprintf_s(msg, size, str.c_str(), append);
#else
        vsnprintf(msg, size, str.c_str(), append);
#endif
        {
            SetColorForLoglevel(LOGLEVEL);
            if (IsErrorLevel(LOGLEVEL))
                std::cerr << msg << std::endl;
            else
                std::cout << msg << std::endl;
        }

        delete[] msg;
    }

    static uint32 const ColorList[LOG_MAX_LOGLEVEL];
    void SetColorForLoglevel(Level level);
    uint8 curColorLevel;

    inline bool IsErrorLevel(Level level) const { return level == LOG_ERROR || level == LOG_FATAL; }
    static bool NeedsLog(Level level);
};

#undef DefineLogLevel
#define sLog Log::instance()

#endif // Log_h
