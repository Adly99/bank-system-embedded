@echo off
REM Bank System Embedded Build Script for Windows
REM Supports both native Windows and QNX cross-compilation builds

setlocal enabledelayedexpansion

echo.
echo ============================================
echo Bank System Embedded - Build Script
echo ============================================
echo.

REM Set default values
set BUILD_TYPE=Release
set TARGET_PLATFORM=native
set CMAKE_GENERATOR="Visual Studio 16 2019"
set BUILD_DIR=build
set INSTALL_DIR=install

REM Parse command line arguments
:parse_args
if "%1"==\"\" goto args_done
if "%1"=="--debug" (
    set BUILD_TYPE=Debug
    shift
    goto parse_args
)
if "%1"=="--release" (
    set BUILD_TYPE=Release
    shift
    goto parse_args
)
if "%1"=="--qnx" (
    set TARGET_PLATFORM=qnx
    shift
    goto parse_args
)
if "%1"=="--clean" (
    set CLEAN_BUILD=1
    shift
    goto parse_args
)
if "%1"=="--help" (
    goto show_help
)
shift
goto parse_args

:args_done

REM Display configuration
echo Build Configuration:
echo - Build Type: %BUILD_TYPE%
echo - Target Platform: %TARGET_PLATFORM%
echo - Build Directory: %BUILD_DIR%
echo.

REM Clean previous build if requested
if defined CLEAN_BUILD (
    echo Cleaning previous build...
    if exist %BUILD_DIR% rmdir /s /q %BUILD_DIR%
    if exist %INSTALL_DIR% rmdir /s /q %INSTALL_DIR%
    echo Clean completed.
    echo.
)

REM Create build directory
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

REM Configure based on platform
echo Configuring CMake...
cd /d %BUILD_DIR%

if "%TARGET_PLATFORM%"=="qnx" (
    echo Configuring for QNX ARM cross-compilation...
    cmake -G %CMAKE_GENERATOR% ^
        -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
        -DCMAKE_TOOLCHAIN_FILE=../toolchain_qnx_arm.cmake ^
        -DQNX=ON ^
        ..
) else (
    echo Configuring for native Windows build...
    cmake -G %CMAKE_GENERATOR% ^
        -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
        ..
)

if errorlevel 1 (
    echo CMAKE configuration failed!
    exit /b 1
)

echo.
echo Building project...
cmake --build . --config %BUILD_TYPE%

if errorlevel 1 (
    echo Build failed!
    exit /b 1
)

echo.
echo Installing project...
cmake --install . --config %BUILD_TYPE% --prefix ..\ %INSTALL_DIR%

if errorlevel 1 (
    echo Installation failed!
    exit /b 1
)

cd ..

echo.
echo ============================================
echo Build Completed Successfully!
echo ============================================
echo Output:
echo - Executable: %INSTALL_DIR%\bin\bank_system_embedded.exe
echo - Build logs: %BUILD_DIR%\CMakeFiles
echo.

goto end

:show_help
echo.
echo Usage: build.cmd [OPTIONS]
echo.
echo Options:
echo   --debug        Build with debug symbols
echo   --release      Build with optimizations (default)
echo   --qnx          Build for QNX ARM target (cross-compile)
echo   --clean        Clean previous build before building
echo   --help         Show this help message
echo.
echo Examples:
echo   build.cmd                    - Build native Release
echo   build.cmd --debug            - Build native Debug
echo   build.cmd --qnx --clean      - Clean and build for QNX
echo.

:end
endlocal
