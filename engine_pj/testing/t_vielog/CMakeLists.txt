cmake_minimum_required(VERSION 3.14)
project(t_vielog)

set(CMAKE_CXX_STANDARD 17)

find_package(vielog REQUIRED)

add_executable(t_vielog src/test_vielog.cpp)

target_link_libraries(t_vielog PRIVATE vielog::vielog)