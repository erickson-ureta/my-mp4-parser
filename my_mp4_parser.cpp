#include <fstream>
#include <iostream>

#include "log.hpp"
#include "my_mp4_parser.hpp"
#include "buffer_utils.hpp"

Logger logger;

Mp4Parser::Mp4Parser(const std::string& fileName)
    : _mFileName(fileName) {}

bool
Mp4Parser::parseMp4File()
{
    logger.info("Analyzing file: %s", _mFileName.c_str());
    if (!_loadFile(_mFileName))
    {
        return false;
    }
    if (!_isValidMp4File())
    {
        return false;
    }

    return true;
}

bool
Mp4Parser::_loadFile(const std::string& fileName)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file)
    {
        logger.error("Failed to open file: %s", fileName.c_str());
        return false;
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    _mBuffer.resize(size);

    if (!file.read(reinterpret_cast<char *>(_mBuffer.data()), size))
    {
        logger.error("Failed to open file: %s", fileName.c_str());
        return false;
    }

    return true;
}

bool
Mp4Parser::_isValidMp4File()
{
    if (!_mBuffer.size())
    {
        logger.error("File is empty: %s", _mFileName.c_str());
        return false;
    }

    size_t atomSize = BufferUtils::read4BytesIntoU32(_mBuffer.cbegin());
    logger.info("atomSize = %zu", atomSize);

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
