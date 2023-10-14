#include <commands.h>
#include <gtest/gtest.h>

class testEnum : public EnumCommand{
public:
    testEnum(const std::string & name) : EnumCommand(name), m_idx(0){
        
        m_values.push_back(EnumCmdItem{"test1", -1, true});
        m_values.push_back(EnumCmdItem{"test2", 1, true});
        m_values.push_back(EnumCmdItem{"test3", 2, false});
    }

    virtual ~testEnum(){}

    bool setValue(const uint32_t idx){
        if((idx != -1 ) && (idx != 1 ) && (idx != 2 )){
            return false;
        }
        m_idx = idx;
        return true;
    }

    int getValue(){
        return m_idx;
    }

private:
    int m_idx;
};

TEST(CommandsTests, TestEnumCommand_1)
{
    testEnum cmd1("testEnum1");
    testEnum cmd2(cmd1);

//test name
    ASSERT_EQ("testEnum1", cmd1.name());
    ASSERT_EQ(cmd1.name(), cmd2.name());

// test help
    ASSERT_EQ("testEnum1 [ENUM [test1] [test2] (test3)]", cmd1.help());

//test execute
    testEnum cmd3("mine");
    std::string err;
    bool res = cmd1.execute("test1", err);
    ASSERT_TRUE(res);
    ASSERT_EQ(-1, cmd1.getValue());
    ASSERT_EQ("test1", cmd1.value());
    ASSERT_EQ("", err);

    res = cmd1.execute("test2", err);
    ASSERT_TRUE(res);
    ASSERT_EQ(1, cmd1.getValue());
    ASSERT_EQ("test2", cmd1.value());
    ASSERT_EQ("", err);

    res = cmd1.execute("test3", err);
    ASSERT_FALSE(res);
    ASSERT_EQ(1, cmd1.getValue());
    ASSERT_EQ("test2", cmd1.value());
    ASSERT_EQ("value is not available", err);

    res = cmd1.execute("", err);
    ASSERT_FALSE(res);
    ASSERT_EQ(1, cmd1.getValue());
    ASSERT_EQ("test2", cmd1.value());
    ASSERT_EQ("Invalid value", err);

//test set value
    cmd1.setValue(-1);
    ASSERT_EQ(-1, cmd1.getValue());
    ASSERT_EQ("test1", cmd1.value());
    ASSERT_TRUE(cmd1.isValid());

    cmd1.setValue(0);
    ASSERT_EQ(-1, cmd1.getValue());
    ASSERT_EQ("test1", cmd1.value());
    ASSERT_FALSE(cmd1.isValid());

    cmd1.setValue(1);
    ASSERT_EQ(1, cmd1.getValue());
    ASSERT_EQ("test2", cmd1.value());
    ASSERT_TRUE(cmd1.isValid());

    cmd1.setValue(2);
    ASSERT_EQ(2, cmd1.getValue());
    ASSERT_EQ("UNAVAILABLE", cmd1.value());
    ASSERT_FALSE(cmd1.isValid());
    
    cmd1.setValue(3);
    ASSERT_EQ(2, cmd1.getValue());
    ASSERT_EQ("UNAVAILABLE", cmd1.value());
    ASSERT_FALSE(cmd1.isValid());   
}

TEST(CommandsTests, TestStringCommand_1)
{
    std::string myString = "myString";
    std::string myString3 = "myString3";
    StringCommand cmd1("testString1", myString);
    StringCommand cmd2(cmd1);

//test name
    ASSERT_EQ("testString1", cmd1.name());
    ASSERT_EQ(cmd1.name(), cmd2.name());

// test help
    ASSERT_EQ("testString1 [STR(32)]", cmd1.help());

//test execute
    std::string err;
    bool res = cmd1.execute("", err);
    ASSERT_TRUE(res);
    ASSERT_EQ("UNDEFINED", cmd1.value());
    ASSERT_EQ("", err);

    StringCommand cmd3("mine", myString3, 6);
    res = cmd3.execute("test2", err);
    ASSERT_TRUE(res);
    ASSERT_EQ("test2", cmd3.value());
    ASSERT_EQ("", err);

    res = cmd3.execute("testtroplong", err);
    ASSERT_FALSE(res);
    ASSERT_EQ("test2", cmd3.value());
    ASSERT_EQ("Input size too big", err);

}

