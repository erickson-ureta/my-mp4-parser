#pragma once

#include "generic_atom.hpp"

class MdatAtom : public GenericAtom
{
    public:
        MdatAtom(size_t size, uint8_t *rawBuffer)
            : GenericAtom(ATOM_MDAT, size, rawBuffer) {}
};
