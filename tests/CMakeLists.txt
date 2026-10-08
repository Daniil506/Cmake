create_executable_project(AllTests)
target_link_libraries(AllTests gtest gtest_main)
add_test(NAME AllTests COMMAND AllTests)