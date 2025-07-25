@echo off
cd /d "%~dp0"
set PATH=%~dp0;%PATH%
set XDG_DATA_DIRS=%~dp0share
echo Starting Server-Sentinel-C Server Monitor...
echo ===================================================
echo.
echo Modern GUI Server Monitoring System
echo Features: Real-time monitoring, Simulation controls, Log export
echo.
start "" "server-sentinel.exe"
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Error: Failed to start the application.
    echo Please ensure all files are present and try again.
    pause
)
