#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace BufferUtils
{
    std::string generateIndentStr(const unsigned int &indentLevel);
    uint32_t read4BytesIntoU32(const uint8_t *buf);
    std::string readBytesIntoStr(const uint8_t *buf, const size_t &len);
    std::string u32BytesIntoStr(const unsigned int value);
}
