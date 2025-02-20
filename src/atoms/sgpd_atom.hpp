#pragma once

#include <memory>
#include "generic_atom.hpp"

class SampleGroupDescriptionEntry
{
    public:
        SampleGroupDescriptionEntry(uint32_t groupingType) :
            _mGroupingType(groupingType) {}

    protected:
        uint32_t _mGroupingType;
};

class VisualSampleGroupEntry : public SampleGroupDescriptionEntry
{
    public:
        VisualSampleGroupEntry(uint32_t groupingType) :
            SampleGroupDescriptionEntry(groupingType) {}
};

class AudioSampleGroupEntry : public SampleGroupDescriptionEntry
{
    public:
        AudioSampleGroupEntry(uint32_t groupingType) :
            SampleGroupDescriptionEntry(groupingType) {}
};

class HintSampleGroupEntry : public SampleGroupDescriptionEntry
{
    public:
        HintSampleGroupEntry(uint32_t groupingType) :
            SampleGroupDescriptionEntry(groupingType) {}
};

class SubtitleSampleGroupEntry : public SampleGroupDescriptionEntry
{
    public:
        SubtitleSampleGroupEntry(uint32_t groupingType) :
            SampleGroupDescriptionEntry(groupingType) {}
};

class TextSampleGroupEntry : public SampleGroupDescriptionEntry
{
    public:
        TextSampleGroupEntry(uint32_t groupingType) :
            SampleGroupDescriptionEntry(groupingType) {}
};

class SgpdAtom : public GenericAtom
{
    public:
        SgpdAtom(size_t size, uint8_t *rawBuffer)
            : GenericAtom(ATOM_SGPD, size, rawBuffer)
        {
            _parseRawBufIntoFields();
        }

        void debugPrint() override
        {
            _printAtomNameAndSize();
            _indentLog("  version = %u", static_cast<unsigned int>(_mVersion));
            _indentLog("  grouping_type = %s", Utils::u32BytesIntoStr(_mGroupingType).c_str());
            if (_mVersion == 1)
            {
                _indentLog("  default_length = %u", static_cast<unsigned int>(_mDefaultLength));
            }
            if (_mVersion == 2)
            {
                _indentLog("  default_sample_description_index = %u",
                           static_cast<unsigned int>(_mDefaultSampleDescriptionIndex));
            }
            _indentLog("  entry_count = %u", static_cast<unsigned int>(_mEntryCount));
            _indentLog("  entries:");
            for (auto i = 0; i < static_cast<unsigned int>(_mEntryCount); i++)
            {
                if (_mVersion == 1 && static_cast<unsigned int>(_mDefaultLength) == 0)
                {
                    _indentLog("  description_length[%u] = %u", i,
                               static_cast<unsigned int>(_mDescriptionLengths[i]));
                }
            }
        }

    protected:
        uint32_t _mGroupingType;
        uint32_t _mDefaultLength; // if version == 1
        uint32_t _mDefaultSampleDescriptionIndex; // if version >= 2
        uint32_t _mEntryCount;
        std::vector<uint32_t> _mDescriptionLengths; // if version == 1
        std::vector<std::shared_ptr<SampleGroupDescriptionEntry>> _mSampleGroupEntries;

        void _parseRawBufIntoFields()
        {
            uint8_t *cursor = _mRawBuffer.data();

            // Skip size, boxname and version/flags fields
            cursor += 12;

            _mGroupingType = Utils::read4BytesIntoU32(cursor);
            cursor += 4;

            if (_mVersion == 1)
            {
                _mDefaultLength = Utils::read4BytesIntoU32(cursor);
                cursor += 4;
            }

            if (_mVersion >= 2)
            {
                _mDefaultSampleDescriptionIndex = Utils::read4BytesIntoU32(cursor);
                cursor += 4;
            }

            _mEntryCount = Utils::read4BytesIntoU32(cursor);
            cursor += 4;

            for (auto i = 0; i < static_cast<unsigned int>(_mEntryCount); i++)
            {
                if (_mVersion == 1 && static_cast<unsigned int>(_mDefaultLength) == 0)
                {
                    _mDescriptionLengths[i] = Utils::read4BytesIntoU32(cursor);
                    cursor += 4;
                }

                unsigned int defaultLength = static_cast<unsigned int>(_mDefaultLength);
                if (defaultLength == 0)
                {
                    defaultLength = static_cast<unsigned int>(_mDescriptionLengths[i]);
                }

                // TODO: deal with the _mSampleGroupEntries vector here later

                cursor += defaultLength;
            }
        }
};
