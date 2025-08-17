#!/bin/bash

. "$(dirname "$0")/lib.sh"
source "$(dirname "$0")/setup_env.sh"

# This script builds all components of the ViSolEngine project.
printf "${BLUE}${BOLD}%-10sBuilding all components of the ViSolEngine project.${ENDLINE}${NC}"
echo

cd "$CMAKE_ROOT_DIR" || {
    echo -e "${RED}ERROR: Could not change to build directory: $CMAKE_BUILD_DIR${NC}"
    exit 1
}

mkdir -p ./tmp/ViSolEngineInstall
cmake -B build -DCMAKE_INSTALL_PREFIX="./tmp/ViSolEngineInstall"
cmake --build build
cmake --install build

# if [ ! -f "CMakeCache.txt" ]; then
#     echo -e "${YELLOW}CMake cache not found. Running cmake to configure project...${NC}"
#     cmake "$CMAKE_BUILD_DIR" -DCMAKE_INSTALL_PREFIX="$CMAKE_INSTALL_DIR" || {
#         echo -e "${RED}ERROR: CMake configuration failed.${NC}"
#         exit 1
#     }
# fi

# core_build=$(( $(nproc) - 3 ))
# cmake --build . --preset linux-debug -- -j "$core_build" || {
# # cmake --build . --target all -- -j "$core_build" || {
#     echo -e "${RED}ERROR: Build failed.${NC}"
#     exit 1
# }

printf "${GREEN}${BOLD}%-10sBuild completed successfully.${ENDLINE}${NC}"
echo
