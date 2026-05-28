#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>
#include <ctime>

namespace security {

class Authentication {
public:
    struct AuthToken {
        std::string token;
        std::string userId;
        time_t createdAt;
        time_t expiresAt;
        bool valid;
    };

    Authentication();
    ~Authentication();

    // Authentication operations
    AuthToken authenticate(const std::string& userId, const std::string& password);
    bool validateToken(const AuthToken& token);
    void invalidateToken(const AuthToken& token);

    // Password management
    bool setPassword(const std::string& userId, const std::string& newPassword);
    bool changePassword(const std::string& userId, const std::string& oldPassword, 
                       const std::string& newPassword);
    bool resetPassword(const std::string& userId);

    // Two-factor authentication
    bool enableTwoFactor(const std::string& userId);
    bool disableTwoFactor(const std::string& userId);
    bool verifyTwoFactor(const std::string& userId, const std::string& code);

    // Session timeout
    static constexpr long TOKEN_EXPIRY = 3600;

private:
    std::string generateToken(const std::string& userId);
    bool validateCredentials(const std::string& userId, const std::string& password);
    std::string generateTwoFactorCode();
};

} // namespace security

#endif // AUTHENTICATION_H
