file(GLOB PLATFORM_SRC *.cpp)

add_library(platform_linux STATIC ${PLATFORM_SRC})

target_include_directories(platform_linux PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(platform_linux engine_core)
