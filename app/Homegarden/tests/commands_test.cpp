#include <commands.h>
#include <gtest/gtest.h>

class testEnum : public EnumCommand{
public:
    testEnum(const std::string & name) : EnumCommand(name), m_idx(0){
        
        m_values.push_back(EnumCmdItem{"test1", -1, true});
        m_values.push_back(EnumCmdItem{"test2", 1, true});
        m_values.push_back(EnumCmdItem{"test3", 2, true});
        
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

//test execute
    testEnum cmd3("mine");
    std::string err;
    bool res = cmd1.execute("test1", err);
    ASSERT_EQ(true, res);
    ASSERT_EQ(-1, cmd1.getValue());
    ASSERT_EQ("test1", cmd1.value());
    ASSERT_EQ("", err);

     res = cmd1.execute("test2", err);
    ASSERT_EQ(true, res);
    ASSERT_EQ(1, cmd1.getValue());
    ASSERT_EQ("test2", cmd1.value());
    ASSERT_EQ("", err);

     res = cmd1.execute("test3", err);
    ASSERT_EQ(true, res);
    ASSERT_EQ(2, cmd1.getValue());
    ASSERT_EQ("test3", cmd1.value());
    ASSERT_EQ("", err);

     res = cmd1.execute("", err);
    ASSERT_EQ(false, res);
    ASSERT_EQ(2, cmd1.getValue());
    ASSERT_EQ("test3", cmd1.value());
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
    ASSERT_EQ("test3", cmd1.value());
    ASSERT_TRUE(cmd1.isValid());
    
    cmd1.setValue(3);
    ASSERT_EQ(2, cmd1.getValue());
    ASSERT_EQ("test3", cmd1.value());
    ASSERT_FALSE(cmd1.isValid());
     
}
/*
TEST(CommandsTests, TestStringCommand_1)
{
    std::string myString = "myString";
    std::string myString3 = "myString3";
    StringCommand cmd1("test", myString);
    StringCommand cmd2("test2", myString);
    StringCommand cmd3("test3", myString3);

    const auto value1 = cmd1.value();
    const auto value2 = cmd2.value();
    const auto value3 = cmd3.value();
    ASSERT_EQ("myString", value1);
    ASSERT_EQ(value1, value2);
    ASSERT_NE(value1, value3);
}

TEST(CommandsTests, TestOnOffommand_1)
{
    bool test = false;
    bool test3 = false;
    OnOffCommand cmd1("test", test);
    OnOffCommand cmd2("test2", test);
    OnOffCommand cmd3("test3", test3);

    const auto name1 = cmd1.name();
    const auto name2 = cmd2.name();
    const auto name3 = cmd3.name();
    ASSERT_EQ("test", name1);
    ASSERT_EQ(name1, name3);
    ASSERT_NE(name1, name2);
}

static bool return_true(){
    return true;
}

class testAction : public ActionCommand{
    public:
    testAction(const testAction & other) : ActionCommand(other){}
    testAction(const std::string & name) : ActionCommand(name){}

    virtual ~testAction(){}

protected:
    virtual bool doAction(){return return_true();}
};

TEST(CommandsTests, TestActionCommand_1)
{
    testAction cmd1("test");
    testAction cmd2("test2");
    testAction cmd3("test3");

    const auto name1 = cmd1.name();
    const auto name2 = cmd2.name();
    const auto name3 = cmd3.name();
    ASSERT_EQ("test", name1);
    ASSERT_EQ(name1, name3);
    ASSERT_NE(name1, name2);
}
*/
