#include <fstream>
#include <iostream>
#include <sstream>
#include "commandsparser.h"

namespace rd{

bool CommandParser::loadFile(const std::string & filepath){
    m_loadingFile = true;

    bool ret = true;

    std::ifstream file(filepath, std::ios::binary);

    if (!file.is_open()){
        std::cout << "failed to open " << filepath << std::endl;
        ret = false;
    }else{
        std::string line;
        while (std::getline(file, line)){
            if(parse(line) == false){
                ret = false;
            }
        }
    }

    m_loadingFile = false;

    return ret;
}

bool CommandParser::parse(const std::string & text){

    int endName = text.find(" ");
    std::string name = text.substr(0, endName);
    if(m_commands.find(name) == m_commands.end()){
        std::cout << "Unknown command " << name;
        return false;
    }

    int firstParam = endName;
    while((firstParam < text.size()) && (text[firstParam] != ' ')){
        firstParam++;
    }

    if(firstParam >= text.size()){
        std::cout << name << " " << m_commands[name]->value() << std::endl;
        return true;
    }

    std::string param = text.substr(firstParam);

    if(param == "HELP"){
        std::cout << name << m_commands[name]->help() << std::endl;
        return true;
    }

    std::string err;
    bool ret = m_commands[name]->execute(param, err);
    if(!err.empty()) std::cout << err << std::endl;
    std::cout << name << " " << m_commands[name]->value() << std::endl;
    return ret;
} 

}; //namespace rd

