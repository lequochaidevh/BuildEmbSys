#!/bin/bash
echo "---Create Project---"
# Check the number of arguments passed
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <project_name> <project_location>"
  exit 1
fi

# Get the parameters from the command line arguments
nameProject=$1
projectDir=$2

# Normalize the projectDir path to remove redundant '/'
projectDir=$(realpath "$projectDir")

scriptDir=$(dirname "$(realpath "$0")")
echo "Script is located at: $scriptDir"

# Create the main project directory at the specified location
mkdir -p "$projectDir/$nameProject"

# Create subdirectories for the project directly at the project directory
mkdir -p "$projectDir/$nameProject/src"
mkdir -p "$projectDir/$nameProject/include"
mkdir -p "$projectDir/$nameProject/lib"
mkdir -p "$projectDir/$nameProject/build"
mkdir -p "$projectDir/$nameProject/tests"
mkdir -p "$projectDir/$nameProject/docs"

# Create a README file for the project
touch "$projectDir/$nameProject/README.md"

# Call create_cmake.sh script without needing to cd
result=$(bash "$scriptDir/create_cmake.sh" "$nameProject" "$projectDir/$nameProject")
echo -e "$result"

# Output a message indicating the project has been created
echo "Project $nameProject has been created at $projectDir/$nameProject"

## chmod +x create_project.sh
## ./create_project.sh MyCppProject /path/to/your/desired/location
