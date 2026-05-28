# QNX ARM Toolchain File
# This file configures CMake for cross-compilation to QNX RTOS on ARM targets

# Set the system name
set(CMAKE_SYSTEM_NAME QNX)
set(CMAKE_SYSTEM_PROCESSOR arm)

# QNX environment variables (adjust path as needed)
# Typically QNX_HOST and QNX_TARGET should be set in environment
if(NOT DEFINED QNX_HOST)
    set(QNX_HOST /opt/qnx700/host/linux/x86_64)
endif()

if(NOT DEFINED QNX_TARGET)
    set(QNX_TARGET /opt/qnx700/target/qnx7)
endif()

message(STATUS "QNX Toolchain Configuration")
message(STATUS "QNX_HOST: ${QNX_HOST}")
message(STATUS "QNX_TARGET: ${QNX_TARGET}")

# Set the C and C++ compilers
set(CMAKE_C_COMPILER ${QNX_HOST}/usr/bin/arm-unknown-nto-qnx7.0.0-gcc)
set(CMAKE_CXX_COMPILER ${QNX_HOST}/usr/bin/arm-unknown-nto-qnx7.0.0-g++)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# Set other tools
set(CMAKE_AR ${QNX_HOST}/usr/bin/arm-unknown-nto-qnx7.0.0-ar CACHE FILEPATH "ar")
set(CMAKE_RANLIB ${QNX_HOST}/usr/bin/arm-unknown-nto-qnx7.0.0-ranlib CACHE FILEPATH "ranlib")
set(CMAKE_STRIP ${QNX_HOST}/usr/bin/arm-unknown-nto-qnx7.0.0-strip CACHE FILEPATH "strip")

# Set compiler flags for ARM embedded system
set(CMAKE_C_FLAGS "-march=armv7-a -mtune=cortex-a9 -mfpu=neon -mfloat-abi=hard -fPIC" CACHE STRING "C flags")
set(CMAKE_CXX_FLAGS "-march=armv7-a -mtune=cortex-a9 -mfpu=neon -mfloat-abi=hard -fPIC" CACHE STRING "C++ flags")

# Include directories for QNX
set(CMAKE_FIND_ROOT_PATH ${QNX_TARGET}/armle-v7hf)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Skip compiler tests
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# QNX specific definitions
add_definitions(-D__QNX__ -D_POSIX_C_SOURCE=200809L)

message(STATUS "QNX ARM Toolchain Configured Successfully")
