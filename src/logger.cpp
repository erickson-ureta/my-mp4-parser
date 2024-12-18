#include "logger.hpp"

Logger&
Logger::get()
{
    return _inst;
}

const LoggerLevel
Logger::getLogLevel()
{
    return _mLogLevel;
}

void
Logger::setLogLevel(const LoggerLevel& logLevel)
{
    _mLogLevel = logLevel;
}

void
Logger::setOutputStream(std::ostream &output)
{
    _mLogOutput = &output;
}

// Private constructor
Logger::Logger() : _mLogLevel(LoggerLevel::INFO), _mLogOutput(&std::cout)
{
}

Logger Logger::_inst;
