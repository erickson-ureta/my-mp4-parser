#include <cstdint>
#include <functional>
#include <unordered_map>

#include "atoms.hpp"
#include "atom_factory.hpp"
#include "constants.hpp"
#include "logger.hpp"

using AtomGenerator = std::function<std::shared_ptr<GenericAtom>(size_t, uint8_t*)>;

std::shared_ptr<GenericAtom>
AtomFactory::createAtom(const std::string &atomName, uint8_t *buf, size_t bufSize)
{
    static const std::unordered_map<std::string, AtomGenerator> atomFactoryMap = {
        {ATOM_FTYP, [](size_t size, uint8_t *rawBuffer){ return std::make_shared<FtypAtom>(size, rawBuffer); }}
    };

    auto it = atomFactoryMap.find(atomName);
    if (it != atomFactoryMap.end())
    {
        return it->second(bufSize, buf);
    }

    return nullptr;
}
