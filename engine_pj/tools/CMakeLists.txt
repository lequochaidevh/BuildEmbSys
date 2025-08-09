file(GLOB TOOL_SRC *.cpp)

add_executable(profiler_tool ${TOOL_SRC})

target_include_directories(profiler_tool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(profiler_tool engine_core)
