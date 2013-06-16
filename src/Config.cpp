
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
    _IntConfig[LOGLEVEL]        = Log::LOG_ERROR;

    // String
    _StringConfig[CONFIG_FILE]  = _StringConfig[PATH] + "/config.xml";
}

bool Config::LoadArguments(int argc, char* argv[])
{
    options_description desc("Allowed options");
    desc.add_options()
        ("help", "produces this help message.")
        ("version,v", "shows the version and the author")
        ("config", value<string>(), "sets the config file")
    ;

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);

    
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

    READ_XML_ELEMENT("loglevel", _IntConfig[LOGLEVEL], CONVERTER_XML_INT);
    READ_XML_ELEMENT("port", _IntConfig[PORT], CONVERTER_XML_INT);

    READ_XML_ELEMENT("bounding", _StringConfig[BOUNDING], CONVERTER_XML_NONE);
    READ_XML_ELEMENT("workingdir", _StringConfig[WORKING_DIR], CONVERTER_XML_NONE);
    READ_XML_ELEMENT("patwin_log", _StringConfig[PATWIN_LOG], CONVERTER_XML_NONE);
    READ_XML_ELEMENT("access_log", _StringConfig[ACCESS_LOG], CONVERTER_XML_NONE);
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
