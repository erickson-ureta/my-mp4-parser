#include <string>

#include "atoms.hpp"
#include "utils.hpp"
#include "logger.hpp"

void
FtypAtom::_parseRawBufIntoFields()
{
    uint8_t *cursor = _mRawBuffer.data();

    // Skip version/flags field
    cursor += 8;

    _mMajorBrand = Utils::read4BytesIntoU32(cursor);
    cursor += 4;
    _mMinorVersion = Utils::read4BytesIntoU32(cursor);
    cursor += 4;
    while (cursor < _mRawBuffer.data() + _mSize)
    {
        _mCompatibleBrands.push_back(Utils::read4BytesIntoU32(cursor));
        cursor += 4;
    }

    _mHasChildren = false;
    _mChildrenOffset = 0;
}

void
FtypAtom::debugPrint()
{
    _indentLog("  major_brand = %s", Utils::u32BytesIntoStr(_mMajorBrand).c_str());
    _indentLog("  minor_version = %#x", static_cast<unsigned int>(_mMinorVersion));
    _indentLog("  compatible_brands = ");
    for (const auto &i : _mCompatibleBrands)
    {
        _indentLog("    %s", Utils::u32BytesIntoStr(i).c_str());
    }
}

void
MoovAtom::_parseRawBufIntoFields()
{
    _mHasChildren = true;
    _mChildrenOffset = 8;
}
