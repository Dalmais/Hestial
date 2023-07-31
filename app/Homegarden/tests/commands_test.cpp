#include <commands.h>
#include <gtest/gtest.h>

TEST(CommandsTests, TestCommandConstructor_1)
{
    Command cmd1("test");
    Command cmd2("test2");
    Command cmd3(cmd1);

    const auto name1 = cmd1.name();
    const auto name2 = cmd2.name();
    const auto name3 = cmd3.name();
    ASSERT_EQ("test", name1);
    ASSERT_EQ(name1, name3);
    ASSERT_NE(name1, name2);
}