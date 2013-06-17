
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

#include <boost/filesystem/path.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include "tinyxml.h"
#include "Config.hpp"
#include "Log.hpp"
#include "Version.hpp"

using namespace boost::program_options;

bool Config::Load(int argc, char* argv[])
{
    {
        boost::filesystem::path path(argv[0]);
        _StringConfig[PATH] = path.branch_path().string();
    }

    // Default Values
    InitDefaultValues();
    // Processes the Arguments
    RETURN_IF_FALSE(LoadArguments(argc, argv));
    // Loads the Configuration File
    RETURN_IF_FALSE(LoadConfigurationFile());
    return true;
}

void Config::InitDefaultValues()
{
    // Int
    _IntConfig[CONSOLE_LOGLEVEL]        = Log::LOG_ERROR;
    _IntConfig[FILE_LOGLEVEL]        = Log::LOG_ERROR;

    // String
    _StringConfig[CONFIG_FILE]  = _StringConfig[PATH] + "/config.xml";
}

bool Config::LoadArguments(int argc, char* argv[])
{
    options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produces this help message.")
        ("version,v", "shows the version and the author")
        ("config", value<string>(), "sets the config file")
    ;

    variables_map vm;

    try
    {
        store(parse_command_line(argc, argv, desc), vm);
    }
    catch (std::exception& e)
    {
        sLog.outError("%s", e.what());
        return false;
    }

    if (vm.count("help"))
    {
        desc.print(std::cout);
        return false;
    }

    if (vm.count("version"))
    {
        std::cout << "Patwin Version: " << version  << std::endl;
        return false;
    }

    if (vm.count("config"))
        _StringConfig[CONFIG_FILE] = vm["config"].as<std::string>();

    return true;
}

#define CONVERTER_XML_NONE( DIGEST ) DIGEST
#define CONVERTER_XML_INT( DIGEST ) boost::lexical_cast<Config::IntConfigType::mapped_type> ( DIGEST )

#define READ_XML_ELEMENT( NAME, DEST, CONVERTER ) \
    { \
        if(TiXmlElement* element = node->FirstChildElement( NAME )) \
            DEST = CONVERTER(element->GetText()); \
        else \
            return false; \
    }

bool Config::LoadConfigurationFile()
{
    std::string const path = getStringConfig(CONFIG_FILE);

    TiXmlDocument xmlFile(path.c_str());
    if (!xmlFile.LoadFile())
    {
        sLog.outError("Didn't find the configuration file (%s).", path.c_str());
        return false;
    }

    TiXmlNode* node = xmlFile.FirstChild("Patwin");
    RETURN_IF_FALSE(node);

    READ_XML_ELEMENT("port", _IntConfig[PORT], CONVERTER_XML_INT);
    READ_XML_ELEMENT("console_loglevel", _IntConfig[CONSOLE_LOGLEVEL], CONVERTER_XML_INT);
    READ_XML_ELEMENT("file_loglevel", _IntConfig[FILE_LOGLEVEL], CONVERTER_XML_INT);

    READ_XML_ELEMENT("bounding", _StringConfig[BOUNDING], CONVERTER_XML_NONE);
    READ_XML_ELEMENT("workingdir", _StringConfig[WORKING_DIR], CONVERTER_XML_NONE);
    READ_XML_ELEMENT("patwin_log", _StringConfig[PATWIN_LOG], CONVERTER_XML_NONE);
    _StringConfig[PATWIN_LOG] = _StringConfig[PATH] + "/" + _StringConfig[PATWIN_LOG];

    return true;
}

#undef READ_XML_ELEMENT
#undef CONVERTER_XML_NONE
#undef CONVERTER_XML_INT64

Config::IntConfigType::mapped_type Config::getIntConfig(uint32 const option) const
{
    IntConfigType::const_iterator itr = _IntConfig.find(option);
    return ((itr != _IntConfig.end()) ? itr->second : 0);
}

Config::StringConfigType::mapped_type Config::getStringConfig(uint32 const option) const
{
    StringConfigType::const_iterator itr = _StringConfig.find(option);
    return ((itr != _StringConfig.end()) ? itr->second : "");
}
