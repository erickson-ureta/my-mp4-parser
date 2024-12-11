#include <iostream>

#include "my_mp4_parser.hpp"

Mp4Parser::Mp4Parser(const std::string fileName)
    : _mFileName(fileName) {}

bool
Mp4Parser::_isValidMp4File(const std::string file)
{
    (void) file;
    return true;
}

int
main(int argc, char **argv)
{
    std::cout << "Hello" << std::endl;

    (void) argc;
    (void) argv;

    return 0;
}
