#!/bin/bash

echo "Creating Server-Sentinel-C Distribution Package..."
echo "================================================="

# Clean any previous distribution
rm -rf dist
mkdir -p dist

# Copy executable
echo "Copying executable..."
cp bin/server-sentinel.exe dist/

# Function to copy DLL and its dependencies
copy_dll_deps() {
    local exe_path="$1"
    local target_dir="$2"
    
    echo "Gathering DLL dependencies..."
    # Use ldd to find dependencies and copy them
    ldd "$exe_path" | grep -E "\.dll" | awk '{print $3}' | while read dll; do
        if [[ "$dll" == /mingw64/* ]]; then
            echo "  Copying: $(basename "$dll")"
            cp "$dll" "$target_dir/" 2>/dev/null || true
        fi
    done
}

# Copy all DLL dependencies
copy_dll_deps "bin/server-sentinel.exe" "dist"

# Copy essential GTK data files
echo "Copying GTK schemas and data files..."
mkdir -p dist/share/glib-2.0/schemas
if [ -d "/mingw64/share/glib-2.0/schemas" ]; then
    cp -r /mingw64/share/glib-2.0/schemas/* dist/share/glib-2.0/schemas/ 2>/dev/null || true
fi

# Copy GTK icons (if available)
if [ -d "/mingw64/share/icons" ]; then
    mkdir -p dist/share/icons
    cp -r /mingw64/share/icons/Adwaita dist/share/icons/ 2>/dev/null || true
fi

# Create launcher script
echo "Creating launcher script..."
cat > dist/Server-Sentinel-C.bat << 'EOF'
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
EOF

# Create alternative launcher for direct execution
cat > dist/run-direct.bat << 'EOF'
@echo off
cd /d "%~dp0"
set PATH=%~dp0;%PATH%
set XDG_DATA_DIRS=%~dp0share
server-sentinel.exe
pause
EOF

# Create comprehensive README
echo "Creating documentation..."
cat > dist/README.txt << 'EOF'
Server-Sentinel-C Server Monitor v1.0
==============================================

DESCRIPTION:
A modern server monitoring system designed for data centers and server rooms.
Features real-time temperature and humidity monitoring with simulation capabilities.

SYSTEM REQUIREMENTS:
- Windows 7 or later (64-bit recommended)
- Minimum 50 MB free disk space
- No additional software installation required

HOW TO RUN:
1. Double-click "Server-Sentinel-C.bat" (Recommended)
2. OR double-click "run-direct.bat" for console output
3. OR run "server-sentinel.exe" directly

FEATURES:
✓ Real-time server monitoring
✓ Modern GUI with ChatGPT-inspired design
✓ Temperature simulation (20-25°C nominal, up to 90-110°C heating)
✓ Humidity monitoring and spike simulation
✓ System state management (Normal/Caution/Danger/Shutdown)
✓ Start/Stop simulation controls
✓ Live log display (120 entries, newest first)
✓ Log file export with timestamp naming
✓ Various scenario testing modes
✓ Critical timer with automatic shutdown protection

GUI CONTROLS:
- Start/Stop Simulation: Control the monitoring simulation
- Scenarios: Test different environmental conditions
  * Stable: Normal operating conditions
  * Heating Up: Temperature increase simulation
  * Cooling Down: Temperature decrease simulation
  * Humidity Spike: Humidity control failure
  * Intermittent Failure: Cycling environmental issues
- Response: System management actions
  * Fail Cooling: Simulate cooling system failure
  * Fix System: Apply corrective measures
- System: Application controls
  * Show Log: View detailed log entries
  * Export Log: Save logs to file with timestamp
  * Exit: Close application

TECHNICAL DETAILS:
- Built with C and GTK4
- Cross-platform compatible (Windows distribution)
- Portable - no installation required
- All dependencies included

TROUBLESHOOTING:
- If the application doesn't start, try "run-direct.bat" to see error messages
- Ensure all files in this folder remain together
- Check that you have sufficient permissions to run executables
- For Windows Defender warnings, add the folder to exclusions

ABOUT:
Created as part of CO253 Software Construction Project
Group 20 - University of Moratuwa
Copyright (C) 2025

For support or questions, refer to the project documentation.

Enjoy monitoring your environment with Server-Sentinel-C!
EOF

# Create installation instructions
cat > dist/INSTALL.txt << 'EOF'
Server-Sentinel-C Installation Instructions
===========================================

QUICK START:
1. Extract all files to a folder on your computer
2. Double-click "Server-Sentinel-C.bat"
3. The application will start automatically

DETAILED SETUP:
1. Choose a permanent location for the application
   (e.g., C:\Program Files\Server-Sentinel-C)

2. Extract/copy all files from this package to that location

3. Ensure the following files are present:
   - server-sentinel.exe (main application)
   - Server-Sentinel-C.bat (launcher)
   - run-direct.bat (alternative launcher)
   - All .dll files (GTK dependencies)
   - share/ folder (GTK data files)
   - README.txt (this documentation)

4. Optional: Create a desktop shortcut
   - Right-click "Server-Sentinel-C.bat"
   - Select "Create shortcut"
   - Move shortcut to desktop
   - Rename as desired

SHARING WITH OTHERS:
- Zip this entire folder to share
- Recipients just need to extract and run
- No additional installation required
- Works on any Windows computer

UNINSTALLATION:
- Simply delete the application folder
- No registry entries or system files modified
- Completely portable application
EOF

# Create version info file
cat > dist/VERSION.txt << 'EOF'
Server-Sentinel-C Version Information
====================================

Version: 1.0.0
Build Date: 2025-07-25
Build Type: GUI-Only Release

Components:
- Core Engine: C99 Standard
- GUI Framework: GTK4
- Platform: Windows (MINGW64)
- Architecture: x64

Features in this release:
✓ Modern GUI interface
✓ Real-time server monitoring
✓ Temperature simulation with bounds
✓ Humidity monitoring
✓ Scenario testing modes
✓ Log export functionality
✓ Critical timer system
✓ Auto-shutdown protection

Dependencies included:
- GTK4 runtime libraries
- GLib/GObject libraries
- Cairo graphics libraries
- Pango text rendering
- All required DLLs

This is a complete, self-contained distribution.
EOF

# Count files and calculate size
echo ""
echo "Distribution package created successfully!"
echo "========================================="
echo "Location: $(pwd)/dist/"
echo "Files created: $(find dist -type f | wc -l)"
echo "Total size: $(du -sh dist | cut -f1)"
echo ""
echo "Package contents:"
echo "- server-sentinel.exe (Main application)"
echo "- Server-Sentinel-C.bat (Primary launcher)"
echo "- run-direct.bat (Alternative launcher)"
echo "- All required DLL dependencies"
echo "- GTK data files and schemas"
echo "- Complete documentation"
echo ""
echo "Ready for distribution!"
echo "To share: Create a ZIP file of the 'dist' folder"
echo ""
echo "Test the package by running: cd dist && ./Server-Sentinel-C.bat"