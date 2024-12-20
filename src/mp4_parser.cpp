#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include <unistd.h>

#include "atoms/atom_factory.hpp"
#include "constants.hpp"
#include "logger.hpp"
#include "mp4_parser.hpp"
#include "utils.hpp"

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

    std::vector<std::shared_ptr<GenericAtom>> atoms =
        AtomFactory::createAtomsFromBuf(_mBuffer);
    for (auto &atom: atoms)
    {
        atom->debugPrint();
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

    if (!file.read(reinterpret_cast<char *>(_mBuffer.data()), size))
    {
        return false;
    }

    return true;
}

bool
Mp4Parser::_isValidMp4File()
{
    if (!_mBuffer.size()) return false;
    std::string firstAtomName = AtomFactory::getAtomName(_mBuffer.data());

    return AtomFactory::isValidAtomName(firstAtomName);
}
