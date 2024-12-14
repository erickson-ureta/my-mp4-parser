#pragma once

#include "generic_atom.hpp"

class MinfAtom : public GenericAtom
{
    public:
        MinfAtom(size_t size, uint8_t *rawBuffer)
            : GenericAtom(ATOM_MINF, size, rawBuffer)
        {
            _parseRawBufIntoFields();
        }

    protected:
        void _parseRawBufIntoFields()
        {
            _mHasChildren = true;
            _mChildrenOffset = 8;
        }
};
