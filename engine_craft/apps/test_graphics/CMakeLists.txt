add_executable(test_graphics main.cpp)

target_link_libraries(test_graphics
    engine_core
    module_graphics
    platform_linux
)
