#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "atoms/atoms.hpp"
#include "constants.hpp"

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
        bool _isValidMp4File();

};
