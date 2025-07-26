#ifndef GUI_INTERFACE_H
#define GUI_INTERFACE_H

#include "interface.h"

#ifdef GUI_INTERFACE
#include <gtk/gtk.h>

/**
 * @brief GTK4 Graphical User Interface implementation
 * Provides a modern, user-friendly graphical interface
 */

/**
 * @brief GUI application state structure
 */
typedef struct {
    GtkApplication* app;
    GtkWidget* main_window;
    GtkWidget* temp_label;
    GtkWidget* humidity_label;
    GtkWidget* state_label;
    GtkWidget* timer_label;
    GtkWidget* warning_label;
    GtkWidget* status_frame;
    GtkWidget* status_box;
    GtkWidget* timer_frame;
    GtkWidget* log_textview;
    GtkTextBuffer* log_buffer;
    GtkWidget* start_btn;
    GtkWidget* stop_btn;
    Controller* controller;
    guint timer_id;
    bool running;
    bool simulation_running;
    char* log_file_path;
    FILE* log_file;
    time_t start_time;
} GuiState;

/**
 * @brief Initialize the GUI interface
 * @param controller Pointer to the main controller
 */
void gui_initialize(Controller* controller);

/**
 * @brief Run the GUI main loop
 * @param controller Pointer to the main controller
 * @return Exit code
 */
int gui_run_main_loop(Controller* controller);

/**
 * @brief Display system status in GUI
 * @param controller Pointer to the main controller
 */
void gui_display_status(const Controller* controller);

/**
 * @brief Display alert message in GUI
 * @param message Alert message
 * @param severity Alert severity level
 */
void gui_display_alert(const char* message, int severity);

/**
 * @brief Cleanup GUI resources
 */
void gui_cleanup(void);

#endif // GUI_INTERFACE

#endif // GUI_INTERFACE_H
