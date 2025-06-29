# Server-Sentinel-C 🖥️🌡️

<p align="center">
    <img src="media/gifs/Virtual Reality Art GIF by Gogolitus.gif" alt="Server Sentinel C Banner" width="200">
</p>

[![Status](https://img.shields.io/badge/Status-In%20Development-yellow)](https://github.com/Oshadha345/server-sentinel-c)
[![Phase](https://img.shields.io/badge/Phase-1%3A%20Architecture-blue)](https://github.com/Oshadha345/server-sentinel-c)
[![License](https://img.shields.io/badge/License-MIT-green)](https://opensource.org/licenses/MIT)
[![C Language](https://img.shields.io/badge/Language-C-orange)](https://en.cppreference.com/w/c)
[![CO253](https://img.shields.io/badge/Course-CO253-red)](https://github.com/Oshadha345/server-sentinel-c)
![GitHub repo size](https://img.shields.io/github/repo-size/Oshadha345/server-sentinel-c?color=blue&label=Repo%20Size)
![GitHub last commit](https://img.shields.io/github/last-commit/Oshadha345/server-sentinel-c?color=purple)
![GitHub stars](https://img.shields.io/github/stars/Oshadha345/server-sentinel-c?style=social)
![GitHub forks](https://img.shields.io/github/forks/Oshadha345/server-sentinel-c?style=social)

> A C-based simulation of a mission-critical environmental controller for data centers, featuring a state-driven design, escalating alerts, and an emergency shutdown protocol based on ASHRAE standards.

---

## 📋 Contents 📚

- [Project Brief](#-project-brief) 📝
- [Features](#-features) ✨
- [Repository Structure](#-repository-structure) 🗂️
- [Team](#-team) 👥
- [Project Plan](#-project-plan) 🗓️
- [Getting Started](#-getting-started) 🚀

---

## 📑 Project Brief

### CO253 - Introduction to Programming and Networking for Electrical Engineering

🌟 **Project Objective**  
Students will develop software-only simulations of embedded systems using the C programming language. This is a foundational exercise intended to simulate real-world behavior of embedded devices while focusing on clean coding practices and logical system design. Graphical features are optional and may be developed using SDL or any cross-platform GUI library.

📅 **Project Allocation**  
Our group has been assigned with following project along with custom parameters.

**Project Description**  
Temperature Logger – Monitors and logs temperature values and provides alerts.

**Group 20:**
- Project: Temp/Humidity Logger
- Alert Threshold: 60
- Log Size: 120

---

## ✨ Features

Our implementation expands on the basic requirements with a comprehensive approach:

- **Advanced State Management:** Four operational states(NORMAL,CAUTION,DANGER,SHUTDOWN)🟢🟡🔴💀
- **Dual-Parameter Monitoring:** Tracks both temperature and humidity with distinct thresholds 🌡️💧
- **Circular Buffer Logging:** Maintains a 120-entry historical log with automatic oldest-entry replacement 🔄📝
- **Escalating Alert System:** Progressive alerts based on environmental conditions 🚨📈
- **Simulated Scenarios:** Multiple environmental test scenarios including cooling failures and humidity spikes 🧪
- **Time-Based Shutdown Protocol:** Automatic system shutdown after sustained critical conditions ⏲️🛑

### Key Parameters

| Parameter | Condition | Description |
|---|---|---|
| **Caution Temperature** | `> 45°C` | System enters `CAUTION` state ⚠️ |
| **Critical Temperature** | `> 60°C` | System enters `DANGER` state 🔥 |
| **Caution Humidity** | `> 70%` or `< 30%` | System enters `CAUTION` state 💧⚠️ |
| **Critical Humidity** | `> 80%` or `< 20%` | System enters `DANGER` state 💧🔥 |
| **Shutdown Timer** | `20 simulated seconds` | Time at Critical Temperature before `SHUTDOWN` ⏳ |

---
 
## 📂 Repository Structure

| Directory | Purpose | Contents |
|-----------|---------|----------|
| [`/docs`](./docs) | Documentation 📖 | Architecture, flowcharts, and module specifications |
| [`/docs/modules`](./docs/modules) | Module Documentation 🧩 | Detailed documentation for each system module |
| [`/include`](./include) | Header Files 📑 | Function prototypes and data structure definitions |
| [`/src`](./src) | Source Code 💻 | Implementation files for all modules |
| [`/bin`](./bin) | Compiled Binaries 🏗️ | Executable files and compiled objects |

---

## 📅 Project Plan

### *Phase 1: Architecture & Design (The Blueprint Phase)* 🚧

- [x] Define system requirements ✅
- [x] Establish repository structure 🗂️
- [x] Complete system architecture documentation 🏛️
- [x] Design system flowcharts 🗺️
- [x] Define module interfaces 🔌
- [ ] Finalize data structures 🏗️

### *Phase 2: Core Logic Development (The Coding Phase)* 📝

- [ ] Implement smart_data.c module 🤓
- [ ] Implement logger.c module 📝
- [ ] Implement system_logic.c module 🧠
- [ ] Implement user_interface.c module 🖥️
- [ ] Implement main.c controller 🎮
- [ ] Create Makefile 🛠️

### *Phase 3: Testing & Refinement (The Validation Phase)* 🧪

- [ ] Develop test plan 🧾
- [ ] Execute scenario testing 🧬
- [ ] Code review and refactor 🔍
- [ ] Performance optimization 🚀

### *Phase 4: GUI Integration (Optional Phase)* 🖼️

- [ ] Select GUI library 🖌️
- [ ] Design UI components 🧩
- [ ] Integrate with core logic 🔗
- [ ] GUI testing 🧪

### *Phase 5: Final Testing & Deployment (The Launch Phase)* 🚀

- [ ] Final system testing 🧪
- [ ] Compile for different platforms 🖥️
- [ ] Create deployment package 📦
- [ ] Project presentation and documentation 🎤

---

## 📊 Project Stats

![Commits](https://img.shields.io/badge/Commits-27-blue)
![Completion](https://img.shields.io/badge/Completion-8%25-yellow)
![Issues](https://img.shields.io/badge/Open%20Issues-4-red)
![PRs](https://img.shields.io/badge/Pull%20Requests-2-green)
![Contributors](https://img.shields.io/badge/Contributors-6-orange)
![GitHub watchers](https://img.shields.io/github/watchers/Oshadha345/server-sentinel-c?style=social)
![GitHub issues](https://img.shields.io/github/issues/Oshadha345/server-sentinel-c?color=red)
![GitHub pull requests](https://img.shields.io/github/issues-pr/Oshadha345/server-sentinel-c?color=green)


### 📈 Detailed Stats

| Lines of Code | ~2,500 (projected) | - |
| Documentation Pages | 7 | - |
    
| Metric | Value | Progress |
|--------|-------|----------|
| Phase 1 Tasks | 5/6 completed (83%) | ███████████░░ 83% |
| Phase 2 Tasks | 0/6 completed (0%) | ░░░░░░░░░░░░░░ 0% |
| Phase 3 Tasks | 0/4 completed (0%) | ░░░░░░░░░░░░░░ 0% |   
| Phase 4 Tasks | 0/4 completed (0%) | ░░░░░░░░░░░░░░ 0% |
| Phase 5 Tasks | 0/4 completed (0%) | ░░░░░░░░░░░░░░ 0% |
| Total Tasks | 5/24 completed | ███░░░░░░░░░░░░ 21% |

---

## 🚀 Getting Started

> ⚠️ **Note:** This project is currently in Phase 1 (Architecture & Design). Build instructions will be added in Phase 2.

### Prerequisites (Planned) 🧰

- GCC compiler (version 9.0+) 🛠️
- Make build system 🏗️
- SDL2 library (for optional GUI components) 🖼️

### Building (Coming in Phase 2) 🏗️

```bash
# Clone the repository
git clone https://github.com/Oshadha345/server-sentinel-c.git

# Navigate to project directory
cd server-sentinel-c

# Compile the project
make

#Running (Coming in Phase 2)
# Run the program
./bin/server-sentinel
```
---

## 📊 System State Diagram

```mermaid
stateDiagram-v2
    [*] --> NORMAL
    NORMAL --> CAUTION: Temp > 45°C<br>OR Humidity < 30%<br>OR Humidity > 70%
    CAUTION --> DANGER: Temp > 60°C<br>OR Humidity < 20%<br>OR Humidity > 80%
    DANGER --> CAUTION: Temp ≤ 60°C<br>AND 20% ≤ Humidity ≤ 80%
    CAUTION --> NORMAL: Temp ≤ 45°C<br>AND 30% ≤ Humidity ≤ 70%
    DANGER --> SHUTDOWN: Critical Temp<br>for > 20 seconds
    SHUTDOWN --> [*]
```
<p align="center">
    <img src="https://img.shields.io/badge/Diagram-Mermaid-blue?logo=mermaid" alt="Mermaid Diagram Badge">
</p>

---

## 🛠️ Tech Stack

### Languages & Tools
![C](https://img.shields.io/badge/-C-000000?style=flat&logo=c)
![Git](https://img.shields.io/badge/-Git-222222?style=flat&logo=git&logoColor=F05032)
![GitHub](https://img.shields.io/badge/-GitHub-222222?style=flat&logo=github&logoColor=181717)
![VS Code](https://img.shields.io/badge/-VS%20Code-007ACC?style=flat&logo=visual-studio-code)
![Make](https://img.shields.io/badge/-Make-427819?style=flat&logo=gnu)
![GitHub Actions](https://img.shields.io/badge/-GitHub%20Actions-2088FF?logo=github-actions&logoColor=white)

### Libraries
![Standard Library](https://img.shields.io/badge/Standard%20Library-libc-blue)
![SDL2](https://img.shields.io/badge/GUI%20(Optional)-SDL2-brightgreen)
![Unit Testing](https://img.shields.io/badge/Testing-CUnit-orange)

### Development Standards
![ANSI C](https://img.shields.io/badge/Standard-ANSI%20C-yellow)
![ASHRAE](https://img.shields.io/badge/Compliance-ASHRAE-lightgrey)
![Prettier](https://img.shields.io/badge/Code%20Style-Prettier-ff69b4?logo=prettier)
![EditorConfig](https://img.shields.io/badge/EditorConfig-enabled-blueviolet?logo=editorconfig)

---

## 👥 Team

**Group 20**  members with their  responsibilities:

| Name | Index | Role | Responsibilities |
|------|-------|------|------------------|
| Prasad V.G.A. (Asitha) | E/21/313 | Developer | Smart data simulation module 🤓 |
| Rathnasiri R.S. (Rumal) | E/21/326 | Developer | User interface and testing 🖥️🧪 |
| Rathnayaka P.G.I.N.B. (Induka) | E/21/327 | Developer | Logger module and data structures 📝 |
| Ratnayake R.M.K.T. (Kaweesha) | E/21/334 | Developer | Project documentation and reporting 📚 |
| Samarakoon S.M.O.T. (Oshadha) | E/21/345 | Developer | System architecture, integration, and coordination 🏗️ |
| Samaranayaka W.W.M.A. (Asanga) | E/21/346 | Developer | System logic implementation 🧠 |

---

<p align="center"> <b>CO253 - Introduction to Programming and Networking for Electrical Engineering</b><br> University of Peradeniya | Department of Electrical & Electronic Engineering | 2025 <br> <img src="https://img.shields.io/badge/Made%20with-GitHub-181717?logo=github"> <img src="https://img.shields.io/badge/Powered%20by-Nerd%20Energy-9cf?logo=github"></p>
