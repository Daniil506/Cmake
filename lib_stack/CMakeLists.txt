add_library(stack INTERFACE)

target_include_directories(stack INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(stack INTERFACE cxx_std_14)