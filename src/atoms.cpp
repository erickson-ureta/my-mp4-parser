#include <string>

#include "atoms.hpp"
#include "utils.hpp"
#include "logger.hpp"

void
FtypAtom::_parseRawBufIntoFields()
{
    uint8_t *cursor = _mRawBuffer;

    _mMajorBrand = BufferUtils::read4BytesIntoU32(cursor);
    cursor += 4;
    _mMinorVersion = BufferUtils::read4BytesIntoU32(cursor);
    cursor += 4;
    while (cursor < _mRawBuffer + _mSize)
    {
        _mCompatibleBrands.push_back(BufferUtils::read4BytesIntoU32(cursor));
        cursor += 4;
    }

    _mHasChildren = false;
    _mChildrenOffset = 0;
}

void
FtypAtom::debugPrint(const unsigned int indentLevel)
{
    std::string indentStr = BufferUtils::generateIndentStr(indentLevel);
    Logger::get().info("%s  major_brand = %u", indentStr.c_str(), static_cast<unsigned int>(_mMajorBrand));
    Logger::get().info("%s  minor_version = %u", indentStr.c_str(), static_cast<unsigned int>(_mMinorVersion));
    Logger::get().info("%s  compatible_brands = ", indentStr.c_str());
    for (const auto &i : _mCompatibleBrands)
    {
        Logger::get().info("%s    %u", indentStr.c_str(), static_cast<unsigned int>(i));
    }
}
