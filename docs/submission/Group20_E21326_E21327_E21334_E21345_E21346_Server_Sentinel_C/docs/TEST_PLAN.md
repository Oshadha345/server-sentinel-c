# Test Plan - Server-Sentinel-C

## Project Information
- **Project Name**: Server-Sentinel-C Server Monitoring System
- **Version**: 1.0.0
- **Team**: Group 20
- **Course**: CO253 - Introduction to Programming and Networking for Electrical Engineering
- **Date**: July 2025

## Testing Overview

This test plan outlines all the inputs we tested and what we expected to happen. Our server monitoring system has many different scenarios and we had to make sure each one works properly.

---

## Test Categories

### 1. Basic System Functionality Tests

#### Test 1.1: System Initialization
**Purpose**: Make sure the program starts up correctly

**Input**: 
- Start the application by double-clicking `Server-Sentinel-C.bat`

**Expected Output**:
- Application window opens successfully
- Initial temperature reading around 22-25°C
- Initial humidity reading around 45-55%
- System state shows "NORMAL"
- All buttons are visible and clickable

**Actual Result**: ✅ PASS - System starts with default values in normal range

---

#### Test 1.2: Start Simulation
**Purpose**: Verify that simulation can be started and stopped

**Input**: 
- Click "▶ Start Simulation" button

**Expected Output**:
- Button text changes to "⏸ Stop Simulation"
- Temperature and humidity readings begin updating every second
- Log entries start appearing in the display

**Actual Result**: ✅ PASS - Simulation starts correctly with real-time updates

---

### 2. Temperature Monitoring Tests

#### Test 2.1: Normal Temperature Range
**Purpose**: Test system behavior within normal temperature limits

**Input**: 
- Start simulation
- Click "🔄 Stable" button
- Observe for 30 seconds

**Expected Output**:
- Temperature stays between 20-25°C
- System state remains "NORMAL"
- Status indicator stays green
- No warning messages appear

**Actual Result**: ✅ PASS - Temperature fluctuates normally around 22.5°C

---

#### Test 2.2: Heating Scenario
**Purpose**: Test temperature increase simulation

**Input**: 
- Start simulation
- Click "🔥 Heating Up" button
- Observe temperature changes

**Expected Output**:
- Temperature begins increasing gradually
- At 45°C: System state changes to "CAUTION" (yellow)
- At 60°C: System state changes to "DANGER" (red)
- Temperature continues rising to 90-110°C range
- System does NOT automatically cool down

**Actual Result**: ✅ PASS - Temperature increases properly, state changes at correct thresholds

---

#### Test 2.3: Cooling Functionality
**Purpose**: Test the fix button cooling feature

**Input**: 
- First heat system using "🔥 Heating Up"
- Wait until temperature exceeds 60°C (DANGER state)
- Click "🔧 Fix" button

**Expected Output**:
- System state changes to "COOLING_DOWN"
- Temperature decreases at approximately 2°C per second
- When temperature reaches 22-25°C range, system auto-stabilizes
- System state returns to "NORMAL"

**Actual Result**: ✅ PASS - Fix button successfully cools overheated system

---

### 3. Humidity Monitoring Tests

#### Test 3.1: Normal Humidity Range
**Purpose**: Test humidity monitoring within normal limits

**Input**: 
- Start simulation with "🔄 Stable"
- Monitor humidity readings

**Expected Output**:
- Humidity stays between 45-55%
- No humidity-related state changes
- Green status indicators

**Actual Result**: ✅ PASS - Humidity remains stable in normal range

---

#### Test 3.2: Humidity Spike Scenario
**Purpose**: Test humidity control failure simulation

**Input**: 
- Start simulation
- Click "💧 Humidity Spike" button

**Expected Output**:
- Humidity jumps outside normal range (either very high or very low)
- If humidity goes below 30% or above 70%: System enters "CAUTION"
- If humidity goes below 20% or above 80%: System enters "DANGER"

**Actual Result**: ✅ PASS - Humidity spikes correctly trigger appropriate state changes

---

### 4. Safety System Tests

#### Test 4.1: Critical Timer Functionality
**Purpose**: Test automatic shutdown protection

**Input**: 
- Heat system to DANGER state (>60°C)
- Wait for 20 seconds without fixing

**Expected Output**:
- Critical timer countdown appears
- After 20 seconds: System automatically enters "SHUTDOWN" state
- All operations cease
- Emergency shutdown message displayed

**Actual Result**: ✅ PASS - Timer counts down correctly and triggers shutdown

---

#### Test 4.2: Emergency Recovery
**Purpose**: Test system recovery from shutdown state

**Input**: 
- After system shutdown, click Exit to reboot again, which shows real world system start-up

**Expected Output**:
- System resets to initial normal state
- Temperature and humidity return to safe ranges
- All controls become functional again

**Actual Result**: ✅ PASS - System recovers successfully from shutdown

---

### 5. User Interface Tests

#### Test 5.1: Button Responsiveness
**Purpose**: Verify all buttons work correctly

**Input**: 
- Click each button in the interface:
  - Start/Stop Simulation
  - Stable
  - Heating Up
  - Humidity Spike
  - Intermittent Failure
  - Fail Cooling
  - Fix
  - Export Log

**Expected Output**:
- Each button responds immediately when clicked
- Visual feedback provided (button press animation)
- Corresponding system state changes occur

**Actual Result**: ✅ PASS - All buttons responsive with immediate feedback

---

#### Test 5.2: Real-time Display Updates
**Purpose**: Test live data display functionality

**Input**: 
- Start simulation and observe displays

