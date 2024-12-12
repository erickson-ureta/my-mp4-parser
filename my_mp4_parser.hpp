#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "constants.hpp"

using AtomBufPtr = std::vector<uint8_t>::const_iterator;

class Mp4Parser
{
    public:
        Mp4Parser(const std::string& fileName);

        bool parseMp4File();

    private:
        // Members
        const std::string _mFileName;
        std::vector<uint8_t> _mBuffer;

        // Helper methods
        bool _loadFile(const std::string& fileName);
        std::string _getAtomName(const AtomBufPtr &atomBuf);
        bool _isValidMp4File();

        // List of known atom names
        const std::vector<std::string> _knownAtomNames = {
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
};
