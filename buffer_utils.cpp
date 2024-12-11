#include "buffer_utils.hpp"

uint32_t
BufferUtils::read4BytesIntoU32(std::vector<uint8_t>::const_iterator buf)
{
    return (static_cast<uint32_t>(*buf) << 24) |
           (static_cast<uint32_t>(*(buf+1)) << 16) |
           (static_cast<uint32_t>(*(buf+2)) << 8) |
           (static_cast<uint32_t>(*(buf+3)));
}
