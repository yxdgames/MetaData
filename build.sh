#!/bin/bash

if [ $# -gt 0 ]; then
    if [ x$1x = "xReleasex" ]; then
        CMK_BUILD_TYPE=Release
    else
        CMK_BUILD_TYPE=Debug
    fi
else
    CMK_BUILD_TYPE=Debug
fi

mkdir -p _build
cd _build

echo "-- Build by ${CMK_BUILD_TYPE}"

cmake .. \
    -DCMAKE_BUILD_TYPE=${CMK_BUILD_TYPE}

make