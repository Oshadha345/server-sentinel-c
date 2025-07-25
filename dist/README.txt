Server-Sentinel-C Environmental Monitor v1.0
==============================================

DESCRIPTION:
A modern environmental monitoring system designed for data centers and server rooms.
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
✓ Real-time environmental monitoring
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
