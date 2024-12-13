#include <string>

#include "atoms.hpp"
#include "utils.hpp"
#include "logger.hpp"

void
FtypAtom::_parseRawBufIntoFields()
{
    uint8_t *cursor = _mRawBuffer;

    // Skip version/flags field

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
    //_indentLog("  major_brand = %u", static_cast<unsigned int>(_mMajorBrand));
    _indentLog("  major_brand = %s", BufferUtils::u32BytesIntoStr(_mMajorBrand));
    _indentLog("  minor_version = %u", static_cast<unsigned int>(_mMinorVersion));
    _indentLog("  compatible_brands = ");
    for (const auto &i : _mCompatibleBrands)
    {
        _indentLog("    %u", static_cast<unsigned int>(i));
    }
}
