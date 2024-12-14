#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Utils
{
    std::string generateIndentStr(const unsigned int &indentLevel);
    uint32_t read3BytesIntoU32(const uint8_t *buf);
    uint32_t read4BytesIntoU32(const uint8_t *buf);
    uint64_t read8BytesIntoU64(const uint8_t *buf);
    std::string readBytesIntoStr(const uint8_t *buf, const size_t &len);
    std::string u32BytesIntoStr(const uint32_t value);
    void printBufAsHex(const std::vector<uint8_t> buf, const size_t len);
}
