#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include <unistd.h>

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

    _loopThroughAtoms(_mBuffer.data(), _mBuffer.size(), 0);

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

std::string
Mp4Parser::_generateIndentStr(const unsigned int &recurseLevel)
{
    std::stringstream ss;
    for (auto i = 0; i < recurseLevel; i++)
    {
        ss << "  ";
    }

    return ss.str();
}

std::shared_ptr<GenericAtom>
Mp4Parser::_createAtomFromBuf(uint8_t *buf, size_t bufSize)
{
    if (!buf)
    {
        return nullptr;
    }

    std::string atomName = _getAtomName(buf);
    //switch (atomName)
    //{
    //}

    return nullptr;
}

void
Mp4Parser::_loopThroughAtoms(uint8_t *buf, const size_t bufSize,
                             const unsigned int &recurseLevel)
{
    uint8_t *cursor = buf;
    size_t cursorPos = 0;
    while (cursorPos < bufSize)
    {
        Logger::get().info("cursor_pos = %zu", cursorPos);

        size_t atomSize = static_cast<size_t>(BufferUtils::read4BytesIntoU32(cursor));
        std::string atomName = _getAtomName(cursor);
        std::string indent = _generateIndentStr(recurseLevel);
        Logger::get().info("%s[%s] (%zu bytes)", indent.c_str(), atomName.c_str(), atomSize);

        usleep(200000);

        // TODO: process atom here
        std::shared_ptr<GenericAtom> atom = _createAtomFromBuf(cursor, atomSize);
        bool atomHasChildren = true;
        bool atomChildrenOffset = 8;

        if (atomHasChildren)
        {
            _loopThroughAtoms(cursor+atomChildrenOffset, atomSize, recurseLevel+1);
        }

        cursor += atomSize;
        cursorPos += atomSize;
    }
}

bool
Mp4Parser::_isValidMp4File()
{
    if (!_mBuffer.size()) return false;

    std::string firstAtomName = _getAtomName(_mBuffer.data());
    auto it = std::find(_mKnownAtomNames.begin(), _mKnownAtomNames.end(), firstAtomName);

    return it != _mKnownAtomNames.end();
}
