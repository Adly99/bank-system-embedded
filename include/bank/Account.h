#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <ctime>
#include "Transaction.h"

namespace bank {

class Account {
public:
    enum AccountType {
        SAVINGS,
        CHECKING,
        INVESTMENT
    };

    Account(const std::string& accountNumber, const std::string& customerName, 
            AccountType type, double initialBalance);
    ~Account();

    // Getters
    std::string getAccountNumber() const { return accountNumber; }
    std::string getCustomerName() const { return customerName; }
    double getBalance() const { return balance; }
    AccountType getType() const { return type; }
    time_t getCreationDate() const { return creationDate; }
    bool isActive() const { return active; }

    // Account operations
    bool deposit(double amount);
    bool withdraw(double amount);
    bool transfer(Account& targetAccount, double amount);
    void deactivate();
    void activate();

    // Transaction history
    void addTransaction(const Transaction& transaction);
    std::vector<Transaction> getTransactionHistory() const { return transactions; }

private:
    std::string accountNumber;
    std::string customerName;
    double balance;
    AccountType type;
    time_t creationDate;
    bool active;
    std::vector<Transaction> transactions;

    // Validation
    bool validateAmount(double amount) const;
};

} // namespace bank

#endif // ACCOUNT_H
