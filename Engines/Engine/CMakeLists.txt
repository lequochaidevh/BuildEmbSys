project(ViSolEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)


include(GNUInstallDirs)
include(CMakePackageConfigHelpers)



file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ViSolEngine/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES} )

set(platform "x86_64_u20")

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ViSolEngine>
    $<INSTALL_INTERFACE:include/ViSolEngine>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Vendors/${platform}/include>
    $<INSTALL_INTERFACE:include/Vendors/${platform}/include>
)

add_library(ViSolEngine::ViSolEngine STATIC IMPORTED)

set(_IMPORT_PREFIX "${CMAKE_INSTALL_PREFIX}")

set_target_properties(ViSolEngine::ViSolEngine PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
    INTERFACE_LINK_LIBRARIES spdlog
)

target_compile_definitions(${PROJECT_NAME} PUBLIC ON_VI_ENGINE DYNAMIC_LIB=0 DYNAMIC_BUILD=0)

# TODO: Will delare public and private include dir

# target_include_directories(${PROJECT_NAME} PUBLIC 
# 	${CMAKE_CURRENT_SOURCE_DIR}/ViSolEngine
#     )
#	${CMAKE_SOURCE_DIR}/Vendors/include #add file vendor
    #	${CMAKE_SOURCE_DIR}/Vendors/glfw/include


# target_link_libraries(${PROJECT_NAME} PUBLIC spdlog )
##glfw)

#	${CMAKE_SOURCE_DIR}/Vendors/include/glad/gl.h

# Check CMake version
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.16")
    message(STATUS "CMake version >= 3.16 detected, enabling PCH")
    target_precompile_headers(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ViSolEngine/pch.h
    )
else()
    message(STATUS "CMake version < 3.16 detected, skipping PCH")
endif()

# Export install target
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
# TODO: PUBLIC HEADER FILE

# FILES_MATCHING to not install file cpp
install(DIRECTORY ViSolEngine/core
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)
# Export the targets to a CMake file
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ViSolEngine::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Generate and install the version file
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Configure the config file
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Install the config files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Install spdlog static library manually
install(FILES ${CMAKE_SOURCE_DIR}/Vendors/${platform}/lib/libspdlog.a
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Vendors/${platform}/include/spdlog
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)