# Set the required CMake version
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MotorSim)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Define the directory containing header files
include_directories(include)

# Add the src directory to compile the source files
add_subdirectory(src)

# If there are external libraries, you can link them as follows:
# link_directories(lib)

# Enable testing if there is a tests directory
enable_testing()
add_subdirectory(tests)

