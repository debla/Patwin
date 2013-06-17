
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

#ifndef Config_h
#define Config_h

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <map>
#include <string>
#include "Singleton.hpp"
#include "Includes.hpp"

using namespace std;

class Config : public Singleton<Config>
{
    typedef std::map<uint32, int64> IntConfigType;
    typedef std::map<uint32, string> StringConfigType;

public:
    bool Load(int argc, char* argv[]);

    enum IntConfig
    {
        PORT,
        CONSOLE_LOGLEVEL,
        FILE_LOGLEVEL,
        MAX_INT_CONFIG
    };

    enum StringConfig
    {
        PATH,
        CONFIG_FILE,
        BOUNDING,
        WORKING_DIR,
        PATWIN_LOG,
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

