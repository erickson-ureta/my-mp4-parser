#include <fstream>
#include <iostream>
#include <algorithm>

#include "constants.hpp"
#include "logger.hpp"
#include "mp4_parser.hpp"
#include "buffer_utils.hpp"

Mp4Parser::Mp4Parser(const std::string& fileName)
    : _mFileName(fileName) {}

bool
Mp4Parser::parseMp4File()
{
    if (!_loadFile(_mFileName))
    {
        Logger::get().error("Failed to open file: %s", _mFileName.c_str());
        return false;
    }
    if (!_isValidMp4File())
    {
        Logger::get().error("File is not a valid MP4 file: %s", _mFileName.c_str());
        return false;
    }

    _loopThroughAtoms(_mBuffer.data(), _mBuffer.size());

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

    if (!file.read(reinterpret_cast<char *>(_mBuffer.data()), size))
    {
        return false;
    }

    return true;
}

std::string
Mp4Parser::_getAtomName(const uint8_t *buf)
{
    return BufferUtils::readBytesIntoStr(buf + ATOM_NAME_OFFSET,
                                         ATOM_NAME_LEN);
}

void
Mp4Parser::_loopThroughAtoms(const uint8_t *buf, const size_t buf_size)
{
}

bool
Mp4Parser::_isValidMp4File()
{
    if (!_mBuffer.size()) return false;

    std::string firstAtomName = _getAtomName(_mBuffer.data());
    auto it = std::find(_mKnownAtomNames.begin(), _mKnownAtomNames.end(), firstAtomName);

    return it != _mKnownAtomNames.end();
}
