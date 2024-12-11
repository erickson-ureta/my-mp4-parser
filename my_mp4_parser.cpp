#include <iostream>

#include "my_mp4_parser.hpp"

Mp4Parser::Mp4Parser(const std::string fileName)
    : _mFileName(fileName) {}

bool
Mp4Parser::parseMp4File()
{
    return _isValidMp4File(_mFileName);
}

bool
Mp4Parser::_isValidMp4File(const std::string file)
{
    (void) file;
    return true;
}

int
main(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        Mp4Parser parser(argv[i]);
        parser.parseMp4File();
    }

    return 0;
}
