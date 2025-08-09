# Set the required CMake version
#cmake_minimum_required(VERSION 3.10)

# Set the project name
#project(MotorSim)

# Set the C++ standard
#set(CMAKE_CXX_STANDARD 17)

# Define the directory containing header files
#include_directories(include)

# Add the src directory to compile the source files
#add_subdirectory(src)

# If there are external libraries, you can link them as follows:
# link_directories(lib)

# Enable testing if there is a tests directory
#enable_testing()
#add_subdirectory(tests)


# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MotorSim VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find SFML package (assuming it's installed on your system)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable target
add_executable(MotorSim
    src/main.cpp
    src/motorsimulation.cpp
)

# Link SFML libraries to the executable
target_link_libraries(MotorSim PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# Set the output directory for the executable (optional)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

