# 🧪 Test Plan

---

## 📝 Overview
This document outlines the testing approach for **Server-Sentinel-C**, ensuring that the system behaves correctly under all simulated conditions.

---

## 🔬 Test Scenarios

### 🔥 Scenario 1: Full Meltdown
- **Description**: Simulates a complete cooling system failure leading to system shutdown.
- **Steps**:
    1. 🏃 Run the program
    2. ⌨️ Enter command: `fail_cooling`
    3. ⏳ Do not intervene
- **Expected Results**:
    - 🟡 System transitions from `NORMAL` to `CAUTION` state when temperature exceeds 45°C.
    - 🟠 System transitions to `DANGER` state when temperature exceeds 60°C.
    - 🔴 System displays `SHUTDOWN` message after 20 seconds at critical temperature.
    - 🛑 Program terminates.

### ✅ Scenario 2: Successful Intervention
- **Description**: Tests recovery from critical conditions.
- **Steps**:
    1. 🏃 Run the program
    2. ⌨️ Enter command: `fail_cooling`
    3. ⏱️ Wait for `DANGER` alert
    4. ⌨️ Enter command: `fix`
- **Expected Results**:
    - 📈 System transitions from `NORMAL` to `CAUTION` to `DANGER`.
    - 📉 After `fix` command, temperature decreases.
    - 🟢 System transitions back to `CAUTION` and then `NORMAL`.
    - 🚫 Shutdown timer is canceled.

### 💧 Scenario 3: Humidity Alert Only
- **Description**: Tests humidity-specific alerts.
- **Steps**:
    1. 🏃 Run the program
    2. ⌨️ Enter command: `humidity_spike`
- **Expected Results**:
    - 🟡 System issues `CAUTION` alerts when humidity exceeds 70%.
    - 🟠 System issues `DANGER` alerts when humidity exceeds 80%.
    - 🌡️ System does not shut down (shutdown is tied only to temperature).

### ⚡ Scenario 4: Intermittent Failure
- **Description**: Tests system response to fluctuating conditions.
- **Steps**:
    1. 🏃 Run the program
    2. ⌨️ Enter command: `intermittent`
- **Expected Results**:
    - ↔️ System alternates between states as conditions fluctuate.
    - 🛡️ System does not trigger false shutdowns.
    - 🔔 Alerts correspond to current conditions.

---

## 📊 Test Execution
Each test scenario will be executed and documented with:
- 📸 Screenshots of console output
- 🕰️ Timestamps of state transitions
- 📋 Log data analysis

---

## ✔️ Acceptance Criteria
- All test scenarios pass without unexpected behavior.
- System correctly transitions between states based on thresholds.
- Logging system captures all events correctly.
- Alert system provides appropriate notifications.
- Shutdown protocol triggers only when conditions warrant.