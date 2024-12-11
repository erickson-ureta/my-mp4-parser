#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Mp4Parser
{
    public:
        Mp4Parser(const std::string fileName);
    private:
        // Members
        const std::string _mFileName;
        std::vector<uint8_t> _mBuffer;
        // Helper methods
        static bool _isValidMp4File(const std::string file);
};
