#!/bin/bash

# Functions set default paths and directories if not existing
# parameters:
#   $1: variable name to set
#   $2: default value if variable is not set
set_default_paths() {
    local var_name="$1"
    local default_value="$2"

    if [[ -z "${!var_name}" ]]; then
        eval "$var_name=\"$default_value\""
    fi
    export "$var_name"
}

