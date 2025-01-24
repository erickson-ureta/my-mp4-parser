#include <algorithm>
#include <cstdint>
#include <functional>
#include <unordered_map>

#include "atoms.hpp"
#include "atom_factory.hpp"
#include "../constants.hpp"
#include "../logger.hpp"

using AtomGenerator = std::function<std::shared_ptr<GenericAtom>(size_t, uint8_t*)>;

std::string
AtomFactory::getAtomName(const uint8_t *buf)
{
    return Utils::readBytesIntoStr(buf + ATOM_NAME_OFFSET,
                                         ATOM_NAME_LEN);
}

bool
AtomFactory::isValidAtomName(const std::string &atomName)
{
    static const std::vector<std::string> knownAtomNames = {
        ATOM_FTYP, ATOM_PDIN, ATOM_MOOV, ATOM_MVHD, ATOM_META, ATOM_TRAK,
        ATOM_TKHD, ATOM_TREF, ATOM_EDTS, ATOM_ELST, ATOM_MDIA, ATOM_MDHD,
        ATOM_HDLR, ATOM_ELNG, ATOM_MINF, ATOM_VMHD, ATOM_SMHD, ATOM_HMHD,
        ATOM_STHD, ATOM_NMHD, ATOM_DINF, ATOM_DREF, ATOM_STBL, ATOM_STSD,
        ATOM_STTS, ATOM_CTTS, ATOM_CSLG, ATOM_STSC, ATOM_STSZ, ATOM_STS2,
        ATOM_STCO, ATOM_CO64, ATOM_STSS, ATOM_STSH, ATOM_PADB, ATOM_STDP,
        ATOM_SDTP, ATOM_SBGP, ATOM_SGPD, ATOM_SUBS, ATOM_SAIZ, ATOM_SAIO,
        ATOM_UDTA, ATOM_MVEX, ATOM_MEHD, ATOM_TREX, ATOM_LEVA, ATOM_MOOF,
        ATOM_MFHD, ATOM_TRAF, ATOM_THFD, ATOM_TRUN, ATOM_TFDT, ATOM_MFRA,
        ATOM_TFRA, ATOM_MFRO, ATOM_MDAT, ATOM_FREE, ATOM_SKIP, ATOM_CPRT,
        ATOM_TSEL, ATOM_STRK, ATOM_STRI, ATOM_STRD, ATOM_ILOC, ATOM_IPRO,
        ATOM_SINF, ATOM_FRMA, ATOM_SCHM, ATOM_SCHI, ATOM_IINF, ATOM_XML,
        ATOM_BXML, ATOM_PITM, ATOM_FIIN, ATOM_PAEN, ATOM_FIRE, ATOM_FPAR,
        ATOM_FECR, ATOM_SEGR, ATOM_GITN, ATOM_IDAT, ATOM_IREF, ATOM_MECO,
        ATOM_MERE, ATOM_STYP, ATOM_SIDX, ATOM_SSIX, ATOM_PRFT,
    };
    auto it = std::find(knownAtomNames.begin(),
                        knownAtomNames.end(),
                        atomName);

    return it != knownAtomNames.end();
}

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

std::vector<std::shared_ptr<GenericAtom>>
AtomFactory::createAtomsFromBuf(std::vector<uint8_t> &buf, unsigned int recurseLevel)
{
    std::vector<std::shared_ptr<GenericAtom>> atoms;

    uint8_t *cursor = buf.data();
    while (cursor < cursor + buf.size())
    {
        size_t atomSize = static_cast<size_t>(Utils::read4BytesIntoU32(cursor));
        std::string atomName = getAtomName(cursor);
        if (!isValidAtomName(atomName))
        {
            break;
        }

        std::shared_ptr<GenericAtom> atom = createAtom(atomName, cursor, atomSize);
        if (atom)
        {
            atom->setLogIndentLevel(recurseLevel);
            //atom->debugPrint();

            size_t childrenOffset = atom->getChildrenOffset();
            uint8_t *childCursor = cursor + childrenOffset;
            std::vector<uint8_t> childrenBuffer(childCursor, childCursor + atomSize - childrenOffset);
            auto childAtoms = AtomFactory::createAtomsFromBuf(childrenBuffer, recurseLevel+1);
            atom->setChildrenAtoms(childAtoms);
            //if (atom->hasChildren())
            //{
            //    size_t childrenOffset = atom->getChildrenOffset();
            //    uint8_t *childCursor = cursor + childrenOffset;
            //    std::vector<uint8_t> childrenBuffer(childCursor, childCursor + atomSize - childrenOffset);
            //    auto asd = AtomFactory::createAtomsFromBuf(childrenBuffer, recurseLevel+1);
            //}

            atoms.push_back(atom);
        }

        cursor += atomSize;
    }

    return atoms;
}
