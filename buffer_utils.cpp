#include <sstream>
#include "buffer_utils.hpp"

namespace BufferUtils
{

uint32_t
read4BytesIntoU32(const std::vector<uint8_t>::const_iterator buf)
{
    return (static_cast<uint32_t>(*buf) << 24) |
           (static_cast<uint32_t>(*(buf+1)) << 16) |
           (static_cast<uint32_t>(*(buf+2)) << 8) |
           (static_cast<uint32_t>(*(buf+3)));
}

std::string
readBytesIntoStr(const std::vector<uint8_t>::const_iterator buf, const size_t &len)
{
    std::stringstream ss;
    for (size_t i = 0; i < len; i++)
    {
        ss << static_cast<char>(buf[i]);
    }

    return ss.str();
}

}
