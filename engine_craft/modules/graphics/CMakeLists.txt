file(GLOB GRAPHICS_SRC *.cpp)

add_library(module_graphics STATIC ${GRAPHICS_SRC})

target_include_directories(module_graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(module_graphics engine_core)
