cmake_minimum_required(VERSION 3.14)
project(vielog VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Library static
file(GLOB VIELOG_SRC src/*.cpp)
add_library(vielog STATIC ${VIELOG_SRC})
target_include_directories(vielog PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# add_library(vielog INTERFACE) # Header-only
# target_include_directories(vielog INTERFACE
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#     $<INSTALL_INTERFACE:include>
# ))

# Export install target
install(TARGETS vielog
    EXPORT vielogTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Generate Config files
install(EXPORT vielogTargets
    FILE vielogTargets.cmake
    NAMESPACE vielog::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/vielog
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/vielogConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/vielogConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/vielogConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/vielog
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/vielogConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/vielogConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/vielog
)