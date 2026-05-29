#include "utils/Helper.h"
#include <algorithm>
#include <cctype>
#include <regex>
#include <random>
#include <cstdio>

using namespace utils;

std::string Helper::trim(const std::string& str) {
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        start++;
    }

    auto end = str.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

std::string Helper::toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return result;
}

std::string Helper::toUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
    return result;
}

bool Helper::startsWith(const std::string& str, const std::string& prefix) {
    return str.compare(0, prefix.length(), prefix) == 0;
}

bool Helper::endsWith(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length()) return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

std::vector<std::string> Helper::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

std::string Helper::join(const std::vector<std::string>& vec, const std::string& delimiter) {
    std::string result;
    for (size_t i = 0; i < vec.size(); ++i) {
        result += vec[i];
        if (i < vec.size() - 1) {
            result += delimiter;
        }
    }
    return result;
}

bool Helper::isValidNumber(const std::string& str) {
    if (str.empty()) return false;

    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') {
        start = 1;
    }

    for (size_t i = start; i < str.length(); ++i) {
        if (!std::isdigit(str[i]) && str[i] != '.') {
            return false;
        }
    }
    return true;
}

double Helper::parseDouble(const std::string& str) {
    try {
        return std::stod(str);
    } catch (...) {
        return 0.0;
    }
}

int Helper::parseInt(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (...) {
        return 0;
    }
}

std::string Helper::formatMoney(double amount) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.2f", amount);
    return std::string(buffer);
}

bool Helper::isValidEmail(const std::string& email) {
    const std::regex pattern(R"((\w+)(\.?(\w+))*@(\w+)(\.?(\w+))+)");
    return std::regex_match(email, pattern);
}

bool Helper::isValidAccountNumber(const std::string& accountNumber) {
    return !accountNumber.empty() && accountNumber.length() >= 8 && 
           accountNumber.length() <= 20 && std::all_of(accountNumber.begin(), 
           accountNumber.end(), ::isalnum);
}

bool Helper::isValidAmount(double amount) {
    return amount > 0 && amount < 1e10;
}

bool Helper::isStrongPassword(const std::string& password) {
    if (password.length() < 8) return false;
    
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

    for (char c : password) {
        if (std::isupper(c)) hasUpper = true;
        else if (std::islower(c)) hasLower = true;
        else if (std::isdigit(c)) hasDigit = true;
        else if (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*') {
            hasSpecial = true;
        }
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

std::string Helper::generateUUID() {
    char uuid_str[37];
    snprintf(uuid_str, sizeof(uuid_str), "%08x-%04x-%04x-%04x-%012x", 
             rand(), rand() % 0xffff, rand() % 0xffff, rand() % 0xffff, rand());
    return std::string(uuid_str);
}

std::string Helper::generateRandomString(size_t length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 61);

    std::string result;
    for (size_t i = 0; i < length; ++i) {
        result += VALID_CHARS[dis(gen)];
    }

    return result;
}
