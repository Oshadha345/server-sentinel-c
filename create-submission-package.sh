#!/bin/bash

# Final Submission Package Creator for Server-Sentinel-C
# Group 20 - CO253 Project

echo "Creating Final Submission Package..."
echo "===================================="

# Define submission information
GROUP_ID="Group20"
MEMBERS="E21345_E21326_E21327_E21334_E21346"
PACKAGE_NAME="${GROUP_ID}_${MEMBERS}_Server_Sentinel_C.zip"

echo "Package name: ${PACKAGE_NAME}"
echo ""

# Create temporary submission directory
TEMP_DIR="submission_temp"
mkdir -p "${TEMP_DIR}"

echo "Gathering required files..."

# 1. Copy all .c and .h source code files
echo "  ✓ Copying source code files (.c and .h)"
mkdir -p "${TEMP_DIR}/src"
mkdir -p "${TEMP_DIR}/include"
cp src/*.c "${TEMP_DIR}/src/"
cp include/*.h "${TEMP_DIR}/include/"

# 2. Copy README.md with project description and usage instructions
echo "  ✓ Copying README.md"
cp docs/submission/README.md "${TEMP_DIR}/"

# 3. Copy Test Plan detailing inputs and expected outputs
echo "  ✓ Copying Test Plan"
cp docs/submission/TEST_PLAN.md "${TEMP_DIR}/"

# 4. Copy Group task breakdown
echo "  ✓ Copying Group Task Breakdown"
cp docs/submission/GROUP_TASK_BREAKDOWN.md "${TEMP_DIR}/"

# 5. Copy test files to show testing approach
echo "  ✓ Copying test files"
mkdir -p "${TEMP_DIR}/test"
cp test/*.c "${TEMP_DIR}/test/"

# 6. Copy Makefile and build instructions
echo "  ✓ Copying build files"
cp Makefile "${TEMP_DIR}/"

# 7. Copy additional important documentation
echo "  ✓ Copying additional documentation"
mkdir -p "${TEMP_DIR}/docs"
cp docs/FINAL_PROJECT_REPORT.md "${TEMP_DIR}/docs/"
cp docs/COMPLETE_USER_GUIDE.md "${TEMP_DIR}/docs/"

# 8. Copy sample output logs (if any exist)
echo "  ✓ Copying sample outputs"
mkdir -p "${TEMP_DIR}/samples"
if [ -f "sample_output.txt" ]; then
    cp sample_output.txt "${TEMP_DIR}/samples/"
fi

# 9. Create a brief project structure document
echo "  ✓ Creating project structure document"
cat > "${TEMP_DIR}/PROJECT_STRUCTURE.txt" << 'EOF'
Server-Sentinel-C Final Submission Structure
===========================================

This submission package contains:

📁 src/                          - All C source code files
   ├── main.c                    - Application entry point
   ├── main_controller.c         - Core business logic
   ├── gui_interface.c           - GTK4 user interface
   ├── smart_data.c              - Environmental simulation
   ├── logger.c                  - Data logging system
   └── system_logic.c            - Safety and state logic

📁 include/                      - All header files
   ├── common.h                  - Shared definitions
   ├── main_controller.h         - Controller interfaces
   ├── gui_interface.h           - GUI declarations
   ├── smart_data.h              - Simulation interfaces
   ├── logger.h                  - Logging interfaces
   └── system_logic.h            - Logic interfaces

📁 test/                         - Test files demonstrating functionality
   ├── test_fix_button.c         - Fix button functionality tests
   ├── test_heating_button.c     - Heating scenario tests
   └── [other test files]        - Additional validation tests

📁 docs/                         - Additional documentation
   ├── FINAL_PROJECT_REPORT.md   - Comprehensive technical report
   └── COMPLETE_USER_GUIDE.md    - Detailed user manual

📄 README.md                     - Main project description and usage
📄 TEST_PLAN.md                  - Detailed testing documentation
📄 GROUP_TASK_BREAKDOWN.md       - Team member contributions
📄 Makefile                      - Build system configuration
📄 PROJECT_STRUCTURE.txt         - This file

Key Features Implemented:
✓ Real-time server monitoring system
✓ Modern GTK4 graphical interface
✓ Multiple simulation scenarios (heating, cooling, humidity)
✓ Intelligent safety systems with emergency shutdown
✓ Comprehensive data logging with export functionality
✓ Professional Windows distribution package

How to Build and Run:
1. Ensure GTK4 development libraries are installed
2. Run: make clean && make
3. Execute: ./bin/server-sentinel.exe

For detailed instructions, see README.md and COMPLETE_USER_GUIDE.md

Group 20 - CO253 Software Construction Project
University of Moratuwa - July 2025
EOF

# 10. Create the final ZIP package
echo ""
echo "Creating final ZIP package..."
cd "${TEMP_DIR}"
if command -v zip &> /dev/null; then
    zip -r "../${PACKAGE_NAME}" .
    echo "  ✓ Created ${PACKAGE_NAME} using zip"
elif command -v 7z &> /dev/null; then
    7z a "../${PACKAGE_NAME}" .
    echo "  ✓ Created ${PACKAGE_NAME} using 7zip"
else
    tar -czf "../${PACKAGE_NAME%.zip}.tar.gz" .
    echo "  ✓ Created ${PACKAGE_NAME%.zip}.tar.gz using tar"
fi
cd ..

# Cleanup temporary directory
rm -rf "${TEMP_DIR}"

echo ""
echo "✓ Final submission package created successfully!"
echo "📦 Package: ${PACKAGE_NAME}"
echo "📁 Location: $(pwd)"
echo ""
echo "Package Contents Summary:"
echo "  • All source code files (.c and .h)"
echo "  • README.md with project description"
echo "  • Comprehensive test plan"
echo "  • Group task breakdown with contributions"
echo "  • Test files demonstrating functionality"
echo "  • Build system (Makefile)"
echo "  • Additional technical documentation"
echo ""
echo "🎉 Ready for submission!"
