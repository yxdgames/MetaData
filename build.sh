#!/bin/bash

mkdir -p _build
cd _build

cmake .. \
    -DCMAKE_BUILD_TYPE=Debug

make