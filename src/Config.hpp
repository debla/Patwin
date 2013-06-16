
#ifndef Config_h
#define Config_h

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <unordered_map>
#include <string>
#include "Singleton.hpp"
#include "Includes.hpp"

using namespace std;

class Config : public Singleton<Config>
{
    typedef std::unordered_map<uint32, int64> IntConfigType;
    typedef std::unordered_map<uint32, string> StringConfigType;

public:
    bool Load(int argc, char* argv[]);

    enum IntConfig
    {
        LOGLEVEL,
        PORT,
        MAX_INT_CONFIG
    };

    enum StringConfig
    {
        PATH,
        CONFIG_FILE,
        BOUNDING,
        WORKING_DIR,
        PATWIN_LOG,
        ACCESS_LOG,
        MAX_STRING_CONFIG
    };

    IntConfigType::mapped_type getIntConfig(uint32 const option) const;
    StringConfigType::mapped_type getStringConfig(uint32 const option) const;

private:
    IntConfigType _IntConfig;
    StringConfigType _StringConfig;

    void InitDefaultValues();
    bool LoadArguments(int argc, char* argv[]);
    bool LoadConfigurationFile();
};

#define sConfig Config::instance()

#endif // Config_h

