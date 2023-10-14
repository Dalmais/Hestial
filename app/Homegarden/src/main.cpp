// Copyright (c) 2023 Romain Damais <dalmais<at>gmail.com>
// See end of file for extended copyright information

#include <iostream>
#include "commands.h"

class TestNumber: public NumberCommand{
    public:
    TestNumber(const TestNumber & other) : NumberCommand(other){}
    TestNumber(const std::string & name) : NumberCommand(name){
        m_separator = ";";
        m_precision = 1;
        m_numbers.push_back(DefinitionNumber(255, 0, 1, DEC));
        m_numbers.push_back(DefinitionNumber(0, -255, 1, DEC));
        m_numbers.push_back(DefinitionNumber(0xFF, 0, 1, HEX));
        m_numbers.push_back(DefinitionNumber(42.0, 0.0, 1.2, FLOAT));
        m_numbers.push_back(DefinitionNumber(-1.0, -42.0, 1.3, FLOAT));
        m_values = {0.0,0.0,0.0,0.0,0.0};
    }

    virtual ~TestNumber(){}

protected:
    virtual std::vector<double> getValue(){
        return m_values;
    }
    virtual void setValue(std::vector<double> value){
        m_values = value;
    }

private:
    std::vector<double> m_values;
};

int main(int argc,  char** argv){
    std::cout << "Hello World!" << std::endl;



    TestNumber cmd1("testNumber");
    std::string err;
    bool ret = cmd1.execute("192;-123;0xdd;21.3;-11.85", err) ;
    std::cout << "retour:" << ret  << " value:" << cmd1.value() << " err: " << err << std::endl;

    return 0;
}


/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
