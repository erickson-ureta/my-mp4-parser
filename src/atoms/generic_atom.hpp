#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <vector>

#include "../constants.hpp"
#include "../logger.hpp"
#include "../utils.hpp"

#define DATA_START_OFFSET ATOM_NAME_OFFSET+ATOM_NAME_LEN

class GenericAtom
{
    public:
        GenericAtom(const std::string& atomName, size_t size, uint8_t *rawBuffer)
            : _mAtomName(atomName), _mSize(size)
        {
            _mRawBuffer = std::vector<uint8_t>(rawBuffer, rawBuffer + size);
            _mVersion = _mRawBuffer[DATA_START_OFFSET];
            _mFlags = Utils::read3BytesIntoU32(_mRawBuffer.data() + DATA_START_OFFSET + 1);
        }

        const size_t getSize()
        {
            return _mSize;
        }

        const std::string getAtomName()
        {
            return _mAtomName;
        }

        const bool hasChildren()
        {
            return _mHasChildren;
        }

        const size_t getChildrenOffset()
        {
            return _mChildrenOffset;
        }

        void setLogIndentLevel(const unsigned int indentLevel)
        {
            _mLogIndentLevel = indentLevel;
        }

        const unsigned int getLogIndentLevel()
        {
            return _mLogIndentLevel;
        }

        virtual void debugPrint() {}

    protected:
        // Common fields across all atoms
        uint8_t _mVersion = 0;
        uint32_t _mFlags = 0; // 24 bits of information stored in a 32-bit uint

        // Metadata stuff fields
        const std::string _mAtomName = "";
        size_t _mSize;
        bool _mHasChildren = false;
        size_t _mChildrenOffset = DATA_START_OFFSET;
        std::vector<uint8_t> _mRawBuffer;
        unsigned int _mLogIndentLevel = 0;

        template <typename ... Args>
        void _indentLog(const std::string &fmt, Args ... args)
        {
            std::string indentStr = Utils::generateIndentStr(_mLogIndentLevel);

            std::stringstream ss;
            ss << indentStr << fmt;

            Logger::get().info(ss.str(), args ...);
        }
};
