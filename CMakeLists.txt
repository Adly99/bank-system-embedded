cmake_minimum_required(VERSION 3.10)
project(BankSystemEmbedded C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_INIT "-fPIC -Wall -Wextra")

# Embedded system specific settings
set(EMBEDDED_SYSTEM TRUE)
set(BANK_SYSTEM_VERSION 1.0.0)

# Include toolchain if cross-compiling
if(CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add source files
set(SOURCES
    src/main.cpp
    src/bank/Account.cpp
    src/bank/Customer.cpp
    src/bank/Transaction.cpp
    src/bank/Database.cpp
    src/bank/BankSystem.cpp
    src/security/SecurityManager.cpp
    src/security/Authentication.cpp
    src/utils/Logger.cpp
    src/utils/Helper.cpp
)

set(HEADERS
    include/bank/Account.h
    include/bank/Customer.h
    include/bank/Transaction.h
    include/bank/Database.h
    include/bank/BankSystem.h
    include/security/SecurityManager.h
    include/security/Authentication.h
    include/utils/Logger.h
    include/utils/Helper.h
)

# Create executable
add_executable(bank_system_embedded ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(bank_system_embedded PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Compiler flags for embedded systems
if(MSVC)
    target_compile_options(bank_system_embedded PRIVATE /W4 /WX)
else()
    target_compile_options(bank_system_embedded PRIVATE -Wall -Wextra -Wpedantic -Werror=unused-result)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        target_compile_options(bank_system_embedded PRIVATE -ftrapv)
    endif()
endif()

# Optimization for embedded systems
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(bank_system_embedded PRIVATE -O2 -s)
else()
    target_compile_options(bank_system_embedded PRIVATE -g)
endif()

# Platform-specific settings
if(UNIX AND NOT APPLE)
    message(STATUS "Building for Unix/Linux embedded system")
    target_compile_definitions(bank_system_embedded PRIVATE PLATFORM_UNIX)
elseif(WIN32)
    message(STATUS "Building for Windows embedded system")
    target_compile_definitions(bank_system_embedded PRIVATE PLATFORM_WINDOWS)
endif()

# QNX specific settings
if(QNX)
    message(STATUS "Building for QNX RTOS")
    target_compile_definitions(bank_system_embedded PRIVATE PLATFORM_QNX)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lsocket")
endif()

# Add embedded system definitions
target_compile_definitions(bank_system_embedded PRIVATE 
    EMBEDDED_SYSTEM=1
    BANK_SYSTEM_VERSION="${BANK_SYSTEM_VERSION}"
)

# Display build information
message(STATUS "================================")
message(STATUS "Bank System Embedded Build Info")
message(STATUS "================================")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Version: ${BANK_SYSTEM_VERSION}")
message(STATUS "Output: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "================================")
