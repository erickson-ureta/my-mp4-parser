#pragma once
#pragma GCC diagnostic ignored "-Wformat-security"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
    // Shamelessly copied from a StackOverflow post

    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '/0'
    if (size_s <= 0)
    {
        throw std::runtime_error("Error during formatting.");
    }

    auto size = static_cast<size_t>(size_s);

    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args...);

    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

enum class LoggerLevel
{
    ERROR = 0,
    INFO = 1,
    DEBUG = 2
};

class Logger
{
    public:
        // Singleton pattern here
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        static Logger& get();

        const LoggerLevel getLogLevel();
        void setLogLevel(const LoggerLevel& logLevel);
        void setOutputStream(std::ostream &output);

        template <typename ... Args>
        void error(const std::string &fmt, Args ... args)
        {
            if (_mLogLevel < LoggerLevel::ERROR) return;

            (*_mLogOutput) << "[ERROR]: " << string_format(fmt, args...) << std::endl;
        }

        template <typename ... Args>
        void info(const std::string &fmt, Args ... args)
        {
            if (_mLogLevel < LoggerLevel::INFO) return;

            (*_mLogOutput) << "[INFO]: " << string_format(fmt, args...) << std::endl;
        }

        template <typename ... Args>
        void debug(const std::string &fmt, Args ... args)
        {
            if (_mLogLevel < LoggerLevel::DEBUG) return;

            (*_mLogOutput) << "[DEBUG]: " << string_format(fmt, args...) << std::endl;
        }

    private:
        LoggerLevel _mLogLevel = LoggerLevel::INFO;
        std::ostream *_mLogOutput;
        static Logger _inst;

        // Private constructor for singleton
        Logger();
};
