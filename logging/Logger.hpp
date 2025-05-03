#pragma once
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>
#include <filesystem>

enum class Modes : uint8_t
{
    INFO,
    VERBOSE,
    WARNING,
    DEBUG,
    ERROR
};

class Logger
{
public:
    Logger(const Logger &other)
    {
    }
    Logger &operator=(const Logger &)
    {
        return *this;
    }

    static Logger &getInstance()
    {
        static Logger instance;
        return instance;
    }

    template <typename... Args>
    void LOG(const char *funcName, const char *file, uint32_t line, const Modes mode, Args &&...message)
    {
        std::lock_guard<std::mutex> lck(mtx);
        std::ostringstream oss;
        std::string filename = std::filesystem::path(file).filename().string();
        (oss << ... << std::forward<Args>(message));
        std::cout << '[' << levelToString(mode) << "] | [" << funcName << ":" << line << "] | [" << filename << "] | " << oss.str() << '\n';
    }

    std::string levelToString(const Modes mode)
    {
        switch (mode)
        {
        case Modes::INFO:
            return "INFO";
        case Modes::VERBOSE:
            return "VERBOSE";
        case Modes::WARNING:
            return "WARNING";
        case Modes::DEBUG:
            return "DEBUG";
        case Modes::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
        }
        return std::string();
    }

private:
    Logger() : loggingMode{Modes::DEBUG} {}

    Modes loggingMode;
    std::mutex mtx;
};

#define LOGINFO(...)                                                                       \
    do                                                                                     \
    {                                                                                      \
        Logger::getInstance().LOG(__func__, __FILE__, __LINE__, Modes::INFO, __VA_ARGS__); \
    } while (0)

#define LOGVERBOSE(...)                                                                       \
    do                                                                                        \
    {                                                                                         \
        Logger::getInstance().LOG(__func__, __FILE__, __LINE__, Modes::VERBOSE, __VA_ARGS__); \
    } while (0)

#define LOGWARNING(...)                                                                       \
    do                                                                                        \
    {                                                                                         \
        Logger::getInstance().LOG(__func__, __FILE__, __LINE__, Modes::WARNING, __VA_ARGS__); \
    } while (0)

#define LOGDEBUG(...)                                                                       \
    do                                                                                      \
    {                                                                                       \
        Logger::getInstance().LOG(__func__, __FILE__, __LINE__, Modes::DEBUG, __VA_ARGS__); \
    } while (0)

#define LOGERROR(...)                                                                       \
    do                                                                                      \
    {                                                                                       \
        Logger::getInstance().LOG(__func__, __FILE__, __LINE__, Modes::ERROR, __VA_ARGS__); \
    } while (0)
