#!/bin/bash

# 0-tool, 1-lib
mode=$1

[ $mode -eq 0 ] && cp build_tool/CMakeLists.txt .. || cp build_lib/CMakeLists.txt ..

pushd ..
[ ! -d build_tmp/ ] && mkdir build_tmp/
[ -d build_tmp/ ] && rm -rf build_tmp/*

cd build_tmp && cmake ..
make install
popd