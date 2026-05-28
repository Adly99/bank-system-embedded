#include "bank/Customer.h"
#include "utils/Logger.h"
#include "utils/Helper.h"
#include <algorithm>
#include <ctime>

using namespace bank;
using namespace utils;

Customer::Customer(const std::string& id, const std::string& name,
                   const std::string& email, CustomerType type)
    : customerId(id), name(name), email(email), type(type),
      registrationDate(std::time(nullptr)), verified(false) {
    Logger::getInstance().info("Customer created: " + id + " (" + name + ")");
}

Customer::~Customer() {
    for (auto account : accounts) {
        delete account;
    }
    accounts.clear();
    Logger::getInstance().info("Customer destroyed: " + customerId);
}

bool Customer::addAccount(const Account& account) {
    Account* newAccount = new Account(account);
    accounts.push_back(newAccount);
    Logger::getInstance().info("Account added to customer: " + customerId);
    return true;
}

bool Customer::removeAccount(const std::string& accountNumber) {
    auto it = std::find_if(accounts.begin(), accounts.end(),
                          [&accountNumber](Account* acc) {
                              return acc->getAccountNumber() == accountNumber;
                          });

    if (it != accounts.end()) {
        delete *it;
        accounts.erase(it);
        Logger::getInstance().info("Account removed from customer: " + customerId);
        return true;
    }
    return false;
}

Account* Customer::findAccount(const std::string& accountNumber) {
    for (auto account : accounts) {
        if (account->getAccountNumber() == accountNumber) {
            return account;
        }
    }
    return nullptr;
}

bool Customer::verifyCustomer() {
    if (validateEmail(email)) {
        verified = true;
        Logger::getInstance().info("Customer verified: " + customerId);
        return true;
    }
    Logger::getInstance().warning("Customer verification failed: " + customerId);
    return false;
}

bool Customer::validateEmail(const std::string& email) const {
    return Helper::isValidEmail(email);
}
