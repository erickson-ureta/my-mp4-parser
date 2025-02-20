#pragma once

#include "generic_atom.hpp"

class MdiaAtom : public GenericAtom
{
    public:
        MdiaAtom(size_t size, uint8_t *rawBuffer)
            : GenericAtom(ATOM_MDIA, size, rawBuffer)
        {
            _parseRawBufIntoFields();
        }

    protected:
        void _parseRawBufIntoFields()
        {
            _mChildrenOffset = 8;
        }
};
