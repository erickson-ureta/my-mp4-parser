#pragma once

#include "generic_atom.hpp"

class FtypAtom : public GenericAtom
{
    public:
        FtypAtom(size_t size, uint8_t *rawBuffer)
            : GenericAtom(ATOM_FTYP, size, rawBuffer)
        {
            _parseRawBufIntoFields();
        }

        void debugPrint()
        {
            _indentLog("  major_brand = %s", Utils::u32BytesIntoStr(_mMajorBrand).c_str());
            _indentLog("  minor_version = %#x", static_cast<unsigned int>(_mMinorVersion));
            _indentLog("  compatible_brands = ");
            for (const auto &i : _mCompatibleBrands)
            {
                _indentLog("    %s", Utils::u32BytesIntoStr(i).c_str());
            }
        }

    protected:
        uint32_t _mMajorBrand;
        uint32_t _mMinorVersion;
        std::vector<uint32_t> _mCompatibleBrands;

        void _parseRawBufIntoFields()
        {
            uint8_t *cursor = _mRawBuffer.data();

            // Skip size and boxtype fields
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
        }
};
