#! /bin/bash

cmake $BUILD_TARGET
cmake --build .

if [[ ! -z $TEST_TARGET ]]; then
    $TEST_TARGET $INPUT_DIR
fi
