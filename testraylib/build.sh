#!/bin/bash

BUILD_DIR="build"

# Convert Windows paths to Unix-style for Git Bash
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Clean function
clean_build() {
    echo "Cleaning build artifacts..."
    rm -rf "$BUILD_DIR/CMakeCache.txt" "$BUILD_DIR/CMakeFiles"
}

# Process arguments
CLEAN=0
CLEAN_ALL=0

while [[ $# -gt 0 ]]; do
    case "$1" in
        -clean)
            CLEAN=1
            shift
            ;;
        -clean-all)
            CLEAN_ALL=1
            shift
            ;;
        *)
            echo "Unknown option: $1"
            echo "Usage: $0 [-clean|-clean-all]"
            echo "  -clean     : Clean CMake cache only"
            echo "  -clean-all : Remove entire build directory"
            exit 1
            ;;
    esac
done

# Handle cleaning based on flags
if [ $CLEAN_ALL -eq 1 ]; then
    echo "Removing entire build directory..."
    rm -rf "$BUILD_DIR"
elif [ $CLEAN -eq 1 ]; then
    clean_build
fi

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir -p "$BUILD_DIR"
fi

# Navigate to build directory
cd "$BUILD_DIR" || exit 1

# Run CMake configure
echo "Configuring project..."
if ! cmake .. -G "Visual Studio 17 2022" -A x64; then
    echo "Error: CMake configuration failed"
    cd ..
    exit 1
fi

# Build the project
echo "Building project..."
if ! cmake --build . --config Debug; then
    echo "Error: Build failed"
    cd ..
    exit 1
fi

echo "Build successful!"
echo "Executable location: $BUILD_DIR/Debug/testraylib.exe"

# Return to original directory
cd .. 