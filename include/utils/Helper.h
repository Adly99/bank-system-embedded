#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <ctime>

namespace utils {

class Helper {
public:
    // String utilities
    static std::string trim(const std::string& str);
    static std::string toLower(const std::string& str);
    static std::string toUpper(const std::string& str);
    static bool startsWith(const std::string& str, const std::string& prefix);
    static bool endsWith(const std::string& str, const std::string& suffix);
    static std::vector<std::string> split(const std::string& str, char delimiter);
    static std::string join(const std::vector<std::string>& vec, const std::string& delimiter);

    // Numeric utilities
    static bool isValidNumber(const std::string& str);
    static double parseDouble(const std::string& str);
    static int parseInt(const std::string& str);
    static std::string formatMoney(double amount);

    // Validation utilities
    static bool isValidEmail(const std::string& email);
    static bool isValidAccountNumber(const std::string& accountNumber);
    static bool isValidAmount(double amount);
    static bool isStrongPassword(const std::string& password);

    // ID generation
    static std::string generateUUID();
    static std::string generateRandomString(size_t length);

private:
    Helper() = default;
    static constexpr const char* VALID_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
};

} // namespace utils

#endif // HELPER_H
