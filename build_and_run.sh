#!/usr/bin/env bash

BUILDDIR=${PWD}/build

print_err_and_exit() {
    echo "${1}"
    exit 1
}

if [ ! -d "${BUILDDIR}" ]; then
    mkdir -p ${BUILDDIR} || print_err_and_exit "Unable to generate build directory"
fi

pushd ${BUILDDIR} || print_err_and_exit "Can't find build directory"

if [ ! -d "${PWD}/CMakeFiles" ]; then
    cmake -DCMAKE_BUILD_TYPE=Debug .. || print_err_and_exit "CMake was unable to generate build files"
fi

make || print_err_and_exit "Unable to build project"

echo ""

./my_mp4_parser ../media/brandon.mp4
