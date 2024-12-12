#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace BufferUtils
{

uint32_t read4BytesIntoU32(const std::vector<uint8_t>::const_iterator buf);
std::string readBytesIntoStr(const std::vector<uint8_t>::const_iterator buf, const size_t &len);

}
