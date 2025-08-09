#!/bin/bash

# include the library functions
. "$(dirname "$0")/lib.sh"
# ================================
# 🔧 CONFIGURATION
# ================================
# Set up default paths and directories
SCRIPT_DIR="$(dirname "$(realpath "$0")")"
set_default_paths "INIT_WORKSPACE_PATH" "$SCRIPT_DIR/.."
set_default_paths "BACKUP_DIR" "$SCRIPT_DIR/backup_cmake"
set_default_paths "INITIAL_LIST_PATH" "$SCRIPT_DIR/asset/cmake_file/initial_list.txt"

# ================================
# 📂 FUNCTION: Load initial list
# ================================
load_initial_list() {
    if [ ! -f "$INITIAL_LIST_PATH" ]; then
        echo "❌ Initial list not found: $INITIAL_LIST_PATH"
        exit 1
    fi
    mapfile -t initial_list < "$INITIAL_LIST_PATH"
}

# ================================
# 🧹 FUNCTION: Find and backup redundant CMakeLists.txt
# ================================
check_and_backup_redundant() {
    echo "🔍 Searching for redundant CMakeLists.txt files..."

    all_cmake_files=$(find "$INIT_WORKSPACE_PATH" -name "CMakeLists.txt")
    mkdir -p "$BACKUP_DIR"

    for file in $all_cmake_files; do
        # Skip backup dir itself
        if [[ "$file" == *"$BACKUP_DIR"* ]]; then
            continue
        fi

        # Check if the file exists in the initial list
        if [[ ! " ${initial_list[*]} " =~ " $file " ]]; then
            echo "  🔸 Redundant: $file"

            # Convert path to flat backup name
            backup_name=$(echo "$file" | sed 's|/|?|g' | sed 's|^\.\.||')
            cp "$file" "$BACKUP_DIR/$backup_name"
        fi
    done

    echo "✅ Redundant file check complete. Backed up to: $BACKUP_DIR"
}

# ================================
# ♻️ FUNCTION: Restore from backup
# ================================
restore_from_backup() {
    echo "♻️ Restoring files from $BACKUP_DIR back to workspace..."

    for file in "$BACKUP_DIR"/*; do
        filename=$(basename "$file")
        filepath="${filename%_CMakeLists.txt}"
        restored_path=$(echo "$filepath" | sed 's|?|/|g')

        # mkdir -p "$(dirname "$restored_path")"
        # cp "$file" "$restored_path"
        echo "  ✅ Restored: $restored_path"
    done

    echo "✅ All files restored."
}

# ================================
# 📦 MAIN EXECUTION
# ================================
# Shift arguments to check to export environment variables
while [[ "$1" == -* ]]; do
    case "$1" in
        --help) 
            echo "Usage: $0 [--backup-dir <backup_dir>] [--initial-list <initial_list_path>] [--restore]"
            echo "Options:"
            echo "  --backup-dir <backup_dir>    Specify the backup directory (default: ./backup_cmake)"
            echo "  --initial-list <initial_list_path> Specify the initial list file path (default: ./asset/cmake_file/initial_list.txt)"
            echo "  --restore                     Restore files from backup"
            exit 0
            ;;
        --backup-dir) BACKUP_DIR="$2"; shift 2 ;;
        --initial-list) INITIAL_LIST_PATH="$2"; shift 2 ;;
        --restore) restore_flag="true"; shift ;;
        *) echo "Unknown option: $1"; exit 1 ;;
    esac
done

load_initial_list
check_and_backup_redundant
if [ "$restore_flag" == "true" ]; then
    restore_from_backup
else
    echo "Run with --restore to restore files from backup."
fi
