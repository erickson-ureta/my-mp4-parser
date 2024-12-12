#pragma once

#include <cstdint>
#include <string>
#include <vector>

using AtomBufPtr = std::vector<uint8_t>::const_iterator;

class Mp4Parser
{
    public:
        Mp4Parser(const std::string& fileName);

        bool parseMp4File();

    private:
        // Members
        const std::string _mFileName;
        std::vector<uint8_t> _mBuffer;

        // Helper methods
        bool _loadFile(const std::string& fileName);
        std::string _getAtomName(const AtomBufPtr &atom);
        bool _isValidMp4File();
};
