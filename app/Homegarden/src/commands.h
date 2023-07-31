#ifndef _COMMANDS_
#define _COMMANDS_

#include <string>

class Command{
public:
    Command(const Command & other){m_name = other.m_name;}
    Command(std::string name){m_name = name;}
    std::string name(){return m_name;}

private:
    std::string m_name;
};

#endif // _COMMANDS_