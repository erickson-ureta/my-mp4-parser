#include "gtest/gtest.h"
#include "../src/logger.hpp"

class LoggerTest : public testing::Test
{
    protected:
        std::stringstream ss;
        Logger *logger;

        void SetUp() override
        {
            logger = &Logger::get();
            Logger::get().setOutputStream(ss);
        }
};

TEST_F(LoggerTest, TestLogLevels)
{
    // Default log level setting should be info
    ASSERT_EQ(logger->getLogLevel(), LoggerLevel::INFO);

    logger->setLogLevel(LoggerLevel::DEBUG);
    ASSERT_EQ(logger->getLogLevel(), LoggerLevel::DEBUG);
    logger->debug("this is a debug message");
    ASSERT_EQ(ss.str(), "[DEBUG]: this is a debug message\n");
    ss.str("");
    logger->info("this is an info message");
    ASSERT_EQ(ss.str(), "[INFO]: this is an info message\n");
    ss.str("");
    logger->error("this is an error message");
    ASSERT_EQ(ss.str(), "[ERROR]: this is an error message\n");
    ss.str("");

    logger->setLogLevel(LoggerLevel::ERROR);
    ASSERT_EQ(logger->getLogLevel(), LoggerLevel::ERROR);
    logger->debug("this is a debug message");
    ASSERT_EQ(ss.str(), "");
    ss.str("");
    logger->info("this is an info message");
    ASSERT_EQ(ss.str(), "");
    ss.str("");
    logger->error("this is an error message");
    ASSERT_EQ(ss.str(), "[ERROR]: this is an error message\n");
    ss.str("");

    logger->setLogLevel(LoggerLevel::INFO);
    ASSERT_EQ(logger->getLogLevel(), LoggerLevel::INFO);
    logger->debug("this is a debug message");
    ASSERT_EQ(ss.str(), "");
    ss.str("");
    logger->info("this is an info message");
    ASSERT_EQ(ss.str(), "[INFO]: this is an info message\n");
    ss.str("");
    logger->error("this is an error message");
    ASSERT_EQ(ss.str(), "[ERROR]: this is an error message\n");
    ss.str("");
}

TEST_F(LoggerTest, TestFormatSpecifierTypes)
{
    logger->info("%d", -2147483648);
    ASSERT_EQ(ss.str(), "[INFO]: -2147483648\n");
    ss.str("");

    logger->info("%u", 4294967295);
    ASSERT_EQ(ss.str(), "[INFO]: 4294967295\n");
    ss.str("");

    logger->info("%o", 1000);
    ASSERT_EQ(ss.str(), "[INFO]: 1750\n");
    ss.str("");

    logger->info("%x %#X", 1000, 1000);
    ASSERT_EQ(ss.str(), "[INFO]: 3e8 0X3E8\n");
    ss.str("");

    logger->info("%.2f %.2F", 9999.99, 9999.99);
    ASSERT_EQ(ss.str(), "[INFO]: 9999.99 9999.99\n");
    ss.str("");

    logger->info("%.2e %.2E", 1000.0, 1000.0);
    ASSERT_EQ(ss.str(), "[INFO]: 1.00e+03 1.00E+03\n");
    ss.str("");

    logger->info("%c", 'a');
    ASSERT_EQ(ss.str(), "[INFO]: a\n");
    ss.str("");

    const std::string strVar = "hello world";
    logger->info("%s %s", "hello world", strVar.c_str());
    ASSERT_EQ(ss.str(), "[INFO]: hello world hello world\n");
    ss.str("");

    void *testPtr = (void *) 0x12345678;
    logger->info("%p", testPtr);
    ASSERT_EQ(ss.str(), "[INFO]: 0x12345678\n");
    ss.str("");
}

TEST_F(LoggerTest, TestMultipleFormatSpecifiers)
{
    logger->info("%d", 1);
    ASSERT_EQ(ss.str(), "[INFO]: 1\n");
    ss.str("");

    logger->info("%d %d", 1, 2);
    ASSERT_EQ(ss.str(), "[INFO]: 1 2\n");
    ss.str("");

    logger->info("%d %d %d", 1, 2, 3);
    ASSERT_EQ(ss.str(), "[INFO]: 1 2 3\n");
    ss.str("");

    logger->info("%d %d %d %d", 1, 2, 3, 4);
    ASSERT_EQ(ss.str(), "[INFO]: 1 2 3 4\n");
    ss.str("");

    logger->info("%d %d %d %d %d", 1, 2, 3, 4, 5);
    ASSERT_EQ(ss.str(), "[INFO]: 1 2 3 4 5\n");
    ss.str("");
}
