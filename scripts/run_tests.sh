#!/usr/bin/env bash

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build"

echo "Configuring project..."
cmake -S "$PROJECT_ROOT" -B "$BUILD_DIR"

echo
echo "Building project..."
cmake --build "$BUILD_DIR"

echo
echo "Running tests..."
cd "$BUILD_DIR"
ctest --output-on-failure
