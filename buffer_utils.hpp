#pragma once

#include <cstdint>
#include <vector>

namespace BufferUtils
{

uint32_t read4BytesIntoU32(std::vector<uint8_t>::const_iterator buf);

}
