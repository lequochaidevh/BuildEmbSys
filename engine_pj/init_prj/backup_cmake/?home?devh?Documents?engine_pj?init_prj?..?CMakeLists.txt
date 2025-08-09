cmake_minimum_required(VERSION 3.15)
project(MyEngineSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ============ OPTIONS ============
option(ENABLE_AI "Enable AI Module" ON)
option(ENABLE_GRAPHICS "Enable Graphics Module" ON)
option(ENABLE_EMBEDDED "Enable Embedded Module" ON)
option(ENABLE_GAME "Enable Game Module" ON)

# ============ OUTPUT DIRS ============
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ============ THIRD PARTY ============
add_subdirectory(third_party)

# ============ CORE ============
add_subdirectory(core)

# ============ PLATFORM ============
add_subdirectory(platform)

# ============ MODULES ============
add_subdirectory(modules)

# ============ APPS ============
add_subdirectory(apps)

# ============ TOOLS & TESTING ============
add_subdirectory(tools)
add_subdirectory(testing)
