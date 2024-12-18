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
