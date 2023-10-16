#ifndef _COMMANDS_
#define _COMMANDS_

#include <string>
#include <vector>

class Command{
public:
    Command(const Command & other) : m_name(other.m_name){}
    Command(const std::string & name) : m_name(name){}

    virtual ~Command(){}

    virtual std::string help() = 0;
    virtual bool execute(const std::string & input, std::string & error) = 0;

    virtual std::string name(){return m_name;}
    virtual std::string value() = 0;
    virtual bool isValid(){return m_valid;}

private:
    std::string m_name;
    bool        m_valid;
};

class EnumCommand : public Command{
public:

    struct EnumCmdItem{
        std::string name;
        int value;
        bool available;
    }; 

    EnumCommand(const EnumCommand & other) : Command(other), m_values(other.m_values){}
    EnumCommand(const std::string & name) : Command(name){}

    virtual ~EnumCommand(){}

    virtual std::string help();
    virtual bool execute(const std::string & input, std::string & error);
    virtual std::string value();

protected:
    virtual bool setValue(const uint32_t idx) = 0;
    virtual int getValue() = 0;

    std::vector<EnumCmdItem> m_values;
};

class StringCommand : public Command{
public:
    StringCommand(const StringCommand & other) : Command(other), m_text(other.m_text){}
    StringCommand(const std::string & name, std::string & text, uint32_t size = 32) : Command(name), m_text(text), m_maxSize(size){}

    virtual ~StringCommand(){}

    virtual std::string help();
    virtual bool execute(const std::string & input, std::string & error);
    virtual std::string value();

private:
    std::string & m_text;
    uint32_t m_maxSize;
};

class NumberCommand : public Command{
public:

    enum IntType{
        DEC=0,
        HEX,
        FLOAT
    };

    struct DefinitionNumber{
        double max;
        double min;
        double step;
        IntType type;
        DefinitionNumber(double ma, double mi, double s, IntType t) : max(ma),min(mi), step(s), type(t){}
        DefinitionNumber(int ma, int mi, int s, IntType t): max((double)ma),min((double)mi), step((double)s), type(t){}

    };
    NumberCommand(const NumberCommand & other) : 
        Command(other), m_numbers(other.m_numbers), m_separator(other.m_separator), m_precision(other.m_precision){}
    NumberCommand(const std::string & name);

    virtual ~NumberCommand(){}

    virtual std::string help();
    virtual bool execute(const std::string & input, std::string & error);
    virtual std::string value();
    virtual void setSeparator(std::string s){m_separator = s;}
    virtual void setPrecision(uint32_t p){m_precision = p;}

protected:
    virtual std::vector<double> getValue() = 0;
    virtual void setValue(std::vector<double> value) = 0;

    std::vector<DefinitionNumber> m_numbers;
    std::string m_separator;
    uint32_t m_precision;

private:
// returns count of non-overlapping occurrences of 'sub' in 'str'
    int countSubstring(const std::string& str, const std::string& sub);

    uint32_t numberSize(int32_t number);
};

class OnOffCommand : public EnumCommand{
public:

    OnOffCommand(const OnOffCommand & other): EnumCommand(other), m_state(other.m_state){}
    OnOffCommand(const std::string & name, bool & value);

    virtual ~OnOffCommand(){}

    static const uint8_t NB_ITEM = 2;

protected:
    virtual bool setValue(const uint32_t idx);
    virtual int getValue(){return m_state ? m_values[1].value : m_values[0].value;}

private:

    bool & m_state;
};

class ActionCommand : public EnumCommand{
public:
    ActionCommand(const ActionCommand & other): EnumCommand(other){}
    ActionCommand(const std::string & name);

    virtual ~ActionCommand(){}

    virtual std::string value(){return "UNDEFINED";}

protected:
    virtual bool setValue(const uint32_t idx);
    virtual int getValue(){return 0;}
    virtual bool doAction() = 0;

};


#endif // _COMMANDS_