TEST(CommandsTests, TestOnOffommand_1)
{
    bool test = false;
    OnOffCommand cmd1("testOnOff", test);
    OnOffCommand cmd2(cmd1);

// name
    ASSERT_EQ("testOnOff", cmd1.name());
    ASSERT_EQ(cmd1.name(), cmd2.name());

// test help
    ASSERT_EQ("testOnOff [ENUM [OFF] [ON]]", cmd1.help());

//test execute
    std::string err;
    bool res = cmd1.execute("ON", err);
    ASSERT_TRUE(res);
    ASSERT_EQ("ON", cmd1.value());
    ASSERT_EQ("", err);
    
    res = cmd1.execute("OFF", err);
    ASSERT_TRUE(res);
    ASSERT_EQ("OFF", cmd1.value());
    ASSERT_EQ("", err);
    
    res = cmd1.execute("BAD", err);
    ASSERT_FALSE(res);
    ASSERT_EQ("OFF", cmd1.value());
    ASSERT_EQ("Invalid value", err);

}

static bool value_test = false;
static bool return_true(){
    value_test = true;
    return true;
}

class TestAction : public ActionCommand{
    public:
    TestAction(const TestAction & other) : ActionCommand(other){}
    TestAction(const std::string & name) : ActionCommand(name){}

    virtual ~TestAction(){}

protected:
    virtual bool doAction(){return return_true();}
};

TEST(CommandsTests, TestActionCommand_1)
{
    TestAction cmd1("testAction");
    TestAction cmd2(cmd1);

// name
    ASSERT_EQ("testAction", cmd1.name());
    ASSERT_EQ(cmd1.name(), cmd2.name());

// test help
    ASSERT_EQ("testAction [ENUM [APPLY]]", cmd1.help());

//test execute
    std::string err;
    
    bool res = cmd1.execute("BAD", err);
    ASSERT_FALSE(res);
    ASSERT_FALSE(value_test);
    ASSERT_EQ("UNDEFINED", cmd1.value());
    ASSERT_EQ("Invalid value", err);

    res = cmd1.execute("APPLY", err);
    ASSERT_TRUE(res);
    ASSERT_TRUE(value_test);
    ASSERT_EQ("UNDEFINED", cmd1.value());
    ASSERT_EQ("", err);
}

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
    }

    virtual ~TestNumber(){}

protected:
    virtual std::vector<double> getValue(){
        return number;
    }
    virtual void setValue(std::vector<double> value){
        number = value;
    }

private:
    std::vector<double> number;
};

TEST(CommandsTests, TestNumberCommand_1)
{
    TestNumber cmd1("testNumber");
    TestNumber cmd2(cmd1);

// name
    ASSERT_EQ("testNumber", cmd1.name());
    ASSERT_EQ(cmd1.name(), cmd2.name());

// test help
    ASSERT_EQ("testNumber [NUM DEC[0:1:255];DEC[-255:1:0];HEX[0x0:0x1:0xff];FLOAT[0.0:1.2:42.0];FLOAT[-42.0:1.3:-1.0]]", cmd1.help());

//test execute
    std::string err;
    
    bool res = cmd1.execute("192;-123;0xdd;21.3;", err);
    ASSERT_FALSE(res);
    ASSERT_EQ("INVALID", cmd1.value());
    ASSERT_EQ("Bad parameters number: 4/5", err);

    res = cmd1.execute("192;-123;0xdd;21.3;1.5;77", err);
    ASSERT_FALSE(res);
    ASSERT_EQ("INVALID", cmd1.value());
    ASSERT_EQ("Bad parameters number: 6/5", err);

    res = cmd1.execute("192;-123;ddd;21.4;-24.2", err);
    ASSERT_FALSE(res);
    ASSERT_EQ("INVALID", cmd1.value());
    ASSERT_EQ("Invalid value", err);

    res = cmd1.execute("192;-123;0xdd;21.3;-11.85", err);
    ASSERT_TRUE(res);
    ASSERT_TRUE(value_test);
    ASSERT_EQ("192;-123;0xdd;21.3;-11.8", cmd1.value());
    ASSERT_EQ("", err);

}
