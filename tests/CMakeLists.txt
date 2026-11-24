create_executable_project(AllTests)

target_link_libraries(AllTests
    gtest
    gtest_main
    stack
    queue
)

add_test(NAME AllTests COMMAND AllTests)

target_include_directories(AllTests PRIVATE ${CMAKE_SOURCE_DIR})
