#include <fstream>
#include <iostream>
#include <algorithm>

#include "constants.hpp"
#include "log.hpp"
#include "my_mp4_parser.hpp"
#include "buffer_utils.hpp"

Logger logger;

Mp4Parser::Mp4Parser(const std::string& fileName)
    : _mFileName(fileName) {}

bool
Mp4Parser::parseMp4File()
{
    if (!_loadFile(_mFileName))
    {
        logger.error("Failed to open file: %s", _mFileName.c_str());
        return false;
    }
    if (!_isValidMp4File())
    {
        logger.error("File is not a valid MP4 file: %s", _mFileName.c_str());
        return false;
    }

    return true;
}

bool
Mp4Parser::_loadFile(const std::string& fileName)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file) return false;

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    _mBuffer.resize(size);

    return static_cast<bool>(file.read(reinterpret_cast<char *>(_mBuffer.data()), size));
}

std::string
Mp4Parser::_getAtomName(const AtomBufPtr &atomBuf)
{
    return BufferUtils::readBytesIntoStr(atomBuf + ATOM_NAME_OFFSET,
                                         ATOM_NAME_LEN);
}

bool
Mp4Parser::_isValidMp4File()
{
    if (!_mBuffer.size()) return false;

    std::string firstAtomName = _getAtomName(_mBuffer.cbegin());
    auto it = std::find(_knownAtomNames.begin(), _knownAtomNames.end(), firstAtomName);

    return it != _knownAtomNames.end();
}

int
main(int argc, char **argv)
{
    if (argc <= 1)
    {
        logger.error("No input files specified.");
        logger.error("usage: ./%s <file1.mp4> <file2.mp4> ... <fileN.mp4>",
                     argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        logger.info("----");
        logger.info("Analyzing file: %s", argv[i]);
        Mp4Parser parser(argv[i]);
        parser.parseMp4File();
    }

    return 0;
}
