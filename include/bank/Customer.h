#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <ctime>
#include "Account.h"

namespace bank {

class Customer {
public:
    enum CustomerType {
        INDIVIDUAL,
        CORPORATE,
        VIP
    };

    Customer(const std::string& id, const std::string& name, 
             const std::string& email, CustomerType type);
    ~Customer();

    // Getters
    std::string getCustomerId() const { return customerId; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    CustomerType getType() const { return type; }
    time_t getRegistrationDate() const { return registrationDate; }
    bool isVerified() const { return verified; }

    // Account management
    bool addAccount(const Account& account);
    bool removeAccount(const std::string& accountNumber);
    Account* findAccount(const std::string& accountNumber);
    std::vector<Account*> getAllAccounts() { return accounts; }

    // Customer verification
    bool verifyCustomer();
    void updateVerificationStatus(bool status) { verified = status; }

    // Profile updates
    void updateEmail(const std::string& newEmail) { email = newEmail; }

private:
    std::string customerId;
    std::string name;
    std::string email;
    CustomerType type;
    time_t registrationDate;
    bool verified;
    std::vector<Account*> accounts;

    bool validateEmail(const std::string& email) const;
};

} // namespace bank

#endif // CUSTOMER_H
