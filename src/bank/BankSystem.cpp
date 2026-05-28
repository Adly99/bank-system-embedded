#include "bank/BankSystem.h"
#include "utils/Logger.h"
#include "utils/Helper.h"
#include <iostream>
#include <sstream>

using namespace bank;
using namespace utils;

BankSystem::BankSystem()
    : database(Database::getInstance()), running(false), transactionCounter(0) {
}

BankSystem::~BankSystem() {
    shutdown();
}

bool BankSystem::initialize() {
    Logger::getInstance().initialize("bank_system.log");
    Logger::getInstance().info("Bank System initializing...");
    running = true;
    Logger::getInstance().info("Bank System initialized successfully");
    return true;
}

void BankSystem::shutdown() {
    Logger::getInstance().info("Bank System shutting down...");
    running = false;
    Logger::getInstance().info("Bank System shut down successfully");
}

bool BankSystem::registerCustomer(const std::string& id, const std::string& name,
                                 const std::string& email, Customer::CustomerType type) {
    if (!running) {
        Logger::getInstance().error("Bank System is not running");
        return false;
    }

    Customer* customer = new Customer(id, name, email, type);
    if (!customer->verifyCustomer()) {
        Logger::getInstance().warning("Customer verification failed: " + id);
        delete customer;
        return false;
    }

    return database.addCustomer(customer);
}

bool BankSystem::createAccount(const std::string& customerId, const std::string& accountNumber,
                              Account::AccountType type, double initialBalance) {
    if (!running) {
        Logger::getInstance().error("Bank System is not running");
        return false;
    }

    Customer* customer = database.findCustomer(customerId);
    if (!customer) {
        Logger::getInstance().error("Customer not found: " + customerId);
        return false;
    }

    Account* account = new Account(accountNumber, customer->getName(), type, initialBalance);
    customer->addAccount(*account);
    return database.addAccount(account);
}

bool BankSystem::processDeposit(const std::string& accountNumber, double amount) {
    if (!running) return false;

    Account* account = database.findAccount(accountNumber);
    if (!account) {
        Logger::getInstance().error("Account not found: " + accountNumber);
        return false;
    }

    return account->deposit(amount);
}

bool BankSystem::processWithdrawal(const std::string& accountNumber, double amount) {
    if (!running) return false;

    Account* account = database.findAccount(accountNumber);
    if (!account) {
        Logger::getInstance().error("Account not found: " + accountNumber);
        return false;
    }

    return account->withdraw(amount);
}

bool BankSystem::processTransfer(const std::string& sourceAccount, const std::string& destAccount,
                                double amount) {
    if (!running) return false;

    Account* source = database.findAccount(sourceAccount);
    Account* dest = database.findAccount(destAccount);

    if (!source || !dest) {
        Logger::getInstance().error("Transfer failed: Account not found");
        return false;
    }

    return source->transfer(*dest, amount);
}

Account* BankSystem::getAccount(const std::string& accountNumber) {
    return database.findAccount(accountNumber);
}

Customer* BankSystem::getCustomer(const std::string& customerId) {
    return database.findCustomer(customerId);
}

double BankSystem::getAccountBalance(const std::string& accountNumber) {
    Account* account = database.findAccount(accountNumber);
    if (account) {
        return account->getBalance();
    }
    return -1.0;
}

void BankSystem::printSystemStatus() {
    std::cout << "\n========== Bank System Status ==========" << std::endl;
    std::cout << "Status: " << (running ? "RUNNING" : "STOPPED") << std::endl;
    std::cout << "Customers: " << database.getCustomerCount() << std::endl;
    std::cout << "Accounts: " << database.getAccountCount() << std::endl;
    std::cout << "Transactions: " << transactionCounter << std::endl;
    std::cout << "======================================\n" << std::endl;
}

std::string BankSystem::getSystemStatus() const {
    std::stringstream ss;
    ss << "Running: " << (running ? "Yes" : "No");
    ss << ", Customers: " << database.getCustomerCount();
    ss << ", Accounts: " << database.getAccountCount();
    return ss.str();
}

std::string BankSystem::generateTransactionId() {
    return "TXN_" + std::to_string(++transactionCounter);
}

bool BankSystem::validateTransaction(const Transaction& transaction) {
    return transaction.validate();
}
