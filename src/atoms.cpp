#include <string>

#include "atoms.hpp"
#include "buffer_utils.hpp"
#include "logger.hpp"

void
FtypAtom::_parseRawBufIntoFields()
{
    Logger::get().info("--- HELLO WORLD! ---");
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
FtypAtom::debugPrint()
{
    Logger::get().info("major_brand = %u", static_cast<unsigned int>(_mMajorBrand));
    Logger::get().info("minor_version = %u", static_cast<unsigned int>(_mMinorVersion));
    Logger::get().info("compatible_brands = ");
    for (const auto &i : _mCompatibleBrands)
    {
        Logger::get().info("%u", static_cast<unsigned int>(i));
    }
}
