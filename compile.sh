#!/bin/bash

BUILD=Release

if [ "$#" -gt 0 ]
then
    if [[ "$@" = "debug" ]]
    then
	BUILD=Debug
    else
	echo "Invalid parameter: $@"
	exit 1
    fi
fi

mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=$BUILD .. && make -j2 && cd ..
