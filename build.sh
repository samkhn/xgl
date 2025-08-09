#!/bin/bash
#set -x

pushd $(dirname $0)

PROJECT_DIR="$(echo "$(pwd)" | sed -e 's/^\/home\/samiur\/src\///')"
SOURCE_DIR=$(pwd)
BUILD_DIR=$HOME/build/$PROJECT_DIR/

if [ ! -d "$BUILD_DIR" ]; then
	mkdir -p $BUILD_DIR
	cmake -DCMAKE_BUILD_TYPE=Debug -B $BUILD_DIR -G Ninja -S $SOURCE_DIR
	if [ $? -ne 0 ]; then
	    echo "CMake build failed; deleting $BUILD_DIR"
	    rm -rf $BUILD_DIR
	fi
fi

cmake --build $BUILD_DIR
$BUILD_DIR/game

popd
