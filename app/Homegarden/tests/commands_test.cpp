#include <commands.h>
#include <gtest/gtest.h>

class testEnum : public EnumCommand{
public:
    testEnum(const std::string & name) : EnumCommand(name, m_items), m_idx(0){
        m_items.push_back(EnumCmdItem{"test1", -1, true});
        m_items.push_back(EnumCmdItem{"test2", 1, true});
        m_items.push_back(EnumCmdItem{"test3", 2, true});
    }

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
    std::vector<EnumCmdItem> m_items;
    int m_idx;
};

TEST(CommandsTests, TestEnumCommand_1)
{
    testEnum cmd1("test");
    testEnum cmd2("test2");
    testEnum cmd3(cmd1);

    const auto name1 = cmd1.name();
    const auto name2 = cmd2.name();
    const auto name3 = cmd3.name();
    ASSERT_EQ("test", name1);
    ASSERT_EQ(name1, name3);
    ASSERT_NE(name1, name2);
}

TEST(CommandsTests, TestStringCommand_1)
{
    std::string myString = "myString";
    std::string myString3 = "myString3";
    StringCommand cmd1("test", myString);
    StringCommand cmd2("test2", myString);
    StringCommand cmd3("test3", myString3);

    const auto name1 = cmd1.name();
    const auto name2 = cmd2.name();
    const auto name3 = cmd3.name();
    ASSERT_EQ("test", name1);
    ASSERT_EQ(name1, name3);
    ASSERT_NE(name1, name2);
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