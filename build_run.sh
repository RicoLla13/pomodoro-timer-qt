#!/bin/bash

BUILD_DIR="./build"
SOUND_DIR="./res/sounds"

clean_build () {
    if [[ -d "$BUILD_DIR" ]]; then
        echo "[i] Removing build directory"
        rm -rf "$BUILD_DIR"
    fi
    echo "[i] Generating CMake configuration"
    cmake -S . -B "$BUILD_DIR"
}

if [[ $# -gt 0 ]]; then
    if [[ $1 == "--clean" ]]; then
        echo "[i] Doing a clean build"
        clean_build
    fi
fi

if [[ ! -d "$BUILD_DIR" ]]; then
    echo "[i] Creating build directory"
    clean_build
fi

if [[ ! -d "$BUILD_DIR/sounds" ]]; then
    echo "[i] Copying sound files to build dir"
    cp -r "$SOUND_DIR" "$BUILD_DIR" 
fi

echo "[i] Building project"
cmake --build "$BUILD_DIR"

echo "[i] Running app"
"$BUILD_DIR/pomodoro-qt"
