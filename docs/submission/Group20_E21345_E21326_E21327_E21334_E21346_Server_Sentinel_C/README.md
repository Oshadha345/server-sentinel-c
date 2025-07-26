# Server-Sentinel-C - Final Project Submission

## Project Description

**Server-Sentinel-C** is a professional server monitoring system designed for data centers and server rooms. This C-based application provides real-time temperature and humidity monitoring with advanced simulation capabilities, intelligent safety systems, and a modern graphical user interface.

### What Does It Do?

Our Server-Sentinel-C system monitors server room conditions just like a security guard watches over a building! It:

- **Monitors Temperature & Humidity**: Keeps track of how hot and humid your server room is
- **Provides Alerts**: Warns you when things get too hot or too cold
- **Simulates Different Scenarios**: You can test what happens when cooling systems fail
- **Automatic Safety**: Shuts down systems before they get damaged
- **Professional GUI**: Easy-to-use windows and buttons interface

### Key Features

#### 🌡️ **Environmental Monitoring**
- Real-time temperature tracking (20-25°C normal range)
- Humidity monitoring (45-55% normal range)
- Multi-state system: Normal → Caution → Danger → Emergency Shutdown
- ASHRAE compliant thresholds for data center environments

#### 🎮 **Simulation Controls**
- **Stable Operation**: Normal server room conditions
- **Heating Up**: Simulates air conditioning failure
- **Cooling Down**: Tests cooling system recovery
- **Humidity Spike**: Simulates humidity control problems
- **Intermittent Failure**: Random environmental issues

#### 🛡️ **Safety Systems**
- Critical timer system (20-second countdown)
- Automatic emergency shutdown protection
- Smart fix button that analyzes conditions
- Color-coded visual alerts (Green/Yellow/Red)

#### 💻 **User Interface**
- Modern GTK4 graphical interface
- Real-time status displays
- Interactive control buttons
- Live log display (newest entries first)
- Professional CSS styling with rounded corners

#### 📊 **Data Management**
- Circular logging buffer (120 total entries)
- Real-time log display (shows latest 20 entries)
- Log export functionality with timestamps
- Automatic file naming with start/end times

## Usage Instructions

### Installation & Setup

1. **Download the Package**
   - Get `Server-Sentinel-C_v1.0_Windows_Distribution.tar.gz` (16 MB)
   - This contains everything you need - no additional software required!

2. **Extract the Files**
   ```
   # Extract to any folder on your computer
   # You can use WinRAR, 7zip, or Windows built-in extractor
   ```

3. **Launch the Application**
   - Navigate to the extracted folder
   - Double-click `Server-Sentinel-C.bat`
   - The application window will open automatically

### Using the Interface

#### Getting Started
1. **Start Monitoring**: Click the "▶ Start Simulation" button
2. **Watch the Display**: See temperature and humidity readings update every second
3. **Check Status**: Monitor the system state (Normal/Caution/Danger)

#### Testing Different Scenarios

**Normal Operation:**
- Click "🔄 Stable" to maintain normal conditions
- Temperature stays around 22-25°C
- Humidity stays around 45-55%

**Heating Test:**
- Click "🔥 Heating Up" to simulate cooling failure
- Watch temperature rise gradually to 90-110°C
- System enters Caution (45°C+) then Danger (60°C+)

**Cooling Recovery:**
- During heating, click "🔧 Fix" to start cooling
- Temperature decreases at 2°C per second
- System automatically stabilizes at normal range

**Humidity Problems:**
- Click "💧 Humidity Spike" to test humidity control
- Humidity jumps outside normal range
- System alerts when humidity is too high/low

**Intermittent Issues:**
- Click "⚡ Intermittent Failure" for random problems
- System cycles between different issues
- Use "🔧 Fix" to resolve problems

#### Reading the Display

**Temperature Display:**
- Green: Normal (20-45°C)
- Yellow: Caution (45-60°C)  
- Red: Danger (60°C+)

**Humidity Display:**
- Green: Normal (30-70%)
- Yellow: Caution (20-30% or 70-80%)
- Red: Danger (below 20% or above 80%)

**System State:**
- **NORMAL**: Everything is working fine
- **CAUTION**: Some readings outside normal range
- **DANGER**: Critical conditions detected
- **SHUTDOWN**: Emergency shutdown activated

#### Log Management

**Viewing Logs:**
- Live log display shows latest 20 entries
- Each entry shows timestamp, temperature, humidity, and status
- Newest entries appear at the top

**Exporting Logs:**
- Click "📥 Export Log" to save current data
- Files saved with timestamp names like "log_20250726_140530_to_140630.txt"
- Contains all 120 entries from circular buffer

### Troubleshooting

**Application Won't Start:**
- Make sure you extracted all files from the .tar.gz package
- Try running `run-direct.bat` to see error messages
- Check that you're on Windows 7 or later

**No Temperature Changes:**
- Click "▶ Start Simulation" to begin monitoring
- Make sure you've selected a scenario (Stable, Heating, etc.)

**Fix Button Not Working:**
- Only works during Heating Up or Intermittent Failure states
- Make sure system is actually in a problem state first

**Interface Looks Strange:**
- Close and restart the application
- Make sure all DLL files are in the same folder

### System Requirements

- **Operating System**: Windows 7, 8, 10, or 11
- **Memory**: Minimum 64 MB available RAM
- **Storage**: 50 MB free disk space
- **Additional Software**: None required (completely portable)

### File Structure

```
Server-Sentinel-C_Distribution/
├── server-sentinel.exe          # Main application
├── Server-Sentinel-C.bat        # Primary launcher (recommended)
├── run-direct.bat              # Alternative launcher with console
├── [46 DLL files]              # All required dependencies
├── share/                      # GTK4 data files and icons
├── README.txt                  # Quick start guide
├── INSTALL.txt                 # Installation instructions
└── VERSION.txt                 # Version information
```

### Advanced Usage

**Command Line Options:**
```bash
# Show help information
server-sentinel.exe --help

# Show version information  
server-sentinel.exe --version
```

**Log File Format:**
```
Timestamp: 2025-07-26 14:05:30
Temperature: 23.4°C, Humidity: 48.2%, State: NORMAL
```

### Support

For technical questions or issues:
1. Check the troubleshooting section above
2. Review the complete user guide: `docs/COMPLETE_USER_GUIDE.md`
3. See technical documentation: `docs/FINAL_PROJECT_REPORT.md`

---

**Server-Sentinel-C v1.0.0** - Professional Server Monitoring System  
**Developed by**: Group 20, University of Moratuwa  
**Course**: CO253 - Software Construction Project  
**Date**: July 2025
