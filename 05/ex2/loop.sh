#!/bin/bash

# Check if two arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <binary> <number_of_times>"
    exit 1
fi

# Store arguments
executable=$1
num_times=$2

# Check if the argument is a valid integer
if ! [[ $num_times =~ ^[0-9]+$ ]]; then
    echo "Error: Argument must be a positive integer."
    exit 1
fi

# Check if the binary file exists and is executable
if [ ! -x $executable ]; then
    echo "Error: Binary file '$executable' not found or is not executable."
    exit 1
fi

# Execute the binary file for the specified number of times
for ((i=0; i<$num_times; i++)); do
    $executable
done
