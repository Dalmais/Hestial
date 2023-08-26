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
    EnumCommand(const std::string & name, std::vector<EnumCmdItem> values) : Command(name), m_values(values){}

    virtual ~EnumCommand(){}

    virtual std::string help();
    virtual bool execute(const std::string & input, std::string & error);
    virtual std::string value();

protected:
    virtual bool setValue(const uint32_t idx) = 0;
    virtual int getValue() = 0;

private:
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
    NumberCommand(const NumberCommand & other): Command(other), m_numbers(other.m_numbers), m_separator(other.m_separator){}
    NumberCommand(const std::string & name, const std::vector<std::string> & str_numbers);

    virtual ~NumberCommand(){}

    virtual std::string help();
    virtual bool execute(const std::string & input, std::string & error);
    virtual std::string value();

private:
    std::vector<double> m_numbers;
    std::string m_separator;
};

class OnOffCommand : public EnumCommand{
public:

    OnOffCommand(const OnOffCommand & other): EnumCommand(other), m_value(other.m_value), m_items(other.m_items){}
    OnOffCommand(const std::string & name, bool & value);

    virtual ~OnOffCommand(){}

    static const uint8_t NB_ITEM = 2;

protected:
    virtual bool setValue(const uint32_t idx);
    virtual int getValue(){return m_value ? m_items[1].value : m_items[0].value;}

private:

    bool & m_value;
    std::vector<EnumCmdItem> m_items;
};

class ActionCommand : public EnumCommand{
public:
    ActionCommand(const ActionCommand & other): EnumCommand(other), m_items(other.m_items){}
    ActionCommand(const std::string & name);

    virtual ~ActionCommand(){}

    virtual std::string value(){return "UNDEF";}

protected:
    virtual bool setValue(const uint32_t idx);
    virtual int getValue(){return 0;}
    virtual bool doAction() = 0;
private:
    std::vector<EnumCmdItem> m_items;
};


#endif // _COMMANDS_