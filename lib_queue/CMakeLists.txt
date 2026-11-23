add_library(queue INTERFACE)

target_include_directories(queue INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(queue INTERFACE cxx_std_14)