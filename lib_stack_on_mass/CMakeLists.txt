create_project_lib(Algorithms)
add_depend(Algorithms StackOnMass ../lib_stack_on_mass)

target_include_directories(Algorithms PRIVATE ${CMAKE_SOURCE_DIR})
