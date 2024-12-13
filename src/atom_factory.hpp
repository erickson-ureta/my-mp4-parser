#pragma once

#include <cstdint>
#include <memory>
#include "atoms.hpp"

namespace AtomFactory
{
    std::shared_ptr<GenericAtom> createAtom(const std::string &atomName, uint8_t *buf, size_t bufSize);
};
