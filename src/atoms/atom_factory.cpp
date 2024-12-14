#include <cstdint>
#include <functional>
#include <unordered_map>

#include "atoms.hpp"
#include "atom_factory.hpp"
#include "../constants.hpp"
#include "../logger.hpp"

using AtomGenerator = std::function<std::shared_ptr<GenericAtom>(size_t, uint8_t*)>;

std::shared_ptr<GenericAtom>
AtomFactory::createAtom(const std::string &atomName, uint8_t *buf, size_t bufSize)
{
    // Lookup table that uses the atom string name to return a lambda func that creates the appropriate atom
    static const std::unordered_map<std::string, AtomGenerator> atomFactoryMap = {
        {ATOM_FTYP, [](size_t sz, uint8_t *buf){ return std::make_shared<FtypAtom>(sz, buf); }},
        {ATOM_MOOV, [](size_t sz, uint8_t *buf){ return std::make_shared<MoovAtom>(sz, buf); }},
        {ATOM_TRAK, [](size_t sz, uint8_t *buf){ return std::make_shared<TrakAtom>(sz, buf); }},
        {ATOM_MVHD, [](size_t sz, uint8_t *buf){ return std::make_shared<MvhdAtom>(sz, buf); }},
        {ATOM_MDIA, [](size_t sz, uint8_t *buf){ return std::make_shared<MdiaAtom>(sz, buf); }},
        {ATOM_MINF, [](size_t sz, uint8_t *buf){ return std::make_shared<MinfAtom>(sz, buf); }},
        {ATOM_STBL, [](size_t sz, uint8_t *buf){ return std::make_shared<StblAtom>(sz, buf); }},
        {ATOM_SGPD, [](size_t sz, uint8_t *buf){ return std::make_shared<SgpdAtom>(sz, buf); }},
        {ATOM_MDAT, [](size_t sz, uint8_t *buf){ return std::make_shared<MdatAtom>(sz, buf); }},
        {ATOM_FREE, [](size_t sz, uint8_t *buf){ return std::make_shared<FreeAtom>(sz, buf); }},
    };

    auto it = atomFactoryMap.find(atomName);
    if (it != atomFactoryMap.end())
    {
        return it->second(bufSize, buf);
    }

    return nullptr;
}
