#pragma once

#include "generic_atom.hpp"

class MvhdAtom : public GenericAtom
{
    public:
        MvhdAtom(size_t size, uint8_t *rawBuffer)
            : GenericAtom(ATOM_MVHD, size, rawBuffer)
        {
            _parseRawBufIntoFields();
        }

        void debugPrint()
        {
            _indentLog("  version = %u", static_cast<unsigned int>(_mVersion));
            unsigned int creationTime =
                static_cast<unsigned int>((_mVersion == 1) ? _mCreationTimeV1 : _mCreationTime);
            unsigned int modificationTime =
                static_cast<unsigned int>((_mVersion == 1) ? _mModificationTimeV1 : _mModificationTime);
            unsigned int timescale =
                static_cast<unsigned int>(_mTimescale);
            unsigned int duration =
                static_cast<unsigned int>((_mVersion == 1) ? _mDurationV1 : _mDuration);
            _indentLog("  creation_time = %u", creationTime);
            _indentLog("  modification_time = %u", modificationTime);
            _indentLog("  timescale = %u", timescale);
            _indentLog("  duration = %u", duration);
        }

    protected:
        // Version 0 fields
        uint32_t _mCreationTime;
        uint32_t _mModificationTime;
        uint32_t _mTimescale; // Also exists in version 1 as a 32-bit field
        uint32_t _mDuration;
        // Version 1 fields
        uint64_t _mCreationTimeV1;
        uint64_t _mModificationTimeV1;
        // 32-bit timescale field in between
        uint64_t _mDurationV1;

        void _parseRawBufIntoFields()
        {
            uint8_t *cursor = _mRawBuffer.data();

            // Skip size, boxtype and version/flags fields
            cursor += 12;

            if (_mVersion == 1)
            {
                _mCreationTimeV1 = Utils::read8BytesIntoU64(cursor);
                cursor += 8;
                _mModificationTimeV1 = Utils::read8BytesIntoU64(cursor);
                cursor += 8;
                _mTimescale = Utils::read4BytesIntoU32(cursor);
                cursor += 4;
                _mDurationV1 = Utils::read8BytesIntoU64(cursor);
            }
            else // version 0
            {
                _mCreationTime = Utils::read4BytesIntoU32(cursor);
                cursor += 4;
                _mModificationTime = Utils::read4BytesIntoU32(cursor);
                cursor += 4;
                _mTimescale = Utils::read4BytesIntoU32(cursor);
                cursor += 4;
                _mDuration = Utils::read4BytesIntoU32(cursor);
            }
        }
};
