@echo off
REM Argosy Tides - Setup Script
REM This script helps set up the development environment

echo ============================================
echo Argosy Tides - Development Setup
echo ============================================
echo.

REM Check for Visual Studio
echo [1/5] Checking for Visual Studio...
set VSWHERE="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist %VSWHERE% (
    echo ERROR: Visual Studio Installer not found!
    echo Please install Visual Studio 2022 with C++ workload.
    echo Download: https://visualstudio.microsoft.com/downloads/
    echo.
    pause
    exit /b 1
)

REM Check for VS with C++ tools
for /f "tokens=*" %%i in ('%VSWHERE% -latest -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath') do set VS_INSTALL=%%i
if "%VS_INSTALL%"=="" (
    echo ERROR: Visual Studio C++ tools not found!
    echo Please install "Game development with C++" workload.
    echo.
    pause
    exit /b 1
)
echo Found Visual Studio: %VS_INSTALL%
echo.

REM Check for Unreal Engine
echo [2/5] Checking for Unreal Engine...
set UE5_PATH="C:\Program Files\Epic Games\UE_5.4"
if not exist %UE5_PATH% (
    echo WARNING: Unreal Engine 5.4 not found at default location
    echo Please update UE5_PATH in this script if installed elsewhere
    echo.
) else (
    echo Found Unreal Engine: %UE5_PATH%
)
echo.

REM Check for Rust
echo [3/5] Checking for Rust...
where rustc >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo WARNING: Rust not found in PATH
    echo Rust is installed but may need PATH update
    echo.
) else (
    rustc --version
)
echo.

REM Initialize Git LFS
echo [4/5] Initializing Git LFS...
git lfs install
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Git LFS initialization failed
    echo.
    pause
    exit /b 1
)
echo.

REM Verify project structure
echo [5/5] Verifying project structure...
if not exist "ArgosyTides.uproject" (
    echo ERROR: ArgosyTides.uproject not found!
    echo.
    pause
    exit /b 1
)
if not exist "Source\ArgosyTides\ArgosyTides.Build.cs" (
    echo ERROR: Source files not found!
    echo.
    pause
    exit /b 1
)
echo Project structure verified.
echo.

echo ============================================
echo Setup Complete!
echo ============================================
echo.
echo Next steps:
echo 1. Open ArgosyTides.uproject in Unreal Editor
echo 2. Build Rust data pipeline (requires VS C++ tools):
echo    cd Tools\DataPipeline
echo    cargo build --release
echo.
echo See SETUP.md for detailed instructions.
echo.
pause
