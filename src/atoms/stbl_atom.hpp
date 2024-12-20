#pragma once

#include "generic_atom.hpp"

class StblAtom : public GenericAtom
{
    public:
        StblAtom(size_t size, uint8_t *rawBuffer)
            : GenericAtom(ATOM_STBL, size, rawBuffer)
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
