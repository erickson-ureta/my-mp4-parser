#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace BufferUtils
{
    uint32_t read4BytesIntoU32(const uint8_t *buf);
    std::string readBytesIntoStr(const uint8_t *buf, const size_t &len);
}
