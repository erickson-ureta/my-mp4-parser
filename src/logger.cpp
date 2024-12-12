#include "logger.hpp"

Logger&
Logger::get()
{
    return _inst;
}

void
Logger::setLogLevel(const LoggerLevel& logLevel)
{
    _mLogLevel = logLevel;
}

// Private constructor
Logger::Logger() : _mLogLevel(LoggerLevel::INFO)
{
}

Logger Logger::_inst;
