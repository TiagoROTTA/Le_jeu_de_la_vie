#!/bin/bash
if [ $# -ne 2 ]; then
    echo "Please provide both sizeY and sizeX as arguments."
    echo "Usage: $0 sizeY sizeX"
    exit 1
fi

# Set sizeY and sizeX from command line arguments
sizeY=$1
sizeX=$2

# Validate that sizeY and sizeX are positive integers
if ! [[ "$sizeY" =~ ^[0-9]+$ ]] || ! [[ "$sizeX" =~ ^[0-9]+$ ]]; then
    echo "Error: Both sizeY and sizeX must be positive integers."
    exit 1
fi

# Generate the filename based on sizeY and sizeX
filename="${sizeY}x${sizeX}.txt"

# Create the matrix file
{
    echo "$sizeY $sizeX"  # Print matrix size at the top
    for ((i = 0; i < sizeY; i++)); do
        # Print a row of 0s, separated by spaces
        for ((j = 0; j < sizeX; j++)); do
            echo -n "0 "
        done
        echo  # Newline at the end of each row
    done
} > "$filename"

echo "Matrix file '$filename' created successfully."