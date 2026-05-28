#ifndef SECURITYMANAGER_H
#define SECURITYMANAGER_H

#include <string>
#include <vector>
#include <map>

namespace security {

class SecurityManager {
public:
    static SecurityManager& getInstance();

    // Encryption/Decryption
    std::string encrypt(const std::string& data, const std::string& key);
    std::string decrypt(const std::string& encryptedData, const std::string& key);

    // Hash functions
    std::string hashPassword(const std::string& password);
    bool verifyPassword(const std::string& password, const std::string& hash);

    // Session management
    bool createSession(const std::string& userId);
    bool validateSession(const std::string& sessionToken);
    bool destroySession(const std::string& sessionToken);

    // Audit logging
    void logSecurityEvent(const std::string& userId, const std::string& action, 
                         const std::string& details);
    std::vector<std::string> getAuditLog() const { return auditLog; }

    // Rate limiting
    bool checkRateLimit(const std::string& userId);
    void resetRateLimit(const std::string& userId);

private:
    SecurityManager() = default;
    ~SecurityManager();

    SecurityManager(const SecurityManager&) = delete;
    SecurityManager& operator=(const SecurityManager&) = delete;

    std::vector<std::string> activeSessions;
    std::vector<std::string> auditLog;
    std::map<std::string, int> rateLimitMap;

    static constexpr int MAX_ATTEMPTS = 5;
    static constexpr int RATE_LIMIT_WINDOW = 300;
};

} // namespace security

#endif // SECURITYMANAGER_H