**Expected Output**:
- Temperature display updates every second
- Humidity display updates every second
- System state indicator changes color appropriately
- Log entries appear in real-time (newest first)

**Actual Result**: ✅ PASS - All displays update correctly in real-time

---

### 6. Data Management Tests

#### Test 6.1: Log Display Functionality
**Purpose**: Test live log viewing

**Input**: 
- Start simulation
- Let it run for several minutes
- Observe log display

**Expected Output**:
- Latest 20 log entries visible
- Newest entries appear at top
- Each entry shows: timestamp, temperature, humidity, status
- Log scrolls automatically as new entries appear

**Actual Result**: ✅ PASS - Log display works correctly with proper formatting

---

#### Test 6.2: Log Export Feature
**Purpose**: Test log file export functionality

**Input**: 
- Run simulation for several minutes
- Click "📥 Export Log" button

**Expected Output**:
- File save dialog appears (or file saved automatically)
- Filename includes timestamp (e.g., "log_20250726_140530_to_140630.txt")
- File contains all 120 log entries from circular buffer
- File format is readable text

**Actual Result**: ✅ PASS - Log export creates properly formatted file with timestamp

---

### 7. Scenario Integration Tests

#### Test 7.1: Complete Heating/Cooling Cycle
**Purpose**: Test full heating and recovery cycle

**Input**: 
1. Start simulation
2. Click "🔥 Heating Up"
3. Wait for DANGER state
4. Click "🔧 Fix"
5. Wait for system to stabilize

**Expected Output**:
1. Normal operation (22°C, NORMAL state)
2. Temperature rises, state progresses: NORMAL → CAUTION → DANGER
3. Fix initiated, cooling begins
4. Temperature decreases, state returns: DANGER → CAUTION → NORMAL
5. System stabilizes at normal temperature

**Actual Result**: ✅ PASS - Complete cycle works correctly with proper state transitions

---

#### Test 7.2: Intermittent Failure Handling
**Purpose**: Test random failure scenario

**Input**: 
- Start simulation
- Click "⚡ Intermittent Failure"
- Monitor system for several minutes
- Click "🔧 Fix" when problems occur

**Expected Output**:
- System exhibits random environmental issues
- Temperature and humidity fluctuate unpredictably
- Fix button resolves current issues
- System may develop new issues after fixing

**Actual Result**: ✅ PASS - Intermittent failures occur randomly and fix button resolves them

---

### 8. Error Handling Tests

#### Test 8.1: Invalid State Transitions
**Purpose**: Test system behavior with rapid button clicks

**Input**: 
- Click multiple scenario buttons rapidly in sequence
- Try clicking buttons while system is in transition

**Expected Output**:
- System handles rapid inputs gracefully
- No crashes or undefined behavior
- Current operation completes before starting new one

**Actual Result**: ✅ PASS - System handles rapid inputs without issues

---

#### Test 8.2: Resource Cleanup
**Purpose**: Test proper cleanup when application closes

**Input**: 
- Start simulation
- Close application window using 'X' button

**Expected Output**:
- Application closes cleanly
- No error messages or crashes
- No lingering processes in Task Manager

**Actual Result**: ✅ PASS - Application closes properly with clean resource cleanup

---

## Performance Tests

#### Test 9.1: Memory Usage
**Purpose**: Monitor memory consumption during operation

**Input**: 
- Run application for extended period (30+ minutes)
- Monitor Task Manager for memory usage

**Expected Output**:
- Memory usage remains stable (< 64 MB)
- No memory leaks detected
- Performance remains responsive

**Actual Result**: ✅ PASS - Memory usage stable around 45 MB with no leaks

---

#### Test 9.2: CPU Usage
**Purpose**: Monitor processor utilization

**Input**: 
- Run simulation continuously
- Monitor CPU usage in Task Manager

**Expected Output**:
- CPU usage remains low (< 2%)
- No excessive processor consumption
- System remains responsive to other applications

**Actual Result**: ✅ PASS - CPU usage averages 1.2% during normal operation

---

## Test Results Summary

### Overall Results
- **Total Tests Conducted**: 18 tests
- **Tests Passed**: 18 ✅
- **Tests Failed**: 0 ❌
- **Success Rate**: 100%

### Critical Issues Found
- **Major Bugs**: 0
- **Minor Issues**: 0
- **Performance Problems**: 0

### Key Achievements
1. ✅ All core functionality works as designed
2. ✅ Safety systems function properly
3. ✅ User interface is responsive and intuitive
4. ✅ Data management operates correctly
5. ✅ Resource usage is optimized
6. ✅ Error handling is robust

## Test Environment

**Hardware**:
- Intel Core i5 processor
- 8 GB RAM
- Windows 11 64-bit

**Software**:
- MINGW64 build environment
- GTK4 libraries
- All required DLL dependencies included

**Testing Period**: July 20-26, 2025

---

## Conclusion

Server-Sentinel-C has successfully passed all planned tests. The system demonstrates:

- **Reliable Core Functionality**: All monitoring and simulation features work correctly
- **Robust Safety Systems**: Critical timer and emergency shutdown operate as designed
- **Professional User Experience**: Interface is responsive and user-friendly
- **Efficient Performance**: Low resource usage with stable operation
- **Comprehensive Error Handling**: System gracefully handles edge cases

The application is ready for production deployment and meets all specified requirements.

---

**Test Plan Document**  
**Prepared by**: Group 20 Testing Team (Rumal Rathnasiri)  
**Date**: July 26, 2025  
**Status**: ✅ ALL TESTS PASSED
