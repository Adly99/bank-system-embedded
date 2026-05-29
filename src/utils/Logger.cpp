#include "utils/Logger.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace utils;

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() : currentLogLevel(INFO), logFilePath("") {
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

bool Logger::initialize(const std::string& logFilePath_param) {
    logFilePath = logFilePath_param;
    logFile.open(logFilePath, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file: " << logFilePath << std::endl;
        return false;
    }
    info("Logger initialized");
    return true;
}

void Logger::debug(const std::string& message) {
    log(DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(INFO, message);
}

void Logger::warning(const std::string& message) {
    log(WARNING, message);
}

void Logger::error(const std::string& message) {
    log(ERROR, message);
}

void Logger::critical(const std::string& message) {
    log(CRITICAL, message);
}

void Logger::clearLogs() {
    if (logFile.is_open()) {
        logFile.close();
    }
    logFile.open(logFilePath, std::ios::trunc);
    info("Logs cleared");
}

void Logger::log(LogLevel level, const std::string& message) {
    if (level < currentLogLevel) {
        return;
    }

    std::string logMessage = getTimestamp() + " [" + levelToString(level) + "] " + message;

    std::cout << logMessage << std::endl;

    if (logFile.is_open()) {
        logFile << logMessage << std::endl;
        logFile.flush();
    }
}

std::string Logger::getTimestamp() const {
    auto now = std::time(nullptr);
    struct tm tm_buf;
    struct tm* tm = nullptr;
    
#ifdef _MSC_VER
    if (localtime_s(&tm_buf, &now) == 0) {
        tm = &tm_buf;
    }
#else
    tm = localtime_r(&now, &tm_buf);
#endif

    if (!tm) {
        return "UNKNOWN";
    }

    std::ostringstream oss;
    oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string Logger::levelToString(LogLevel level) const {
    switch (level) {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        case CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN";
    }
}
