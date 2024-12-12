#include <sstream>
#include "buffer_utils.hpp"

uint32_t
BufferUtils::read4BytesIntoU32(const uint8_t *buf)
{
    return (static_cast<uint32_t>(*buf) << 24) |
           (static_cast<uint32_t>(*(buf+1)) << 16) |
           (static_cast<uint32_t>(*(buf+2)) << 8) |
           (static_cast<uint32_t>(*(buf+3)));
}

std::string
BufferUtils::readBytesIntoStr(const uint8_t *buf, const size_t &len)
{
    std::stringstream ss;
    for (size_t i = 0; i < len; i++)
    {
        ss << static_cast<char>(buf[i]);
    }

    return ss.str();
}
