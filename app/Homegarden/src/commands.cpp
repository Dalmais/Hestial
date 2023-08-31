#include "commands.h"

// ENUM
std::string EnumCommand::help(){
    std::string help_cmd = name() + "[";
    auto it = m_values.begin();
    while(it != m_values.end()){
        if(it->available){
            help_cmd += " " + it->name; 
        }else{
            help_cmd += " (" + it->name + ")"; 
        }
    }
    return help_cmd + "]";
}

bool EnumCommand::execute(const std::string & input, std::string & error){
    auto it = m_values.begin();

    while(it !=  m_values.end()){
        if(it->name == input){
            if(it->available == false){
                error = "value is not available";
                return false;
            }

            return setValue(it->value);
        }
        it++;
    }
    error = "Invalid value";
    return false;
}

std::string EnumCommand::value(){
    uint32_t value = getValue();
    auto it = m_values.begin();

    while(it !=  m_values.end()){
        if(it->value == value){
            if(it->available == false){
                return "UNAVAILABLE";
            }

            return it->name;
        }
        it++;
    }  
    return "UNDEFINED";
}

// STRING

std::string StringCommand::help(){
    return name() + " [STR(" + std::to_string(m_maxSize) + ")]"; 
}

bool StringCommand::execute(const std::string & input, std::string & error){
    if(input.size() > m_maxSize){
        error = "Too big input size";
        return false;
    }
    m_text = input;
    return true;
}

std::string StringCommand::value(){
    if(m_text.empty()){
        return "UNDEFINED";
    }

    return m_text;
}

// NUMBER
NumberCommand::NumberCommand(const std::string & name, const std::vector<std::string> & str_numbers) : Command(name){

}

std::string NumberCommand::help(){
    return name() + "[NUM]";
}

bool NumberCommand::execute(const std::string & input, std::string & error){
    return false;
}

std::string NumberCommand::value(){
    return "12";
}

// ON/OFF 
OnOffCommand::OnOffCommand(const std::string & name, bool & value) : EnumCommand(name), m_state(value){
    m_values.push_back(EnumCmdItem{"OFF", 0, true});       
    m_values.push_back(EnumCmdItem{"ON", 1, true});
}

bool OnOffCommand::setValue(const uint32_t idx){
    if(idx == 0){
        m_state = false;
    }else if(idx == 1){
        m_state = true;
    }
    return false;
}

// ACTION
ActionCommand::ActionCommand(const std::string & name) : EnumCommand(name){
    m_values.push_back(EnumCmdItem{"APPLY", 1, true});  
}

 bool ActionCommand::setValue(const uint32_t idx){
    if(idx == 1){
        return doAction();
    }
    return false;
 }
