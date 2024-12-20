#pragma once

#include "generic_atom.hpp"

class TrakAtom : public GenericAtom
{
    public:
        TrakAtom(size_t size, uint8_t *rawBuffer)
            : GenericAtom(ATOM_TRAK, size, rawBuffer)
        {
            _parseRawBufIntoFields();
        }

    protected:
        void _parseRawBufIntoFields()
        {
            //_mHasChildren = true;
            _mChildrenOffset = 8;
        }
};
