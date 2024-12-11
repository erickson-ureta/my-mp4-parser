#include <iostream>

#include "log.hpp"
#include "my_mp4_parser.hpp"

Logger logger;

Mp4Parser::Mp4Parser(const std::string fileName)
    : _mFileName(fileName) {}

bool
Mp4Parser::parseMp4File()
{
    logger.info("Analyzing file: %s", _mFileName);
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
    if (argc <= 1)
    {
        logger.error("Not enough arguments.");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        Mp4Parser parser(argv[i]);
        parser.parseMp4File();
    }

    return 0;
}
