# Server-Sentinel-C Makefile
# GUI-only build system

# Compiler and basic flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./include
LIBS = -lm

# GTK4 flags (required for all builds)
GTK_CFLAGS = $(shell pkg-config --cflags gtk4 2>/dev/null)
GTK_LIBS = $(shell pkg-config --libs gtk4 2>/dev/null)

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
TEST_DIR = test

# Core source files
CORE_SRCS = $(SRC_DIR)/main_controller.c \
            $(SRC_DIR)/smart_data.c \
            $(SRC_DIR)/logger.c \
            $(SRC_DIR)/system_logic.c

# GUI source files (only interface supported)
GUI_SRCS = $(CORE_SRCS) $(SRC_DIR)/gui_interface.c

# Test source files
TEST_SRCS = $(TEST_DIR)/test_main_controller.c \
            $(TEST_DIR)/test_system_logic.c

# Binary names
GUI_BIN = $(BIN_DIR)/server-sentinel
TEST_BIN = $(BIN_DIR)/test-suite

# Default target (GUI only)
all: gui

# GUI build (requires GTK4)
gui: check-gtk $(GUI_BIN)

# GUI binary
$(GUI_BIN): $(SRC_DIR)/main.c $(GUI_SRCS) | $(BIN_DIR)
	@echo "Building GUI interface..."
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -DGUI_INTERFACE $(SRC_DIR)/main.c $(GUI_SRCS) -o $@ $(LIBS) $(GTK_LIBS)
	@echo "GUI build complete: $@"

# Test suite
test: $(TEST_BIN)
	@echo "Running test suite..."

# Heating button test
test-heating: $(BIN_DIR)/test-heating.exe
	@echo "Running heating button test..."
	./$(BIN_DIR)/test-heating.exe

$(BIN_DIR)/test-heating.exe: $(TEST_DIR)/test_heating_button.c $(CORE_SRCS) | $(BIN_DIR)
	@echo "Building heating button test..."
	$(CC) $(CFLAGS) $(TEST_DIR)/test_heating_button.c $(CORE_SRCS) -o $@ $(LIBS)

# Fix button test
test-fix: $(BIN_DIR)/test-fix.exe
	@echo "Running fix button test..."
	./$(BIN_DIR)/test-fix.exe

$(BIN_DIR)/test-fix.exe: $(TEST_DIR)/test_fix_button.c $(CORE_SRCS) | $(BIN_DIR)
	@echo "Building fix button test..."
	$(CC) $(CFLAGS) $(TEST_DIR)/test_fix_button.c $(CORE_SRCS) -o $@ $(LIBS)
	./$(TEST_BIN)

# Test binary
$(TEST_BIN): $(TEST_DIR)/test_main_controller.c $(CORE_SRCS) | $(BIN_DIR)
	@echo "Building test suite..."
	$(CC) $(CFLAGS) $(TEST_DIR)/test_main_controller.c $(CORE_SRCS) -o $@ $(LIBS)
	@echo "Test build complete: $@"

# Create bin directory
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Check for GTK4 development libraries
check-gtk:
	@echo "Checking for GTK4 development libraries..."
	@pkg-config --exists gtk4 || (echo "GTK4 development libraries not found!" && \
		echo "Install with: sudo apt install libgtk-4-dev (Ubuntu/Debian)" && \
		echo "Or with: pacman -S mingw-w64-x86_64-gtk4 (Windows MSYS2)" && \
		echo "Or with: brew install gtk4 (macOS)" && exit 1)
	@echo "GTK4 development libraries found"

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BIN_DIR)/*
	@echo "Clean complete"

# Install system-wide (Unix-like systems)
install: unified
	@echo "Installing Server-Sentinel-C..."
	sudo cp $(GUI_BIN) /usr/local/bin/server-sentinel
	sudo chmod +x /usr/local/bin/server-sentinel
	@echo "Installation complete. Run with: server-sentinel"

# Uninstall system-wide
uninstall:
	@echo "Uninstalling Server-Sentinel-C..."
	sudo rm -f /usr/local/bin/server-sentinel
	@echo "Uninstallation complete"

# Development targets
dev: clean gui
	@echo "Development build complete"

# Debug builds
debug: CFLAGS += -g -DDEBUG
debug: gui

# Show help
help:
	@echo "Server-Sentinel-C Build System"
	@echo "==============================="
	@echo ""
	@echo "Available targets:"
	@echo "  all         - Build CLI and unified binaries (default)"
	@echo "  cli         - Build CLI-only version"
	@echo "  gui         - Build GUI-only version (requires GTK4)"
	@echo "  unified     - Build unified version (supports both CLI and GUI)"
	@echo "  test        - Build and run test suite"
	@echo "  clean       - Remove build artifacts"
	@echo "  install     - Install system-wide (Unix-like systems)"
	@echo "  uninstall   - Remove system installation"
	@echo "  debug-cli   - Build CLI with debug symbols"
	@echo "  debug-gui   - Build GUI with debug symbols"
	@echo "  help        - Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make cli              # Build CLI version only"
	@echo "  make gui              # Build GUI version only"
	@echo "  make unified          # Build both interfaces"
	@echo "  make test             # Run tests"
	@echo "  make clean all        # Clean and rebuild"

# Force GTK4 installation check
check-gtk-force:
	@echo "🔍 Checking GTK4 installation..."
	@echo "GTK4 CFLAGS: $(GTK_CFLAGS)"
	@echo "GTK4 LIBS: $(GTK_LIBS)"
	@pkg-config --exists gtk4 && echo "✅ GTK4 is available" || echo "❌ GTK4 not found"

# Show system information
info:
	@echo "🖥️ Build System Information"
	@echo "=========================="
	@echo "Compiler: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Libraries: $(LIBS)"
	@echo "GTK4 Available: $(shell pkg-config --exists gtk4 && echo 'Yes' || echo 'No')"
	@echo "GTK4 Version: $(shell pkg-config --modversion gtk4 2>/dev/null || echo 'Not found')"
	@echo ""

.PHONY: all cli gui unified test clean install uninstall dev-cli dev-gui debug-cli debug-gui help check-gtk check-gtk-force info
