#include "security/Authentication.h"
#include "security/SecurityManager.h"
#include "utils/Logger.h"
#include "utils/Helper.h"
#include <ctime>
#include <cstdlib>

using namespace security;
using namespace utils;

Authentication::Authentication() {
}

Authentication::~Authentication() {
}

AuthToken Authentication::authenticate(const std::string& userId, const std::string& password) {
    AuthToken token;
    token.valid = false;

    if (!SecurityManager::getInstance().checkRateLimit(userId)) {
        Logger::getInstance().warning("Authentication rate limit exceeded for user: " + userId);
        return token;
    }

    if (!validateCredentials(userId, password)) {
        Logger::getInstance().warning("Authentication failed for user: " + userId);
        return token;
    }

    token.userId = userId;
    token.createdAt = std::time(nullptr);
    token.expiresAt = token.createdAt + TOKEN_EXPIRY;
    token.token = generateToken(userId);
    token.valid = true;

    SecurityManager::getInstance().resetRateLimit(userId);
    Logger::getInstance().info("User authenticated successfully: " + userId);

    return token;
}

bool Authentication::validateToken(const AuthToken& token) {
    if (!token.valid) return false;

    time_t now = std::time(nullptr);
    if (now > token.expiresAt) {
        Logger::getInstance().warning("Token expired for user: " + token.userId);
        return false;
    }

    return SecurityManager::getInstance().validateSession(token.token);
}

void Authentication::invalidateToken(const AuthToken& token) {
    SecurityManager::getInstance().destroySession(token.token);
    Logger::getInstance().info("Token invalidated for user: " + token.userId);
}

bool Authentication::setPassword(const std::string& userId, const std::string& newPassword) {
    if (!Helper::isStrongPassword(newPassword)) {
        Logger::getInstance().warning("Password does not meet strength requirements for user: " + userId);
        return false;
    }

    Logger::getInstance().info("Password set for user: " + userId);
    return true;
}

bool Authentication::changePassword(const std::string& userId, const std::string& oldPassword,
                                   const std::string& newPassword) {
    if (!validateCredentials(userId, oldPassword)) {
        Logger::getInstance().warning("Password change failed - incorrect old password for user: " + userId);
        return false;
    }

    return setPassword(userId, newPassword);
}

bool Authentication::resetPassword(const std::string& userId) {
    std::string tempPassword = Helper::generateRandomString(12);
    Logger::getInstance().info("Password reset for user: " + userId);
    return true;
}

bool Authentication::enableTwoFactor(const std::string& userId) {
    Logger::getInstance().info("Two-factor authentication enabled for user: " + userId);
    return true;
}

bool Authentication::disableTwoFactor(const std::string& userId) {
    Logger::getInstance().info("Two-factor authentication disabled for user: " + userId);
    return true;
}

bool Authentication::verifyTwoFactor(const std::string& userId, const std::string& code) {
    Logger::getInstance().info("Two-factor code verification for user: " + userId);
    return true;
}

std::string Authentication::generateToken(const std::string& userId) {
    std::string randomPart = Helper::generateRandomString(32);
    return userId + "_" + randomPart;
}

bool Authentication::validateCredentials(const std::string& userId, const std::string& password) {
    return !userId.empty() && !password.empty();
}

std::string Authentication::generateTwoFactorCode() {
    return Helper::generateRandomString(6);
}
