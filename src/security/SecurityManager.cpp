#include "security/SecurityManager.h"
#include "utils/Logger.h"
#include <algorithm>
#include <functional>
#include <ctime>

using namespace security;
using namespace utils;

SecurityManager& SecurityManager::getInstance() {
    static SecurityManager instance;
    return instance;
}

SecurityManager::~SecurityManager() {
    activeSessions.clear();
    auditLog.clear();
    rateLimitMap.clear();
}

std::string SecurityManager::encrypt(const std::string& data, const std::string& key) {
    std::string encrypted = data;
    for (size_t i = 0; i < encrypted.length(); ++i) {
        encrypted[i] ^= key[i % key.length()];
    }
    return encrypted;
}

std::string SecurityManager::decrypt(const std::string& encryptedData, const std::string& key) {
    return encrypt(encryptedData, key);
}

std::string SecurityManager::hashPassword(const std::string& password) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

bool SecurityManager::verifyPassword(const std::string& password, const std::string& hash) {
    return hashPassword(password) == hash;
}

bool SecurityManager::createSession(const std::string& userId) {
    std::string sessionToken = userId + "_" + std::to_string(std::time(nullptr));
    activeSessions.push_back(sessionToken);
    logSecurityEvent(userId, "SESSION_CREATE", "Session created");
    return true;
}

bool SecurityManager::validateSession(const std::string& sessionToken) {
    return std::find(activeSessions.begin(), activeSessions.end(), sessionToken) != activeSessions.end();
}

bool SecurityManager::destroySession(const std::string& sessionToken) {
    auto it = std::find(activeSessions.begin(), activeSessions.end(), sessionToken);
    if (it != activeSessions.end()) {
        activeSessions.erase(it);
        logSecurityEvent("", "SESSION_DESTROY", "Session destroyed");
        return true;
    }
    return false;
}

void SecurityManager::logSecurityEvent(const std::string& userId, const std::string& action,
                                       const std::string& details) {
    time_t now = std::time(nullptr);
    std::string logEntry = "[" + std::string(std::ctime(&now)) + "] User: " + userId +
                          " Action: " + action + " Details: " + details;
    auditLog.push_back(logEntry);
    Logger::getInstance().info(logEntry);
}

bool SecurityManager::checkRateLimit(const std::string& userId) {
    if (rateLimitMap[userId] >= MAX_ATTEMPTS) {
        Logger::getInstance().warning("Rate limit exceeded for user: " + userId);
        return false;
    }
    rateLimitMap[userId]++;
    return true;
}

void SecurityManager::resetRateLimit(const std::string& userId) {
    rateLimitMap[userId] = 0;
}
