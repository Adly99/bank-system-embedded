#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>
#include <vector>
#include "Account.h"
#include "Customer.h"

namespace bank {

class Database {
public:
    static Database& getInstance();

    // Customer operations
    bool addCustomer(Customer* customer);
    bool removeCustomer(const std::string& customerId);
    Customer* findCustomer(const std::string& customerId);
    std::vector<Customer*> getAllCustomers();

    // Account operations
    bool addAccount(Account* account);
    bool removeAccount(const std::string& accountNumber);
    Account* findAccount(const std::string& accountNumber);
    std::vector<Account*> getAllAccounts();

    // Database operations
    bool backup(const std::string& filename);
    bool restore(const std::string& filename);
    void clear();
    int getCustomerCount() const { return customers.size(); }
    int getAccountCount() const { return accounts.size(); }

private:
    Database() = default;
    ~Database();

    // Delete copy constructor and assignment operator
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    std::map<std::string, Customer*> customers;
    std::map<std::string, Account*> accounts;

    // Serialization helpers
    bool serializeData(const std::string& filename);
    bool deserializeData(const std::string& filename);
};

} // namespace bank

#endif // DATABASE_H
