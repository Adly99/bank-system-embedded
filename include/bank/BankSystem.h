#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include <string>
#include <map>
#include "Account.h"
#include "Customer.h"
#include "Transaction.h"
#include "Database.h"

namespace bank {

class BankSystem {
public:
    BankSystem();
    ~BankSystem();

    // System initialization and shutdown
    bool initialize();
    void shutdown();
    bool isRunning() const { return running; }

    // Customer management
    bool registerCustomer(const std::string& id, const std::string& name, 
                         const std::string& email, Customer::CustomerType type);
    bool createAccount(const std::string& customerId, const std::string& accountNumber,
                      Account::AccountType type, double initialBalance);

    // Transaction operations
    bool processDeposit(const std::string& accountNumber, double amount);
    bool processWithdrawal(const std::string& accountNumber, double amount);
    bool processTransfer(const std::string& sourceAccount, const std::string& destAccount, 
                        double amount);

    // Account queries
    Account* getAccount(const std::string& accountNumber);
    Customer* getCustomer(const std::string& customerId);
    double getAccountBalance(const std::string& accountNumber);

    // System status
    void printSystemStatus();
    std::string getSystemStatus() const;

private:
    Database& database;
    bool running;
    int transactionCounter;

    // Helper methods
    std::string generateTransactionId();
    bool validateTransaction(const Transaction& transaction);
};

} // namespace bank

#endif // BANKSYSTEM_H
