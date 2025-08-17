cmake_minimum_required(VERSION 3.15)
project(camera_viewer)

add_executable(camera_viewer main.cpp)
# Link với module camera (target đặt ở module CMakeLists)
target_link_libraries(camera_viewer PRIVATE modules::camera)
target_compile_features(camera_viewer PRIVATE cxx_std_17)
