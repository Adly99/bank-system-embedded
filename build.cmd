@echo off
REM Bank System Embedded Build Script for Windows
REM Supports both native Windows and QNX cross-compilation builds
REM Enhanced with: incremental builds, parallel compilation, verbose mode, and build timing

setlocal enabledelayedexpansion

REM Start timer
for /f "tokens=1-4 delims=:.," %%A in ("%time%") do (
    set /a START_TIME=(%%A*3600000)+(%%B*60000)+(%%C*1000)+%%D
)

echo.
echo ============================================
echo Bank System Embedded - Build Script v2.0
echo ============================================
echo.

REM Set default values
set BUILD_TYPE=Release
set TARGET_PLATFORM=native
set CMAKE_GENERATOR="Visual Studio 17 2022"
set BUILD_DIR=build
set INSTALL_DIR=install
set INCREMENTAL_BUILD=0
set VERBOSE_BUILD=0
set BUILD_JOBS=0
set SKIP_CONFIG=0

REM Parse command line arguments
:parse_args
if "%1"=="" goto args_done

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
    set INCREMENTAL_BUILD=0
    shift
    goto parse_args
)
if "%1"=="--incremental" (
    set INCREMENTAL_BUILD=1
    shift
    goto parse_args
)
if "%1"=="--verbose" (
    set VERBOSE_BUILD=1
    shift
    goto parse_args
)
if "%1"=="--jobs" (
    if not "%2"=="" (
        set BUILD_JOBS=%2
        shift
        shift
        goto parse_args
    )
)
if "%1"=="--ninja" (
    set CMAKE_GENERATOR="Ninja"
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
echo - Build Type:        %BUILD_TYPE%
echo - Target Platform:   %TARGET_PLATFORM%
echo - Build Directory:   %BUILD_DIR%
echo - Incremental:       %INCREMENTAL_BUILD%
echo - Verbose:           %VERBOSE_BUILD%
if %BUILD_JOBS% gtr 0 echo - Parallel Jobs:     %BUILD_JOBS%
echo.

REM Clean previous build if not incremental
if %INCREMENTAL_BUILD% equ 0 (
    if exist %BUILD_DIR% (
        echo Cleaning previous build...
        rmdir /s /q %BUILD_DIR% 2>nul
        if exist %INSTALL_DIR% rmdir /s /q %INSTALL_DIR% 2>nul
        echo Clean completed.
        echo.
    )
    set SKIP_CONFIG=0
) else (
    set SKIP_CONFIG=1
    echo Using incremental build (skipping clean)
    echo.
)

REM Create build directory
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

REM Configure based on platform (skip if incremental and cache exists)
if %SKIP_CONFIG% equ 0 (
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
        cd ..
        exit /b 1
    )
    cd ..
    echo CMake configuration completed.
    echo.
) else (
    echo Skipping CMake configuration (using cached config)
    echo.
)

REM Build project
echo Building project...
cd /d %BUILD_DIR%

set BUILD_CMD=cmake --build . --config %BUILD_TYPE%
if %VERBOSE_BUILD% equ 1 (
    set BUILD_CMD=!BUILD_CMD! --verbose
)
if %BUILD_JOBS% gtr 0 (
    set BUILD_CMD=!BUILD_CMD! --parallel %BUILD_JOBS%
) else (
    set BUILD_CMD=!BUILD_CMD! --parallel
)

!BUILD_CMD!

if errorlevel 1 (
    echo Build failed!
    cd ..
    exit /b 1
)

echo Build completed successfully.
echo.

REM Install project
echo Installing project...
cmake --install . --config %BUILD_TYPE% --prefix ..\%INSTALL_DIR%

if errorlevel 1 (
    echo Installation failed!
    cd ..
    exit /b 1
)

cd ..

echo.
echo ============================================
echo Build Completed Successfully!
echo ============================================

REM Calculate elapsed time
for /f "tokens=1-4 delims=:.," %%A in ("%time%") do (
    set /a END_TIME=(%%A*3600000)+(%%B*60000)+(%%C*1000)+%%D
)

set /a ELAPSED_MS=!END_TIME!-!START_TIME!
if %ELAPSED_MS% lss 0 set /a ELAPSED_MS=%ELAPSED_MS%+86400000

set /a ELAPSED_S=!ELAPSED_MS!/1000
set /a ELAPSED_M=!ELAPSED_S!/60
set /a ELAPSED_S=!ELAPSED_S!%%60

echo Build Time: !ELAPSED_M!m !ELAPSED_S!s
echo.
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
echo   --debug          Build with debug symbols
echo   --release        Build with optimizations (default)
echo   --qnx            Build for QNX ARM target (cross-compile)
echo   --clean          Clean and rebuild (default)
echo   --incremental    Incremental build (skip clean)
echo   --verbose        Show detailed build output
echo   --jobs N         Use N parallel jobs (default: auto-detect)
echo   --ninja          Use Ninja generator instead of Visual Studio
echo   --help           Show this help message
echo.
echo Examples:
echo   build.cmd                           - Build native Release (clean)
echo   build.cmd --debug                   - Build native Debug (clean)
echo   build.cmd --incremental --verbose   - Incremental build with verbose output
echo   build.cmd --qnx --clean             - Clean and build for QNX
echo   build.cmd --jobs 4                  - Build with 4 parallel jobs
echo   build.cmd --ninja --release         - Build with Ninja generator
echo.

:end
endlocal
