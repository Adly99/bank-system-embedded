#include <iostream>
#include <iomanip>
#include "bank/BankSystem.h"
#include "security/Authentication.h"
#include "security/SecurityManager.h"
#include "utils/Logger.h"
#include "utils/Helper.h"

using namespace std;
using namespace bank;
using namespace security;
using namespace utils;

void printHeader() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════╗\n";
    cout << "║     Embedded Bank System v1.0.0            ║\n";
    cout << "║     QNX RTOS ARM Platform                  ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    cout << "\n";
}

void demonstrateSystem() {
    BankSystem bankSystem;

    cout << "[*] Initializing Bank System..." << endl;
    if (!bankSystem.initialize()) {
        cerr << "[ERROR] Failed to initialize Bank System" << endl;
        return;
    }

    cout << "[+] Bank System initialized successfully\n" << endl;

    cout << "[*] Registering customers..." << endl;
    bankSystem.registerCustomer("CUST001", "Ahmed Ali", "ahmed.ali@bank.com", Customer::INDIVIDUAL);
    bankSystem.registerCustomer("CUST002", "Sarah Smith", "sarah.smith@bank.com", Customer::INDIVIDUAL);
    bankSystem.registerCustomer("CUST003", "Tech Corp", "info@techcorp.com", Customer::CORPORATE);
    cout << "[+] Customers registered successfully\n" << endl;

    cout << "[*] Creating bank accounts..." << endl;
    bankSystem.createAccount("CUST001", "ACC001", Account::SAVINGS, 5000.00);
    bankSystem.createAccount("CUST001", "ACC002", Account::CHECKING, 2000.00);
    bankSystem.createAccount("CUST002", "ACC003", Account::INVESTMENT, 10000.00);
    bankSystem.createAccount("CUST003", "ACC004", Account::CHECKING, 50000.00);
    cout << "[+] Accounts created successfully\n" << endl;

    cout << "[*] Performing transactions..." << endl;

    cout << "  - Deposit $1500 to ACC001..." << endl;
    bankSystem.processDeposit("ACC001", 1500.00);

    cout << "  - Withdraw $500 from ACC001..." << endl;
    bankSystem.processWithdrawal("ACC001", 500.00);

    cout << "  - Transfer $2000 from ACC001 to ACC003..." << endl;
    bankSystem.processTransfer("ACC001", "ACC003", 2000.00);

    cout << "[+] Transactions completed\n" << endl;

    cout << "[*] Account Information:" << endl;
    cout << "  ACC001 Balance: $" << fixed << setprecision(2) 
         << bankSystem.getAccountBalance("ACC001") << endl;
    cout << "  ACC002 Balance: $" << fixed << setprecision(2) 
         << bankSystem.getAccountBalance("ACC002") << endl;
    cout << "  ACC003 Balance: $" << fixed << setprecision(2) 
         << bankSystem.getAccountBalance("ACC003") << endl;
    cout << "  ACC004 Balance: $" << fixed << setprecision(2) 
         << bankSystem.getAccountBalance("ACC004") << endl;
    cout << "\n";

    cout << "[*] Testing security features..." << endl;
    Authentication auth;
    Authentication::AuthToken token = auth.authenticate("CUST001", "password123");
    if (token.valid) {
        cout << "[+] User authenticated successfully" << endl;
        cout << "    Token: " << token.token << endl;
        cout << "    Expires: " << token.expiresAt << endl;
    }
    cout << "\n";

    cout << "[*] Testing utility functions..." << endl;
    cout << "  - Email validation (ahmed.ali@bank.com): " 
         << (Helper::isValidEmail("ahmed.ali@bank.com") ? "VALID" : "INVALID") << endl;
    cout << "  - Account number validation (ACC001): " 
         << (Helper::isValidAccountNumber("ACC001") ? "VALID" : "INVALID") << endl;
    cout << "  - Password strength check: " 
         << (Helper::isStrongPassword("SecurePass123!") ? "STRONG" : "WEAK") << endl;
    cout << "  - Amount formatting: $" << Helper::formatMoney(1234.567) << endl;
    cout << "\n";

    cout << "[*] System Status:" << endl;
    bankSystem.printSystemStatus();

    cout << "[*] Shutting down Bank System..." << endl;
    bankSystem.shutdown();
    cout << "[+] Bank System shut down successfully\n" << endl;
}

int main() {
    try {
        printHeader();

        cout << "Platform: ";
#ifdef PLATFORM_QNX
        cout << "QNX RTOS (ARM)" << endl;
#elif defined(PLATFORM_UNIX)
        cout << "Unix/Linux" << endl;
#elif defined(PLATFORM_WINDOWS)
        cout << "Windows" << endl;
#else
        cout << "Unknown" << endl;
#endif

        cout << "Build Type: ";
#ifdef NDEBUG
        cout << "Release" << endl;
#else
        cout << "Debug" << endl;
#endif

        cout << "\nStarting demonstration...\n" << endl;

        demonstrateSystem();

        cout << "[+] Program completed successfully" << endl;
        cout << "\nBank System logs available in: bank_system.log\n" << endl;

        return 0;
    }
    catch (const exception& e) {
        cerr << "[ERROR] Exception: " << e.what() << endl;
        return 1;
    }
}
