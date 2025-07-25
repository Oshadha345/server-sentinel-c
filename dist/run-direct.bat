@echo off
cd /d "%~dp0"
set PATH=%~dp0;%PATH%
set XDG_DATA_DIRS=%~dp0share
server-sentinel.exe
pause
