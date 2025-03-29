#!/bin/bash

echo "---Create CMakeLists---"
# Check if the correct number of arguments is passed
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <project_name> <destination_path>"
  exit 1
fi

# Get the project name and destination path from the arguments
nameProject=$1
destinationPath=$2

# Normalize the projectDir path to remove redundant '/'
destinationPath=$(realpath "$destinationPath")

scriptDir=$(dirname "$(realpath "$0")")
echo "Script is located at: $scriptDir"

# Set the default template path if not provided
templatePath="$scriptDir/templCmakeAll.txt"

# Check if the template file exists
if [ ! -f "$templatePath" ]; then
  echo "Template file $templatePath not found!"
  exit 1
fi

if [ ! -d "$destinationPath" ]; then
  echo "Template file $destinationPath not found!"
  #mkdir -p "$destinationPath"
fi

# Create the CMakeLists.txt file at the destination path based on the template
sed "s/\$nameProject/$nameProject/" "$templatePath" > "$destinationPath/CMakeLists.txt"

# Output a message confirming the file creation
echo "CMakeLists.txt has been created for project $nameProject at $destinationPath"

## chmod +x create_cmake.sh
## ./create_cmake.sh MyCppProject /path/to/CMakeTemplate.txt
