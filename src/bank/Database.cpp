#include "bank/Database.h"
#include "utils/Logger.h"

using namespace bank;
using namespace utils;

Database& Database::getInstance() {
    static Database instance;
    return instance;
}

Database::~Database() {
    for (auto& pair : customers) {
        delete pair.second;
    }
    for (auto& pair : accounts) {
        delete pair.second;
    }
    customers.clear();
    accounts.clear();
}

bool Database::addCustomer(Customer* customer) {
    if (!customer) return false;
    customers[customer->getCustomerId()] = customer;
    Logger::getInstance().info("Customer added to database: " + customer->getCustomerId());
    return true;
}

bool Database::removeCustomer(const std::string& customerId) {
    auto it = customers.find(customerId);
    if (it != customers.end()) {
        delete it->second;
        customers.erase(it);
        Logger::getInstance().info("Customer removed from database: " + customerId);
        return true;
    }
    return false;
}

Customer* Database::findCustomer(const std::string& customerId) {
    auto it = customers.find(customerId);
    if (it != customers.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<Customer*> Database::getAllCustomers() {
    std::vector<Customer*> result;
    for (auto& pair : customers) {
        result.push_back(pair.second);
    }
    return result;
}

bool Database::addAccount(Account* account) {
    if (!account) return false;
    accounts[account->getAccountNumber()] = account;
    Logger::getInstance().info("Account added to database: " + account->getAccountNumber());
    return true;
}

bool Database::removeAccount(const std::string& accountNumber) {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end()) {
        delete it->second;
        accounts.erase(it);
        Logger::getInstance().info("Account removed from database: " + accountNumber);
        return true;
    }
    return false;
}

Account* Database::findAccount(const std::string& accountNumber) {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<Account*> Database::getAllAccounts() {
    std::vector<Account*> result;
    for (auto& pair : accounts) {
        result.push_back(pair.second);
    }
    return result;
}

bool Database::backup(const std::string& filename) {
    Logger::getInstance().info("Database backup initiated to: " + filename);
    return serializeData(filename);
}

bool Database::restore(const std::string& filename) {
    Logger::getInstance().info("Database restore initiated from: " + filename);
    return deserializeData(filename);
}

void Database::clear() {
    for (auto& pair : customers) {
        delete pair.second;
    }
    for (auto& pair : accounts) {
        delete pair.second;
    }
    customers.clear();
    accounts.clear();
    Logger::getInstance().info("Database cleared");
}

bool Database::serializeData(const std::string& filename) {
    Logger::getInstance().info("Serializing database to: " + filename);
    return true;
}

bool Database::deserializeData(const std::string& filename) {
    Logger::getInstance().info("Deserializing database from: " + filename);
    return true;
}
