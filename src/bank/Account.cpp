#include "bank/Account.h"
#include "bank/Transaction.h"
#include "utils/Logger.h"
#include <ctime>

using namespace bank;
using namespace utils;

Account::Account(const std::string& accountNumber, const std::string& customerName,
                 AccountType type, double initialBalance)
    : accountNumber(accountNumber), customerName(customerName), balance(initialBalance),
      type(type), creationDate(std::time(nullptr)), active(true) {
    Logger::getInstance().info("Account created: " + accountNumber + " for " + customerName);
}

Account::~Account() {
    Logger::getInstance().info("Account destroyed: " + accountNumber);
}

bool Account::deposit(double amount) {
    if (!validateAmount(amount)) {
        Logger::getInstance().warning("Invalid deposit amount: " + std::to_string(amount));
        return false;
    }

    balance += amount;
    Transaction txn("TXN_DEPOSIT_" + accountNumber, Transaction::DEPOSIT, amount, accountNumber);
    txn.markComplete();
    addTransaction(txn);
    Logger::getInstance().info("Deposit successful: " + std::to_string(amount) + " to " + accountNumber);
    return true;
}

bool Account::withdraw(double amount) {
    if (!validateAmount(amount)) {
        Logger::getInstance().warning("Invalid withdrawal amount: " + std::to_string(amount));
        return false;
    }

    if (balance < amount) {
        Logger::getInstance().warning("Insufficient funds for withdrawal from " + accountNumber);
        return false;
    }

    balance -= amount;
    Transaction txn("TXN_WITHDRAW_" + accountNumber, Transaction::WITHDRAWAL, amount, accountNumber);
    txn.markComplete();
    addTransaction(txn);
    Logger::getInstance().info("Withdrawal successful: " + std::to_string(amount) + " from " + accountNumber);
    return true;
}

bool Account::transfer(Account& targetAccount, double amount) {
    if (!validateAmount(amount) || balance < amount) {
        Logger::getInstance().warning("Transfer failed from " + accountNumber);
        return false;
    }

    this->withdraw(amount);
    targetAccount.deposit(amount);
    Logger::getInstance().info("Transfer successful: " + std::to_string(amount) + 
                              " from " + accountNumber + " to " + targetAccount.getAccountNumber());
    return true;
}

void Account::deactivate() {
    active = false;
    Logger::getInstance().info("Account deactivated: " + accountNumber);
}

void Account::activate() {
    active = true;
    Logger::getInstance().info("Account activated: " + accountNumber);
}

void Account::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
}

bool Account::validateAmount(double amount) const {
    return amount > 0;
}
