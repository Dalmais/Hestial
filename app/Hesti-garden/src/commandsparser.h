#ifndef _COMMANDS_PARSER_
#define _COMMANDS_PARSER_

#include <atomic>
#include <map>
#include <string>
#include <memory>

#include "commands.h"

namespace rd{

class CommandParser{
public:

    static CommandParser & getInstance(){
        static CommandParser commandParser;
        return commandParser;
    }

    bool loadFile(const std::string & file);
    bool isLoadingFile() {return m_loadingFile;}

    bool parse(const std::string & text);

private:
    CommandParser(){}
    bool help(const std::string & name, const std::string & helpstr);

    std::atomic<bool> m_loadingFile;
    std::map<std::string, std::shared_ptr<Command>> m_commands;
};

}; //namespace rd

#endif // _COMMANDS_PARSER_