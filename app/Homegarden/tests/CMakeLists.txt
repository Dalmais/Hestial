include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(commands_test commands_test.cpp)

target_include_directories(commands_test PUBLIC ../src)

target_link_libraries(commands_test
 PRIVATE
  GTest::GTest)

add_test(commands_gtests commands_test)