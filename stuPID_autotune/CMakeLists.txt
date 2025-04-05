# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)
# Set the project name (PN)
set(PN stuPID_autotune)
# Set the project name and version
project(stuPID_autotune VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Find SFML package (assuming it's installed on your system)
#find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable target
add_executable(${PN}
    src/main.cpp
    src/pid_autotune.cpp
)

# Link SFML libraries to the executable
#target_link_libraries(${PN} PRIVATE)

# Set the output directory for the executable (optional)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

