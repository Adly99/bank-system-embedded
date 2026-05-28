#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>

namespace utils {

class Logger {
public:
    enum LogLevel {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3,
        CRITICAL = 4
    };

    static Logger& getInstance();

    // Initialize logger
    bool initialize(const std::string& logFile);

    // Logging functions
    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void critical(const std::string& message);

    // Set log level
    void setLogLevel(LogLevel level) { currentLogLevel = level; }
    LogLevel getLogLevel() const { return currentLogLevel; }

    // Clear logs
    void clearLogs();

private:
    Logger();
    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(LogLevel level, const std::string& message);
    std::string getTimestamp() const;
    std::string levelToString(LogLevel level) const;

    std::ofstream logFile;
    LogLevel currentLogLevel;
    std::string logFilePath;
};

} // namespace utils

#endif // LOGGER_H
