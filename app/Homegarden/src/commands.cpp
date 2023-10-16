#include "commands.h"

#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cmath>
#include <iomanip>

// ENUM
std::string EnumCommand::help(){
    std::string help_cmd = name() + " [ENUM";
    auto it = m_values.begin();
    while(it != m_values.end()){
        if(it->available){
            help_cmd += " [" + it->name + "]"; 
        }else{
            help_cmd += " (" + it->name + ")"; 
        }
        it++;
    }
    return help_cmd + "]";
}

bool EnumCommand::execute(const std::string & input, std::string & error){
    auto it = m_values.begin();
    error.clear();

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
    error.clear();
    if(input.size() > m_maxSize){
        error = "Input size too big";
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
NumberCommand::NumberCommand(const std::string & name) : 
    Command(name), m_separator("."), m_precision(0){

}

uint32_t NumberCommand::numberSize(int32_t number){
  unsigned int number_of_digits = 0;

    do {
        ++number_of_digits; 
        number /= 10;
    } while (number);  

    return number_of_digits;
}

std::string NumberCommand::help(){
    std::stringstream ret;
    ret << std::showbase << std::internal << std::setprecision(m_precision) << std::fixed;
    ret << name() << " [NUM ";
    for(int i=0; i<m_numbers.size(); i++){
        if(m_numbers[i].type == HEX){
            int min = std::round(m_numbers[i].min);
            int step = std::round(m_numbers[i].step);
            int max = std::round(m_numbers[i].max);
            ret << "HEX[" << std::hex << std::nouppercase ;
            if(min == 0){
                ret << "0x"; // https://bugzilla.redhat.com/show_bug.cgi?id=166735 
            } 
            ret << min << ":";
            if(step == 0){
                ret << "0x"; // https://bugzilla.redhat.com/show_bug.cgi?id=166735 
            } 
            ret << step << ":";
            if(max == 0){
                ret << "0x"; // https://bugzilla.redhat.com/show_bug.cgi?id=166735 
            } 
            ret << max << "]"; 

        }else if(m_numbers[i].type == DEC){
            
            int min = std::round(m_numbers[i].min);
            int step = std::round(m_numbers[i].step);
            int max = std::round(m_numbers[i].max);
            ret << "DEC[" << std::dec << min << ":" << step << ":" << max << "]"; 

        }else if(m_numbers[i].type == FLOAT){
            ret << "FLOAT[" << std::dec << m_numbers[i].min << ":" << m_numbers[i].step << ":" << m_numbers[i].max << "]"; 

        }else{
            return "Bad format";
        }
        if(i < m_numbers.size()-1){
            ret << m_separator;
        }
    }
    ret << "]";
    return ret.str();
}

// returns count of non-overlapping occurrences of 'sub' in 'str'
int NumberCommand::countSubstring(const std::string& str, const std::string& sub)
{
    if (sub.length() == 0) return 0;
    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos;
     offset = str.find(sub, offset + sub.length()))
    {
        ++count;
    }
    return count;
}

bool NumberCommand::execute(const std::string & input, std::string & error){

    size_t pos=0, rpos = 0;
    std::vector<double> values;
    error.clear();

    auto count = countSubstring(input, m_separator);
    if (count+1 > m_numbers.size()){
        error = "Too many values: " + std::to_string(count+1) + "/" + std::to_string(m_numbers.size());
        return false;
    }
    if (count+1 < m_numbers.size()){
        error = "Not enough values: " + std::to_string(count+1) + "/" + std::to_string(m_numbers.size());
        return false;
    }

//    std::cout << input << std::endl; 
    for(int i=0; i<m_numbers.size(); i++){
        std::string strvalue;
        try{

            pos = input.find(m_separator, rpos);
            bool noSeparator = (pos == std::string::npos);

            //if first elem then start is rpo
            int valueidx = rpos==0?rpos:rpos+1;
            int valuesize = noSeparator?input.size()-rpos:pos-rpos;
            strvalue = input.substr(rpos, valuesize);
            double value = 0.0;
            
            if(strvalue.size()>2 && \
              ((strvalue.substr(0,2) == "0x") || strvalue.substr(0,2) == "0X")){
                value = std::stol(strvalue, 0, 16);
            }else{
                value = std::stod(strvalue);
            }
            if(m_numbers[i].max < value){
                throw std::out_of_range("Too big");
            }
            if(m_numbers[i].min > value){
                throw std::out_of_range("Too small");
            }

            values.push_back(value);
        }
        catch(std::invalid_argument const& ){
            error = "Invalid value : '" + strvalue + "'";
            return false;

        }
        catch(std::out_of_range const& ){
            error = "Argument out of range : '" + strvalue + "'";
            return false;
        }
        catch(std::exception& ){
            error = "Bad format : '" + strvalue + "'";
            return false;
        }
        
        rpos = pos+1;
    }

    setValue(values);
    return true;
}

std::string NumberCommand::value(){

    if(m_numbers.empty()){
        return "UNDEFINED";
    }

    std::stringstream ret;
    std::vector<double> value = getValue();

    if(value.size() != m_numbers.size()){
        return "INVALID";
    }

    for(int i=0; i<m_numbers.size(); i++){
        if(i>0){
            ret << m_separator;
        }

        double min = m_numbers[i].min;
        double max = m_numbers[i].max;
        double currentvalue = value[i];

        if(max < currentvalue){
            return "INVALID";
        }
        if(min > currentvalue){
            return "INVALID";
        }

        if(m_numbers[i].type == HEX){
            ret << std::hex << std::nouppercase;
            ret << "0x" << static_cast<int>(std::round(currentvalue));
        }else if(m_numbers[i].type == DEC){
            ret << std::dec << std::round(currentvalue);
        }else if(m_numbers[i].type == FLOAT){
            ret << std::dec << std::setprecision(m_precision) << std::fixed << currentvalue;
        }
    }

    return ret.str();
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
    }else{
        return false;
    }
    return true;
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
