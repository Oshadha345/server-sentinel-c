#include "../include/main_controller.h"
#include "../include/gui_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_usage(const char* program_name) {
    printf("Server-Sentinel-C Server Monitoring System\n");
    printf("=================================================\n\n");
    printf("Usage: %s [OPTIONS]\n\n", program_name);
    printf("Options:\n");
    printf("  --help     Show this help message\n");
    printf("  --version  Show version information\n\n");
    printf("Note: This version only supports the GTK4 Graphical Interface.\n");
    printf("Please ensure GTK4 libraries are installed.\n");
    printf("\nFor more information, see the user manual.\n");
}

void show_version() {
    printf("Server-Sentinel-C v1.0.0\n");
    printf("Server Monitoring System for Data Centers\n");
    printf("Built with C and GTK4\n");
    printf("Copyright (C) 2025 Group 20 - CO253 Project\n");
}

int main(int argc, char* argv[]) {
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            show_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            show_version();
            return 0;
        } else {
            printf("Unknown option: %s\n", argv[i]);
            show_usage(argv[0]);
            return 1;
        }
    }
    
    printf("Starting Server-Sentinel-C with GUI Interface\n");
    printf("=============================================\n\n");

    // Create the main controller
    Controller controller;

    // Initialize the GUI interface
    gui_initialize(&controller);

    // Run the main application loop  
    int exit_code = gui_run_main_loop(&controller);

    // Cleanup
    gui_cleanup();

    // Final message
    if (exit_code == 0) {
        printf("\nServer-Sentinel-C terminated successfully.\n");
    } else {
        printf("\nServer-Sentinel-C terminated due to critical conditions.\n");
    }

    printf("Thank you for using Server-Sentinel-C!\n");
    return exit_code;
}
