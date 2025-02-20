#pragma once

#include "generic_atom.hpp"

class MoovAtom : public GenericAtom
{
    public:
        MoovAtom(size_t size, uint8_t *rawBuffer)
            : GenericAtom(ATOM_MOOV, size, rawBuffer)
        {
            _parseRawBufIntoFields();
        }

    protected:
        void _parseRawBufIntoFields()
        {
            _mChildrenOffset = 8;
        }
};
