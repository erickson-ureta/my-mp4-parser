# My MP4 Parser

## About

This is a small program that parses media files using the ISO Base Media File
Format (ISOBMFF), and displaying their metadata to the console. MPEG-4 (or MP4)
is just another name for the ISO standard implementing ISOBMFF.

This is just a little sideproject that basically reimplements already-existing
MP4 parsers, and this is not meant to be used as a serious addition to a
production system (if you do, then you have way bigger problems).

## Building the project

This project requires CMake >= 3.10 and Googletest (which is included as a
submodule for this project).

```
git submodule update --init --recursive
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ..
make all
```

The main executable can be found as `<projectroot>/build/src/my_mp4_parser`.
The unit test executable can be found as `<projectroot>/build/test/my_mp4_parser/test`.

Alternatively, you can use the script file `build_test_run.sh` in the root
directory of this project, as it already does the steps mentioned above, while
also running unit tests, and running the main executable on the test mp4 file
(`<projectroot>/media/brandon.mp4`).

## Usage

This program can take in one or more mp4 files for parsing.

```
./my_mp4_parser <file1.mp4> <file2.mp4> ... <fileN.mp4>
```
