cmake_minimum_required(VERSION 3.10)
project(BankSystemEmbedded C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_INIT "-fPIC -Wall -Wextra")

# Project settings
set(BANK_SYSTEM_VERSION 1.0.0)

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

# Compiler flags for all platforms
if(MSVC)
    target_compile_options(bank_system_embedded PRIVATE /W4 /WX)
else()
    target_compile_options(bank_system_embedded PRIVATE -Wall -Wextra -Wpedantic -Werror=unused-result)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        target_compile_options(bank_system_embedded PRIVATE -ftrapv)
    endif()
endif()

# Optimization flags
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(NOT MSVC)
        target_compile_options(bank_system_embedded PRIVATE -O2 -s)
    else()
        target_compile_options(bank_system_embedded PRIVATE /O2)
    endif()
else()
    target_compile_options(bank_system_embedded PRIVATE -g)
endif()

# Platform detection and settings
if(WIN32)
    message(STATUS "Building for Windows platform")
    target_compile_definitions(bank_system_embedded PRIVATE PLATFORM_WINDOWS)
elseif(APPLE)
    message(STATUS "Building for macOS platform")
    target_compile_definitions(bank_system_embedded PRIVATE PLATFORM_MACOS)
elseif(UNIX)
    message(STATUS "Building for Unix/Linux platform")
    target_compile_definitions(bank_system_embedded PRIVATE PLATFORM_UNIX)
endif()

# Add project definitions
target_compile_definitions(bank_system_embedded PRIVATE 
    BANK_SYSTEM_VERSION="${BANK_SYSTEM_VERSION}"
)

# Link platform-specific libraries if needed
if(UNIX AND NOT APPLE)
    target_link_libraries(bank_system_embedded PRIVATE m)
endif()

# Display build information
message(STATUS "================================")
message(STATUS "Bank System Embedded Build Info")
message(STATUS "================================")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Version: ${BANK_SYSTEM_VERSION}")
message(STATUS "Output: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "================================")
