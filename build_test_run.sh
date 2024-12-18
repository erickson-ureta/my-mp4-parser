#!/usr/bin/env bash

ROOT_DIR=${PWD}
BUILDDIR=${ROOT_DIR}/build

print_err_and_exit() {
    echo "==========================================="
    echo "${1}"
    exit 1
}

git submodule update --init --recursive

if [ ! -d "${BUILDDIR}" ]; then
    mkdir -p ${BUILDDIR} || print_err_and_exit "Unable to generate build directory"
fi
pushd ${BUILDDIR} > /dev/null || print_err_and_exit "Can't find build directory"

if [ ! -d "${PWD}/CMakeFiles" ]; then
    cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" .. || print_err_and_exit "CMake was unable to generate build files"
fi
make all || print_err_and_exit "Unable to build project"
echo ""

echo "==========================================="
echo "Running unit tests"
pushd test > /dev/null
echo ${PWD}
./my_mp4_parser_test || print_err_and_exit "Unit testing failed!"
echo ""

#echo "==========================================="
#echo "Running main program"
#popd > /dev/null
#pushd src > /dev/null
#echo ""
#./my_mp4_parser ${ROOT_DIR}/media/brandon.mp4
