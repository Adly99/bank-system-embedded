# Bank System - Embedded C++ Project

A comprehensive embedded C++ banking system designed for QNX RTOS and ARM platforms with CMake build support.

## Project Overview

This is an enterprise-grade banking system implementation in C++ targeting embedded systems, particularly QNX RTOS on ARM architecture. It includes:

- **Account Management**: SAVINGS, CHECKING, and INVESTMENT account types
- **Customer Management**: Individual, Corporate, and VIP customer types
- **Transaction Processing**: Deposits, withdrawals, and transfers
- **Security**: Authentication, encryption, and audit logging
- **Database**: In-memory database with backup/restore capabilities
- **Logging**: Comprehensive logging system

## Directory Structure

```
bank-system-embedded/
├── CMakeLists.txt
├── toolchain_qnx_arm.cmake
├── build.cmd
├── README.md
├── include/
│   ├── bank/
│   │   ├── Account.h
│   │   ├── Customer.h
│   │   ├── Transaction.h
│   │   ├── Database.h
│   │   └── BankSystem.h
│   ├── security/
│   │   ├── SecurityManager.h
│   │   └── Authentication.h
│   └── utils/
│       ├── Logger.h
│       └── Helper.h
└── src/
    ├── main.cpp
    ├── bank/
    │   ├── Account.cpp
    │   ├── Customer.cpp
    │   ├── Transaction.cpp
    │   ├── Database.cpp
    │   └── BankSystem.cpp
    ├── security/
    │   ├── SecurityManager.cpp
    │   └── Authentication.cpp
    └── utils/
        ├── Logger.cpp
        └── Helper.cpp
```

## Requirements

### System Requirements
- C++17 compatible compiler
- CMake 3.10 or higher
- ARM cross-compilation toolchain (for QNX builds)

### Build Requirements
- **Windows**: Visual Studio 2019 or higher
- **Linux/Unix**: GCC/Clang with ARM toolchain
- **QNX**: QNX 7.0 or higher with ARM support

## Building the Project

### Quick Start - Windows Native Build

```bash
build.cmd
```

### Debug Build

```bash
build.cmd --debug
```

### QNX Cross-Compilation

```bash
build.cmd --qnx
```

### Full Clean Rebuild

```bash
build.cmd --clean --qnx
```

### Manual CMake Build (Windows)

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Manual CMake Build (Linux/Unix)

```bash
mkdir build
cd build
cmake ..
make
```

### Manual CMake Build (QNX Cross-Compile)

```bash
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain_qnx_arm.cmake ..
make
```

## Build Output

After successful build:
- **Executable**: `build/bin/bank_system_embedded` (Linux/Unix) or `build\bin\bank_system_embedded.exe` (Windows)
- **Log Files**: `bank_system.log` (generated at runtime)
- **Install Directory**: `install/` (after running cmake install)

## Running the Application

### Linux/Unix/QNX
```bash
./build/bin/bank_system_embedded
```

### Windows
```bash
build\bin\bank_system_embedded.exe
```

## Features

### Core Banking Features
- ✅ Customer registration and management
- ✅ Multiple account types (SAVINGS, CHECKING, INVESTMENT)
- ✅ Deposit and withdrawal operations
- ✅ Fund transfers between accounts
- ✅ Transaction history tracking
- ✅ Account activation/deactivation

### Security Features
- ✅ User authentication with tokens
- ✅ Password encryption and verification
- ✅ Two-factor authentication support
- ✅ Audit logging for all operations
- ✅ Rate limiting for brute-force protection
- ✅ Session management

### Utility Features
- ✅ Email validation
- ✅ Account number validation
- ✅ Password strength checking
- ✅ Money formatting
- ✅ String manipulation utilities
- ✅ UUID generation
- ✅ Random string generation

### System Features
- ✅ Comprehensive logging system
- ✅ In-memory database with serialization
- ✅ Database backup/restore
- ✅ System status monitoring
- ✅ Cross-platform compatibility
- ✅ Embedded system optimization

## Class Architecture

### Bank Module (`bank/`)
- **Account**: Manages individual bank accounts
- **Customer**: Manages customer information and associated accounts
- **Transaction**: Tracks transaction details and status
- **Database**: Singleton database management
- **BankSystem**: Main system orchestrator

### Security Module (`security/`)
- **SecurityManager**: Encryption, hashing, session management
- **Authentication**: User authentication and token management

### Utilities Module (`utils/`)
- **Logger**: Comprehensive logging with file output
- **Helper**: String, numeric, and validation utilities

## QNX Toolchain Configuration

The `toolchain_qnx_arm.cmake` file configures:
- QNX RTOS as target platform
- ARM Cortex-A9 architecture
- NEON SIMD extensions
- Hard-float ABI
- Position-independent code generation

### Environment Variables
Set these before building:
```bash
export QNX_HOST=/opt/qnx700/host/linux/x86_64
export QNX_TARGET=/opt/qnx700/target/qnx7
```

## Example Usage

```cpp
#include "bank/BankSystem.h"
using namespace bank;

int main() {
    BankSystem system;
    system.initialize();
    
    // Register customer
    system.registerCustomer("CUST001", "John Doe", "john@example.com", 
                          Customer::INDIVIDUAL);
    
    // Create account
    system.createAccount("CUST001", "ACC001", Account::SAVINGS, 1000.00);
    
    // Process transactions
    system.processDeposit("ACC001", 500.00);
    system.processWithdrawal("ACC001", 200.00);
    
    // Get account balance
    double balance = system.getAccountBalance("ACC001");
    
    system.shutdown();
    return 0;
}
```

## Compiler Flags

### Optimization Flags
- **Release**: `-O2 -s` (optimized, stripped)
- **Debug**: `-g` (debug symbols)

### Security Flags
- `-ftrapv` (trap on integer overflow)
- `-Wall -Wextra -Wpedantic` (enhanced warnings)
- `-Werror=unused-result` (treat unused results as errors)

### Platform-Specific
- **ARM**: `-march=armv7-a -mtune=cortex-a9 -mfpu=neon -mfloat-abi=hard`
- **QNX**: `-D__QNX__ -D_POSIX_C_SOURCE=200809L`

## Build Configuration Options

In CMakeLists.txt, you can customize:
- `CMAKE_BUILD_TYPE`: Debug or Release
- `CMAKE_CXX_STANDARD`: C++ standard version
- Compiler-specific flags
- Platform definitions

## Future Enhancements

- [ ] Persistent database (SQLite integration)
- [ ] Network communication (TCP/UDP sockets)
- [ ] Real-time notifications
- [ ] Advanced encryption (AES-256)
- [ ] Mobile app integration
- [ ] Machine learning fraud detection
- [ ] REST API interface

## License

Proprietary - Bank System Embedded v1.0.0

## Support

For issues and questions, refer to the documentation or contact the development team.

## Version History

### v1.0.0 (Current)
- Initial release
- Core banking functionality
- Security features
- QNX/ARM platform support
- CMake build system

---

**Last Updated**: 2026-05-28
**Platform**: QNX RTOS ARM / Unix-like embedded systems
**Maintainer**: Development Team
