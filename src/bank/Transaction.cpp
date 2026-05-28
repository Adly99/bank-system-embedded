#include "bank/Transaction.h"
#include "utils/Logger.h"
#include <ctime>

using namespace bank;
using namespace utils;

Transaction::Transaction(const std::string& id, TransactionType type,
                        double amount, const std::string& sourceAccount)
    : transactionId(id), type(type), amount(amount), sourceAccount(sourceAccount),
      status(PENDING), timestamp(std::time(nullptr)), description("") {
}

Transaction::~Transaction() {
}

bool Transaction::validate() const {
    if (amount <= 0) {
        return false;
    }
    if (sourceAccount.empty()) {
        return false;
    }
    if (type == TRANSFER && destinationAccount.empty()) {
        return false;
    }
    return true;
}

void Transaction::markComplete() {
    status = COMPLETED;
    Logger::getInstance().info("Transaction completed: " + transactionId);
}

void Transaction::markFailed(const std::string& reason) {
    status = FAILED;
    failureReason = reason;
    Logger::getInstance().warning("Transaction failed: " + transactionId + " - " + reason);
}

std::string Transaction::getStatusString() const {
    switch (status) {
        case PENDING:
            return "PENDING";
        case COMPLETED:
            return "COMPLETED";
        case FAILED:
            return "FAILED";
        case CANCELLED:
            return "CANCELLED";
        default:
            return "UNKNOWN";
    }
}
