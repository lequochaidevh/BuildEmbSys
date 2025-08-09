file(GLOB TEST_SRC *.cpp)

add_executable(unit_tests ${TEST_SRC})
target_include_directories(unit_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(unit_tests
    engine_core
    module_camera
    module_game
)
