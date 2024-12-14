#pragma once

#include "generic_atom.hpp"

class SgpdAtom : public GenericAtom
{
    public:
        SgpdAtom(size_t size, uint8_t *rawBuffer)
            : GenericAtom(ATOM_SGPD, size, rawBuffer)
        {
            _parseRawBufIntoFields();
        }

        void debugPrint()
        {
            _indentLog("  version = %u", static_cast<unsigned int>(_mVersion));
            //_indentLog("  major_brand = %s", Utils::u32BytesIntoStr(_mMajorBrand).c_str());
            //_indentLog("  minor_version = %#x", static_cast<unsigned int>(_mMinorVersion));
            //_indentLog("  compatible_brands = ");
            //for (const auto &i : _mCompatibleBrands)
            //{
            //    _indentLog("    %s", Utils::u32BytesIntoStr(i).c_str());
            //}
        }

    protected:
        void _parseRawBufIntoFields()
        {
            uint8_t *cursor = _mRawBuffer.data();

            //cursor += 8;

            //_mMajorBrand = Utils::read4BytesIntoU32(cursor);
            //cursor += 4;
            //_mMinorVersion = Utils::read4BytesIntoU32(cursor);
            //cursor += 4;
            //while (cursor < _mRawBuffer.data() + _mSize)
            //{
            //    _mCompatibleBrands.push_back(Utils::read4BytesIntoU32(cursor));
            //    cursor += 4;
            //}
        }
};
