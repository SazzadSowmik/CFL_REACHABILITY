#!/bin/bash

# Build the project
cd ..
make

# Run the executable with provided input files
cd src
for file in "$@"; do
    ../run "$file"
done