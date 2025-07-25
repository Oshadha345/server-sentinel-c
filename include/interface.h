#ifndef INTERFACE_H
#define INTERFACE_H

#include "main_controller.h"

/**
 * @brief Interface abstraction for GUI interface
 * This provides a clean interface for the GUI implementation
 * to interact with the core system.
 */
typedef struct {
    /**
     * @brief Initialize the interface
     * @param controller Pointer to the main controller
     */
    void (*initialize)(Controller* controller);
    
    /**
     * @brief Run the main interface loop
     * @param controller Pointer to the main controller
     * @return Exit code (0 = success, non-zero = error)
     */
    int (*run_main_loop)(Controller* controller);
    
    /**
     * @brief Display current system status
     * @param controller Pointer to the main controller
     */
    void (*display_status)(const Controller* controller);
    
    /**
     * @brief Display an alert message
     * @param message Alert message to display
     * @param severity Alert severity (0=info, 1=warning, 2=critical)
     */
    void (*display_alert)(const char* message, int severity);
    
    /**
     * @brief Cleanup interface resources
     */
    void (*cleanup)(void);
    
    /**
     * @brief Interface name for identification
     */
    const char* name;
} Interface;

// GUI interface implementation
extern Interface gui_interface;

#endif // INTERFACE_H
