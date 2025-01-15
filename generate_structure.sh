#!/bin/bash

# Set the output file name
output_file="project_structure.txt"

# Clear the output file if it exists
> "$output_file"
echo "Output file cleared: $output_file"

# Function to process each file in the project
function process_files() {
    local dir="$1"

    # Find *.cpp, *.h, and *.hpp files, excluding vcpkg and other dependency folders
    find "$dir" -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -not -path "*/out/*" | while read -r file; do
        # Print a debug message for each processed file
        echo "Processing: $file"

        # Append the file name to the output file as a header
        echo "File: $file" >> "$output_file"
        echo "------------------------------------" >> "$output_file"

        # Check if the file contains readable content
        if [ -s "$file" ] && grep -q '[a-zA-Z]' "$file"; then
            # Append the file's content to the output file
            tr -d '\000' < "$file" >> "$output_file" 2>/dev/null
        else
            # Indicate that the file is empty or contains no meaningful content
            echo "File is empty or contains no valid code." >> "$output_file"
        fi

        # Add a separator between files
        echo -e "\n\n" >> "$output_file"
    done
}

# Ensure the script is targeting the current directory
target_folder="."

if [ -d "$target_folder" ]; then
    echo "Generating C++ project structure from: $target_folder"
    process_files "$target_folder"
    echo "Project structure saved to: $output_file"
else
    echo "Error: Target folder $target_folder does not exist."
    exit 1
fi