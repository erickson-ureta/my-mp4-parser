#pragma once

#include "generic_atom.hpp"

class FreeAtom : public GenericAtom
{
    public:
        FreeAtom(size_t size, uint8_t *rawBuffer)
            : GenericAtom(ATOM_FREE, size, rawBuffer) {}
};
