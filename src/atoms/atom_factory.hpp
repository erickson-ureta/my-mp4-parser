#pragma once

#include <cstdint>
#include <memory>
#include "atoms.hpp"

namespace AtomFactory
{
    //extern const std::vector<std::string> knownAtomNames;
    std::string getAtomName(const uint8_t *buf);
    bool isValidAtomName(const std::string &atomName);
    std::shared_ptr<GenericAtom> createAtom(const std::string &atomName, uint8_t *buf, size_t bufSize);
    std::vector<std::shared_ptr<GenericAtom>> createAtomsFromBuf(std::vector<uint8_t> &buf, unsigned int recurseLevel);
};
