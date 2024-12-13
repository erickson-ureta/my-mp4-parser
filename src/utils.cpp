#include <iomanip>
#include <sstream>

#include "logger.hpp"
#include "utils.hpp"

std::string
Utils::generateIndentStr(const unsigned int &indentLevel)
{
    std::stringstream ss;
    for (auto i = 0; i < indentLevel; i++)
    {
        ss << "  ";
    }

    return ss.str();
}

uint32_t
Utils::read4BytesIntoU32(const uint8_t *buf)
{
    return (static_cast<uint32_t>(*buf) << 24) |
           (static_cast<uint32_t>(*(buf+1)) << 16) |
           (static_cast<uint32_t>(*(buf+2)) << 8) |
           (static_cast<uint32_t>(*(buf+3)));
}

std::string
Utils::readBytesIntoStr(const uint8_t *buf, const size_t &len)
{
    std::stringstream ss;
    for (size_t i = 0; i < len; i++)
    {
        ss << static_cast<char>(buf[i]);
    }

    return ss.str();
}

std::string
Utils::u32BytesIntoStr(const uint32_t value)
{
    char chars[4];
    chars[0] = static_cast<char>((value >> 24) & 0xFF);
    chars[1] = static_cast<char>((value >> 16) & 0xFF);
    chars[2] = static_cast<char>((value >> 8) & 0xFF);
    chars[3] = static_cast<char>(value & 0xFF);

    return std::string(chars);
}

void
Utils::printBufAsHex(const std::vector<uint8_t> buf, const size_t len)
{
    std::stringstream ss;

    for (auto i = 0; i < len; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(buf[i]);
        if (i < len - 1)
        {
            ss << " ";
        }
    }

    Logger::get().info(ss.str().c_str());
}
