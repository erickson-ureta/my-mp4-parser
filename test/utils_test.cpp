#include "gtest/gtest.h"
#include "../src/utils.hpp"

TEST(UtilsTest, TestGenerateIndentStr)
{
    ASSERT_EQ(Utils::generateIndentStr(0), "");
    ASSERT_EQ(Utils::generateIndentStr(1), "  ");
    ASSERT_EQ(Utils::generateIndentStr(2), "    ");
    ASSERT_EQ(Utils::generateIndentStr(3), "      ");
    ASSERT_EQ(Utils::generateIndentStr(4), "        ");
}

TEST(UtilsTest, TestRead3BytesIntoU32)
{
    const std::vector<uint8_t> testBuf = {
        0x12, 0x34, 0x56
    };
    ASSERT_EQ(Utils::read3BytesIntoU32(testBuf.data()), 0x00123456);
    ASSERT_EQ(Utils::read3BytesIntoU32(testBuf.data()), 1193046);
}

TEST(UtilsTest, TestRead4BytesIntoU32)
{
    const std::vector<uint8_t> testBuf = {
        0x12, 0x34, 0x56, 0x78
    };
    ASSERT_EQ(Utils::read4BytesIntoU32(testBuf.data()), 0x12345678);
    ASSERT_EQ(Utils::read4BytesIntoU32(testBuf.data()), 305419896);
}

TEST(UtilsTest, TestRead8BytesIntoU64)
{
    const std::vector<uint8_t> testBuf = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
    };
    ASSERT_EQ(Utils::read8BytesIntoU64(testBuf.data()), 0x0123456789abcdef);
    ASSERT_EQ(Utils::read8BytesIntoU64(testBuf.data()), 81985529216486895);
}

TEST(UtilsTest, TestReadBytesIntoStr)
{
    const std::vector<uint8_t> testBuf = {
        0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64,
    };
    ASSERT_EQ(Utils::readBytesIntoStr(testBuf.data(), testBuf.size()), "hello world");
}

TEST(UtilsTest, TestU32BytesIntoStr)
{
    ASSERT_EQ(Utils::u32BytesIntoStr(0x626c7565), "blue");
    ASSERT_EQ(Utils::u32BytesIntoStr(1651275109), "blue");
}
