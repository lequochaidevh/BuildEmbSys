cmake_minimum_required(VERSION 3.15)
project(modules_camera)

# Create a static library target for the camera module
add_library(camera STATIC
    src/camera_device.cpp
)

# Public include directory (BUILD_INTERFACE for dev builds, INSTALL_INTERFACE for installs)
target_include_directories(camera
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/private_include
)

target_compile_features(camera PUBLIC cxx_std_17)

add_library(modules::camera ALIAS camera)
# If the module depends on core, link it here, for example:
# target_link_libraries(modules::camera PUBLIC core::base)
# --- Install public headers ---
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
)

# --- Install library ---
install(
    TARGETS camera
    EXPORT cameraTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# --- Export CMake target config ---
install(
    EXPORT cameraTargets
    NAMESPACE modules::
    DESTINATION lib/cmake/camera
)