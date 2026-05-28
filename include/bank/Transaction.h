#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

namespace bank {

class Transaction {
public:
    enum TransactionType {
        DEPOSIT,
        WITHDRAWAL,
        TRANSFER,
        INTEREST
    };

    enum TransactionStatus {
        PENDING,
        COMPLETED,
        FAILED,
        CANCELLED
    };

    Transaction(const std::string& id, TransactionType type, 
                double amount, const std::string& sourceAccount);
    ~Transaction();

    // Getters
    std::string getTransactionId() const { return transactionId; }
    TransactionType getType() const { return type; }
    double getAmount() const { return amount; }
    std::string getSourceAccount() const { return sourceAccount; }
    std::string getDestinationAccount() const { return destinationAccount; }
    TransactionStatus getStatus() const { return status; }
    time_t getTimestamp() const { return timestamp; }
    std::string getDescription() const { return description; }

    // Setters
    void setDestinationAccount(const std::string& account) { destinationAccount = account; }
    void setStatus(TransactionStatus newStatus) { status = newStatus; }
    void setDescription(const std::string& desc) { description = desc; }

    // Transaction operations
    bool validate() const;
    void markComplete();
    void markFailed(const std::string& reason);
    std::string getStatusString() const;

private:
    std::string transactionId;
    TransactionType type;
    double amount;
    std::string sourceAccount;
    std::string destinationAccount;
    TransactionStatus status;
    time_t timestamp;
    std::string description;
    std::string failureReason;
};

} // namespace bank

#endif // TRANSACTION_H
