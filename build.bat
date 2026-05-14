@echo off
REM Argosy Tides - Build Script
REM Builds the project from command line

echo ============================================
echo Argosy Tides - Build
echo ============================================
echo.

REM Set Unreal Engine path
set UE5_PATH="C:\Program Files\Epic Games\UE_5.4\Engine\Build\BatchFiles"

if not exist %UE5_PATH% (
    echo ERROR: Unreal Engine build tools not found at %UE5_PATH%
    echo Please update UE5_PATH or install UE 5.4
    echo.
    pause
    exit /b 1
)

echo Building ArgosyTidesEditor for Win64 Development...
echo.

%UE5_PATH%\Build.bat ArgosyTidesEditor Win64 Development -project="%~dp0ArgosyTides.uproject" -log -wait

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ============================================
    echo BUILD SUCCESSFUL
    echo ============================================
    echo.
    echo You can now open ArgosyTides.uproject in Unreal Editor
    echo.
) else (
    echo.
    echo ============================================
    echo BUILD FAILED
    echo ============================================
    echo.
    echo Check the log for details.
    echo.
)

pause
