#!/bin/bash

#Syntax:
#./clear.sh test_out

# Check if the folder path is provided as an argument
if [ -z "$1" ]; then
  echo "Usage: $0 <folder_path>"
  exit 1
fi

FOLDER_PATH="$1"

# Confirm the folder exists
if [ ! -d "$FOLDER_PATH" ]; then
  echo "Error: Folder '$FOLDER_PATH' does not exist."
  exit 1
fi

rm -rf "$FOLDER_PATH"

# Check if the operation succeeded
if [ $? -eq 0 ]; then
  echo "Folder '$FOLDER_PATH' and its contents have been deleted."
else
  echo "Error: Failed to delete the folder '$FOLDER_PATH'."
fi