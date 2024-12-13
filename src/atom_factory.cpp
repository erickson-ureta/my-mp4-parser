#include "atoms.hpp"
#include "atom_factory.hpp"
#include "constants.hpp"
#include "logger.hpp"

std::shared_ptr<GenericAtom>
AtomFactory::createAtom(const std::string &atomName, uint8_t *buf, size_t bufSize)
{
    if (atomName == ATOM_FTYP)
    {
        Logger::get().info("Generating ftyp atom");
        return std::make_shared<FtypAtom>(bufSize, buf);
    }

    return nullptr;
}
