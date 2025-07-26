# Group Task Breakdown - Server-Sentinel-C Project

## Team Information
- **Course**: CO253 - Introduction to Programming and Networking for Electrical Engineering
- **Project**: Server-Sentinel-C Server Monitoring System
- **Team**: Group 20
- **Submission Date**: July 26, 2025

---

## Team Members & Contributions

### 👨‍💻 **Samarakoon S.M.O.T. (Oshadha)** - E/21/345
**Role**: Project Lead & Core Developer  
**Primary Responsibilities**: System architecture, integration, and Github coordination

#### Specific Contributions:
- **System Architecture Design**: Designed the overall modular structure using MVC pattern
- **Main Controller Implementation**: Developed `main_controller.c` - the brain of the system
- **Integration Management**: Connected all modules together and ensured they work as a team
- **Project Coordination**: Managed timelines, task assignments, and team communications
- **GUI Integration**: Helped integrate GTK4 interface with core business logic
- **Distribution Packaging**: Created Windows distribution system with all dependencies
- **Documentation Leadership**: Supervised all technical documentation and user guides
- **Bug Fixing & Testing**: Resolved critical issues like heating button and fix button problems

**Files Primarily Worked On**:
- `src/main_controller.c` (Core system logic - 200+ lines)
- `src/main.c` (Application entry point)
- `include/main_controller.h` (Controller interfaces)
- `Makefile` (Build system configuration)
- `create-distribution.sh` (Distribution packaging script)

**Estimated Work Hours**: ~12 hours

---

### 🖥️ **Rathnasiri R.S. (Rumal)** - E/21/326
**Role**: Developer  
**Primary Responsibilities**: User interface and testing

#### Specific Contributions:
- **GUI Development**: Implemented the beautiful GTK4 graphical interface
- **User Experience Design**: Created intuitive button layouts and visual feedback
- **CSS Styling**: Designed modern interface with ChatGPT-inspired styling and rounded corners
- **Real-time Display**: Implemented live updating of temperature, humidity, and status
- **Testing Coordination**: Developed comprehensive test cases and validation procedures
- **Interface Testing**: Verified all buttons, displays, and user interactions work correctly
- **User Interface Documentation**: Created user guides and interface screenshots

**Files Primarily Worked On**:
- `src/gui_interface.c` (Complete GUI implementation - 900+ lines with the aid of gtk gtk4.demo+gtk user manul and used chatGPT for CSS styling)
- `include/gui_interface.h` (GUI interface definitions)
- `test/test_gui_components.c` (Interface testing)
- CSS styling within GUI code

**Estimated Work Hours**: ~10 hours

---

### 📝 **Rathnayaka P.G.I.N.B. (Induka)** - E/21/327
**Role**: Developer  
**Primary Responsibilities**: Logger module, data structures and video demo creation

#### Specific Contributions:
- **Logging System**: Implemented circular buffer logging with 120-entry capacity
- **Data Structure Design**: Created efficient data structures for sensor readings and logs
- **Memory Management**: Optimized memory usage with circular buffer implementation
- **File I/O Operations**: Developed log export functionality with timestamp naming
- **Data Persistence**: Ensured reliable data storage and retrieval
- **Performance Optimization**: Made sure logging doesn't slow down the system

**Files Primarily Worked On**:
- `src/logger.c` (Complete logging system - 100+ lines)
- `include/logger.h` (Logging interfaces and data structures)
- `include/common.h` (Shared data structure definitions)
- Log export functionality

**Estimated Work Hours**: ~8 hours

---

### 🤓 **Ratnayake R.M.K.T. (Kaweesha)** - E/21/334
**Role**: Developer  
**Primary Responsibilities**: Project documentation, reporting & Smart data simulation module

#### Specific Contributions:
- **Smart Data Engine**: Implemented the environmental simulation system in `smart_data.c`
- **Scenario Development**: Created all simulation scenarios (heating, cooling, humidity spikes, etc.)
- **Documentation Management**: Led creation of comprehensive project documentation
- **Technical Writing**: Authored technical specifications and user manuals
- **Project Reporting**: Created final project reports and presentation materials
- **Data Generation Logic**: Developed realistic environmental data simulation algorithms
- **State Machine Implementation**: Designed the environmental state transition system

**Files Primarily Worked On**:
- `src/smart_data.c` (Environmental simulation engine - 400+ lines)
- `include/smart_data.h` (Simulation interfaces and state definitions)
- `docs/FINAL_PROJECT_REPORT.md` (Comprehensive technical documentation)
- `docs/COMPLETE_USER_GUIDE.md` (Detailed user manual)
- Various documentation files in `docs/` folder

**Estimated Work Hours**: ~10 hours

---

### 🧠 **Samaranayaka W.W.M.A. (Asanga)** - E/21/346
**Role**: Developer  
**Primary Responsibilities**: System logic implementation

#### Specific Contributions:
- **Safety Systems**: Implemented critical timer and emergency shutdown functionality
- **State Management**: Developed system state logic (Normal/Caution/Danger/Shutdown)
- **Environmental Analysis**: Created threshold checking and alert generation
- **Critical Timer**: Implemented 20-second countdown and automatic shutdown protection
- **Safety Logic**: Ensured system responds appropriately to dangerous conditions
- **State Transitions**: Managed smooth transitions between different system states

**Files Primarily Worked On**:
- `src/system_logic.c` (Safety and state management - 150+ lines)
- `include/system_logic.h` (Safety system interfaces)
- Critical timer implementation
- Emergency shutdown procedures

**Estimated Work Hours**: ~8 hours

---

## Collaborative Work

### Joint Responsibilities

**All Team Members Contributed To**:
- **Project Planning**: Initial requirements analysis and feature specification
- **Code Review**: Peer review of each other's code for quality assurance
- **Testing**: Validation of individual modules and integrated system
- **Bug Fixing**: Collaborative debugging and problem resolution
- **Documentation Review**: Ensuring all documentation is accurate and complete

### Integration Efforts

**Cross-Module Collaboration**:
- **Oshadha & Rumal**: Integrated GUI interface with main controller logic
- **Oshadha & Kaweesha**: Connected simulation engine with controller system
- **Induka & Rumal**: Integrated logging system with GUI display
- **Asanga & Kaweesha**: Connected safety logic with simulation states
- **All Members**: Collaborative testing and validation of complete system

