#!/bin/bash

# Build the project
cd ..
make

# Run the executable with all provided arguments
cd src
../run "$@"