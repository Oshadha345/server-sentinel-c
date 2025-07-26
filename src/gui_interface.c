#include "../include/gui_interface.h"

#ifdef GUI_INTERFACE

#include <stdio.h>
#include <string.h>

// Forward declarations for callback function
static void on_stable_clicked(GtkWidget *widget, gpointer user_data);
static void on_heating_clicked(GtkWidget *widget, gpointer user_data);
static void on_humidity_spike_clicked(GtkWidget *widget, gpointer user_data);
static void on_intermittent_clicked(GtkWidget *widget, gpointer user_data);
static void on_fail_cooling_clicked(GtkWidget *widget, gpointer user_data);
static void on_fix_clicked(GtkWidget *widget, gpointer user_data);
static void on_show_log_clicked(GtkWidget *widget, gpointer user_data);
static void on_export_log_clicked(GtkWidget *widget, gpointer user_data);
static void on_start_simulation_clicked(GtkWidget *widget, gpointer user_data);
static void on_stop_simulation_clicked(GtkWidget *widget, gpointer user_data);
static void on_exit_clicked(GtkWidget *widget, gpointer user_data);
static gboolean gui_update_display(gpointer user_data);
// Forward declarations for callback functions
static void on_start_simulation_clicked(GtkWidget* button, gpointer user_data);
static void on_stop_simulation_clicked(GtkWidget* button, gpointer user_data);
static void on_export_log_clicked(GtkWidget* button, gpointer user_data);
static void on_file_save_response(GtkNativeDialog* dialog, gint response, gpointer user_data);
static void apply_modern_css(GuiState* state);

// Global GUI state
static GuiState* gui_state = NULL;

// GUI Interface implementation
Interface gui_interface = {
    .initialize = gui_initialize,
    .run_main_loop = gui_run_main_loop,
    .display_status = gui_display_status,
    .display_alert = gui_display_alert,
    .cleanup = gui_cleanup,
    .name = "GTK4 Graphical Interface"
};


// Callback function implementations
static void on_start_simulation_clicked(GtkWidget* button, gpointer user_data) {
    (void)button; // Suppress unused parameter warning
    GuiState* state = (GuiState*)user_data;
    if (!state->simulation_running) {
        state->simulation_running = true;
        time(&state->start_time);
        
        gtk_widget_set_sensitive(state->start_btn, FALSE);
        gtk_widget_set_sensitive(state->stop_btn, TRUE);
        
        // Start the update timer
        g_timeout_add(1000, gui_update_display, state);
        
        gui_display_alert("Simulation Started", 0);
    }
}

static void on_stop_simulation_clicked(GtkWidget* button, gpointer user_data) {
    (void)button; // Suppress unused parameter warning
    GuiState* state = (GuiState*)user_data;
    if (state->simulation_running) {
        state->simulation_running = false;
        
        gtk_widget_set_sensitive(state->start_btn, TRUE);
        gtk_widget_set_sensitive(state->stop_btn, FALSE);
        
        // Close log file if open
        if (state->log_file) {
            fclose(state->log_file);
            state->log_file = NULL;
        }
        
        gui_display_alert("Simulation Stopped", 1);
    }
}

static void on_export_log_clicked(GtkWidget* button, gpointer user_data) {
    (void)button; // Suppress unused parameter warning
    GuiState* state = (GuiState*)user_data;
    
    // Create file chooser dialog using modern GTK4 approach
    GtkFileChooserNative* dialog = gtk_file_chooser_native_new(
        "Save Log File As",
        GTK_WINDOW(state->main_window),
        GTK_FILE_CHOOSER_ACTION_SAVE,
        "_Save",
        "_Cancel"
    );
    
    // Generate default filename with timestamp format
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    char start_time_str[16], current_time_str[16];
    
    strftime(start_time_str, sizeof(start_time_str), "%I%M%p", localtime(&state->start_time));
    strftime(current_time_str, sizeof(current_time_str), "%I%M%p", tm_info);
    
    char filename[256];
    snprintf(filename, sizeof(filename), 
             "Log_%04d-%02d-%02d_%s_%s.txt",
             tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
             start_time_str, current_time_str);
    
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), filename);
    
    gtk_native_dialog_show(GTK_NATIVE_DIALOG(dialog));
    
    // Use a simple callback approach instead of synchronous dialog
    g_signal_connect(dialog, "response", G_CALLBACK(on_file_save_response), state);
}

// Callback for file save response
static void on_file_save_response(GtkNativeDialog* dialog, gint response, gpointer user_data) {
    GuiState* state = (GuiState*)user_data;
    
    if (response == GTK_RESPONSE_ACCEPT) {
        GFile* file = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(dialog));
        char* save_path = g_file_get_path(file);
        
        // Export current log entries to file
        FILE* export_file = fopen(save_path, "w");
        if (export_file) {
            // Write header with current time
            time_t now = time(NULL);
            struct tm* tm_info = localtime(&now);
            fprintf(export_file, "Server Sentinel C - System Log Export\n");
            fprintf(export_file, "Generated: %04d-%02d-%02d %02d:%02d:%02d\n\n",
                    tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
                    tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
            
            // Export all log entries
            LogEntry entries[120];
            int count = get_latest_entries(&state->controller->log_buffer, entries, 120);
            
            for (int i = count - 1; i >= 0; i--) { // Newest first
                const char* state_name = (entries[i].state == NORMAL) ? "NORMAL" : 
                                         (entries[i].state == CAUTION) ? "CAUTION" : 
                                         (entries[i].state == DANGER) ? "DANGER" : "SHUTDOWN";
                
                fprintf(export_file, "[%3d] %.1f°C | %.1f%% RH | %s\n", 
                        count - i, entries[i].reading.temperature, 
                        entries[i].reading.humidity, state_name);
            }
            
            fclose(export_file);
            
            char success_msg[512];
            snprintf(success_msg, sizeof(success_msg), "Log exported successfully to:\n%s", save_path);
            gui_display_alert(success_msg, 0);
        } else {
            gui_display_alert("Failed to save log file", 2);
        }
        
        g_free(save_path);
        g_object_unref(file);
    }
    
    g_object_unref(dialog);
}

static void apply_modern_css(GuiState* state) {
    (void)state; // Suppress unused parameter warning for now
    GtkCssProvider* css_provider = gtk_css_provider_new();
    const char* css_data = 
        "window { "
        "  background-color: #f7f7f8; "
        "  color: #2d3748; "
        "} "
        "frame { "
        "  background-color: #ffffff; "
        "  border: 1px solid #e2e8f0; "
        "  border-radius: 8px; "
        "  padding: 12px; "
        "  margin: 8px; "
        "  box-shadow: 0 1px 3px rgba(0,0,0,0.1); "
        "} "
        "button { "
        "  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); "
        "  color: white; "
        "  border: none; "
        "  border-radius: 6px; "
        "  padding: 8px 16px; "
        "  margin: 4px; "
        "  font-weight: 500; "
        "  transition: all 0.2s ease; "
        "} "
        "button:hover { "
        "  background: linear-gradient(135deg, #5a6fd8 0%, #6a4190 100%); "
        "  transform: translateY(-1px); "
        "  box-shadow: 0 4px 8px rgba(0,0,0,0.2); "
        "} "
        "button.start-btn { "
        "  background: linear-gradient(135deg, #48bb78 0%, #38a169 100%); "
        "} "
        "button.start-btn:hover { "
        "  background: linear-gradient(135deg, #38a169 0%, #2f855a 100%); "
        "} "
        "button.stop-btn { "
        "  background: linear-gradient(135deg, #f56565 0%, #e53e3e 100%); "
        "} "
        "button.stop-btn:hover { "
        "  background: linear-gradient(135deg, #e53e3e 0%, #c53030 100%); "
        "} "
        "label { "
        "  color: #2d3748; "
        "  font-weight: 500; "
        "} "
        "textview { "
        "  background-color: #f8f9fa; "
        "  border: 1px solid #e2e8f0; "
        "  border-radius: 6px; "
        "  padding: 12px; "
        "  font-family: 'SF Mono', 'Monaco', 'Inconsolata', monospace; "
        "} "
        ".status-normal { background-color: #c6f6d5; border-color: #68d391; } "
        ".status-caution { background-color: #faf089; border-color: #f6e05e; } "
        ".status-danger { background-color: #fed7d7; border-color: #fc8181; } "
        ".status-shutdown { background-color: #feb2b2; border-color: #f56565; }";
    
    gtk_css_provider_load_from_string(css_provider, css_data);
    gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                               GTK_STYLE_PROVIDER(css_provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(css_provider);
}

// GTK Application activation callback
static void activate(GtkApplication* app, gpointer user_data) {
    GuiState* state = (GuiState*)user_data;
    
    // Create main window
    state->main_window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(state->main_window), "Server-Sentinel-C");
    gtk_window_set_default_size(GTK_WINDOW(state->main_window), 800, 600);
    
    // Create main container
    GtkWidget* main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_start(main_box, 20);
    gtk_widget_set_margin_end(main_box, 20);
    gtk_widget_set_margin_top(main_box, 20);
    gtk_widget_set_margin_bottom(main_box, 20);
    gtk_window_set_child(GTK_WINDOW(state->main_window), main_box);
    
    // Title label
    GtkWidget* title_label = gtk_label_new("Server-Sentinel-C Server Monitoring System");
    gtk_widget_add_css_class(title_label, "title");
    gtk_box_append(GTK_BOX(main_box), title_label);
    
    // Status frame with warning background
    state->status_frame = gtk_frame_new("System Status");
    state->status_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_margin_start(state->status_box, 10);
    gtk_widget_set_margin_end(state->status_box, 10);
    gtk_widget_set_margin_top(state->status_box, 10);
    gtk_widget_set_margin_bottom(state->status_box, 10);
    gtk_frame_set_child(GTK_FRAME(state->status_frame), state->status_box);
    
    // Status labels
    state->temp_label = gtk_label_new("Temperature: --°C");
    state->humidity_label = gtk_label_new("Humidity: --%");
    state->state_label = gtk_label_new("State: INITIALIZING");
    state->warning_label = gtk_label_new("");
    
    gtk_box_append(GTK_BOX(state->status_box), state->temp_label);
    gtk_box_append(GTK_BOX(state->status_box), state->humidity_label);
    gtk_box_append(GTK_BOX(state->status_box), state->state_label);
    gtk_box_append(GTK_BOX(state->status_box), state->warning_label);
    
    gtk_box_append(GTK_BOX(main_box), state->status_frame);
    
    // Timer frame (for shutdown countdown)
    state->timer_frame = gtk_frame_new("Critical Timer");
    state->timer_label = gtk_label_new("System Operating Normally");
    gtk_widget_set_margin_start(state->timer_label, 10);
    gtk_widget_set_margin_end(state->timer_label, 10);
    gtk_widget_set_margin_top(state->timer_label, 10);
    gtk_widget_set_margin_bottom(state->timer_label, 10);
    gtk_frame_set_child(GTK_FRAME(state->timer_frame), state->timer_label);
    gtk_box_append(GTK_BOX(main_box), state->timer_frame);
    
    // Simulation Control section
    GtkWidget* control_frame = gtk_frame_new("Simulation Control");
    GtkWidget* control_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_margin_start(control_box, 10);
    gtk_widget_set_margin_end(control_box, 10);
    gtk_widget_set_margin_top(control_box, 10);
    gtk_widget_set_margin_bottom(control_box, 10);
    gtk_frame_set_child(GTK_FRAME(control_frame), control_box);
    
    state->start_btn = gtk_button_new_with_label("▶ Start Simulation");
    state->stop_btn = gtk_button_new_with_label("⏸ Stop Simulation");
    gtk_widget_add_css_class(state->start_btn, "start-btn");
    gtk_widget_add_css_class(state->stop_btn, "stop-btn");
    gtk_widget_set_sensitive(state->stop_btn, FALSE); // Initially disabled
    
    g_signal_connect(state->start_btn, "clicked", G_CALLBACK(on_start_simulation_clicked), state);
    g_signal_connect(state->stop_btn, "clicked", G_CALLBACK(on_stop_simulation_clicked), state);
    
    gtk_box_append(GTK_BOX(control_box), state->start_btn);
    gtk_box_append(GTK_BOX(control_box), state->stop_btn);
    
    gtk_box_append(GTK_BOX(main_box), control_frame);
    
    // Scenarios section
    GtkWidget* scenario_frame = gtk_frame_new("Scenarios");
    GtkWidget* scenario_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_margin_start(scenario_box, 10);
    gtk_widget_set_margin_end(scenario_box, 10);
    gtk_widget_set_margin_top(scenario_box, 10);
    gtk_widget_set_margin_bottom(scenario_box, 10);
    gtk_frame_set_child(GTK_FRAME(scenario_frame), scenario_box);
    
    GtkWidget* stable_btn = gtk_button_new_with_label("Stable");
    GtkWidget* heating_btn = gtk_button_new_with_label("Heating Up");
    GtkWidget* humidity_btn = gtk_button_new_with_label("Humidity Spike");
    GtkWidget* intermittent_btn = gtk_button_new_with_label("Intermittent Failure");
    
    g_signal_connect(stable_btn, "clicked", G_CALLBACK(on_stable_clicked), state);
    g_signal_connect(heating_btn, "clicked", G_CALLBACK(on_heating_clicked), state);
    g_signal_connect(humidity_btn, "clicked", G_CALLBACK(on_humidity_spike_clicked), state);
    g_signal_connect(intermittent_btn, "clicked", G_CALLBACK(on_intermittent_clicked), state);
    
    gtk_box_append(GTK_BOX(scenario_box), stable_btn);
    gtk_box_append(GTK_BOX(scenario_box), heating_btn);
    gtk_box_append(GTK_BOX(scenario_box), humidity_btn);
    gtk_box_append(GTK_BOX(scenario_box), intermittent_btn);
    
    gtk_box_append(GTK_BOX(main_box), scenario_frame);
    
    // Response section
    GtkWidget* response_frame = gtk_frame_new("Response");
    GtkWidget* response_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_margin_start(response_box, 10);
    gtk_widget_set_margin_end(response_box, 10);
    gtk_widget_set_margin_top(response_box, 10);
    gtk_widget_set_margin_bottom(response_box, 10);
    gtk_frame_set_child(GTK_FRAME(response_frame), response_box);
    
    GtkWidget* fail_cooling_btn = gtk_button_new_with_label("Fail Cooling");
    GtkWidget* fix_btn = gtk_button_new_with_label("Fix System");
    
    g_signal_connect(fail_cooling_btn, "clicked", G_CALLBACK(on_fail_cooling_clicked), state);
    g_signal_connect(fix_btn, "clicked", G_CALLBACK(on_fix_clicked), state);
    
    gtk_box_append(GTK_BOX(response_box), fail_cooling_btn);
    gtk_box_append(GTK_BOX(response_box), fix_btn);
    
    gtk_box_append(GTK_BOX(main_box), response_frame);
    
    // System section
    GtkWidget* system_frame = gtk_frame_new("System");
    GtkWidget* system_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_margin_start(system_box, 10);
    gtk_widget_set_margin_end(system_box, 10);
    gtk_widget_set_margin_top(system_box, 10);
    gtk_widget_set_margin_bottom(system_box, 10);
    gtk_frame_set_child(GTK_FRAME(system_frame), system_box);
    
    GtkWidget* log_btn = gtk_button_new_with_label("📋 Show Log");
    GtkWidget* export_btn = gtk_button_new_with_label("💾 Export Log");
    GtkWidget* exit_btn = gtk_button_new_with_label("🚪 Exit");
    
    g_signal_connect(log_btn, "clicked", G_CALLBACK(on_show_log_clicked), state);
    g_signal_connect(export_btn, "clicked", G_CALLBACK(on_export_log_clicked), state);
    g_signal_connect(exit_btn, "clicked", G_CALLBACK(on_exit_clicked), state);
    
    gtk_box_append(GTK_BOX(system_box), log_btn);
    gtk_box_append(GTK_BOX(system_box), export_btn);
    gtk_box_append(GTK_BOX(system_box), exit_btn);
    
    gtk_box_append(GTK_BOX(main_box), system_frame);
    
    // Live Log Display
    GtkWidget* log_frame = gtk_frame_new("📊 Live System Log (Latest 20 Entries)");
    GtkWidget* log_scroll = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(log_scroll), 
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(log_scroll, -1, 150);
    
    state->log_textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(state->log_textview), FALSE);
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(state->log_textview), TRUE);
    state->log_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(state->log_textview));
    gtk_text_buffer_set_text(state->log_buffer, "Initializing system log...\n", -1);
    
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(log_scroll), state->log_textview);
    gtk_frame_set_child(GTK_FRAME(log_frame), log_scroll);
    gtk_box_append(GTK_BOX(main_box), log_frame);
    
    // Show window
    gtk_window_present(GTK_WINDOW(state->main_window));
    
    // Apply modern CSS styling
    apply_modern_css(state);
    
    // Don't start timer automatically - wait for user to start simulation
}

void gui_initialize(Controller* controller) {
    if (!controller) return;
    
    // Allocate GUI state
    gui_state = g_malloc(sizeof(GuiState));
    gui_state->controller = controller;
    gui_state->running = true;
    gui_state->simulation_running = false;
    gui_state->timer_id = 0;
    gui_state->log_file_path = NULL;
    gui_state->log_file = NULL;
    gui_state->start_time = 0;
    
    // Initialize core system
    initialize_system(controller);
    
    // Create GTK application
    gui_state->app = gtk_application_new("com.oshadha.server-sentinel-c", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(gui_state->app, "activate", G_CALLBACK(activate), gui_state);
}

int gui_run_main_loop(Controller* controller) {
    if (!controller || !gui_state) return 1;
    
    // Run GTK main loop
    int status = g_application_run(G_APPLICATION(gui_state->app), 0, NULL);
    
    return status;
}

void gui_display_status(const Controller* controller) {
    if (!controller || !gui_state) return;
    
    char temp_text[64], humidity_text[64], state_text[64], warning_text[128];
    
    // Update temperature
    snprintf(temp_text, sizeof(temp_text), "Temperature: %.1f°C", 
             controller->status.last_reading.temperature);
    gtk_label_set_text(GTK_LABEL(gui_state->temp_label), temp_text);
    
    // Update humidity
    snprintf(humidity_text, sizeof(humidity_text), "Humidity: %.1f%%", 
             controller->status.last_reading.humidity);
    gtk_label_set_text(GTK_LABEL(gui_state->humidity_label), humidity_text);
    
    // Update state and warning system
    const char* state_icon;
    const char* state_name;
    const char* warning_msg = "";
    
    switch (controller->status.state) {
        case NORMAL:
            state_icon = "[OK]";
            state_name = "NORMAL";
            break;
        case CAUTION:
            state_icon = "[!]";
            state_name = "CAUTION";
            warning_msg = "System requires attention";
            break;
        case DANGER:
            state_icon = "[!!]";
            state_name = "DANGER";
            warning_msg = "Critical condition detected!";
            break;
        case SHUTDOWN:
            state_icon = "[X]";
            state_name = "SHUTDOWN";
            warning_msg = "EMERGENCY SHUTDOWN INITIATED!\n             (EXIT AND RESTART)";
            break;
        default:
            state_icon = "[?]";
            state_name = "UNKNOWN";
            break;
    }
    
    snprintf(state_text, sizeof(state_text), "%s State: %s", state_icon, state_name);
    gtk_label_set_text(GTK_LABEL(gui_state->state_label), state_text);
    
    // Update warning label
    snprintf(warning_text, sizeof(warning_text), "%s", warning_msg);
    gtk_label_set_text(GTK_LABEL(gui_state->warning_label), warning_text);
    
    // Update status frame background color using modern CSS classes
    const char* css_class = (controller->status.state == NORMAL) ? "status-normal" :
                            (controller->status.state == CAUTION) ? "status-caution" :
                            (controller->status.state == DANGER) ? "status-danger" : "status-shutdown";
    
    // Remove old classes and add new one
    gtk_widget_remove_css_class(gui_state->status_frame, "status-normal");
    gtk_widget_remove_css_class(gui_state->status_frame, "status-caution");
    gtk_widget_remove_css_class(gui_state->status_frame, "status-danger");
    gtk_widget_remove_css_class(gui_state->status_frame, "status-shutdown");
    gtk_widget_add_css_class(gui_state->status_frame, css_class);
    
    // Update timer
    char timer_text[64];
    if (controller->status.state == DANGER || controller->status.state == SHUTDOWN) {
        snprintf(timer_text, sizeof(timer_text), "Shutdown Timer: %ds", 
                 controller->critical_timer.seconds_at_critical);
        gtk_widget_set_visible(gui_state->timer_frame, TRUE);
    } else {
        snprintf(timer_text, sizeof(timer_text), "System Operating Normally");
        gtk_widget_set_visible(gui_state->timer_frame, FALSE);
    }
    gtk_label_set_text(GTK_LABEL(gui_state->timer_label), timer_text);
}

void gui_display_alert(const char* message, int severity) {
    if (!message || !gui_state) return;
    
    // Create a simple alert window
    GtkWidget* dialog = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(dialog), 
                        (severity == 2) ? "Error" : 
                        (severity == 1) ? "Warning" : "Information");
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(gui_state->main_window));
    gtk_window_set_default_size(GTK_WINDOW(dialog), 300, 150);
    
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_bottom(box, 20);
    gtk_widget_set_margin_start(box, 20);
    gtk_widget_set_margin_end(box, 20);
    
    GtkWidget* label = gtk_label_new(message);
    gtk_label_set_wrap(GTK_LABEL(label), TRUE);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    
    GtkWidget* button = gtk_button_new_with_label("OK");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), dialog);
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    
    gtk_box_append(GTK_BOX(box), label);
    gtk_box_append(GTK_BOX(box), button);
    gtk_window_set_child(GTK_WINDOW(dialog), box);
    
    gtk_window_present(GTK_WINDOW(dialog));
}

void gui_cleanup(void) {
    if (gui_state) {
        if (gui_state->timer_id > 0) {
            g_source_remove(gui_state->timer_id);
        }
        if (gui_state->app) {
            g_object_unref(gui_state->app);
        }
        g_free(gui_state);
        gui_state = NULL;
    }
}

gboolean gui_update_display(gpointer user_data) {
    GuiState* state = (GuiState*)user_data;
    if (!state || !state->controller || !state->running || !state->simulation_running) {
        return FALSE; // Stop timer if not running or simulation stopped
    }
    
    Controller* controller = state->controller;
    
    // Generate new sensor reading
    SensorReading reading = generate_reading(&controller->data_generator);
    controller->status.last_reading = reading;
    
    // Update system state
    update_system_state(controller, reading);
    
    // Log the reading
    log_reading(&controller->log_buffer, reading, controller->status.state);
    
    // Write to log file if active
    if (state->log_file) {
        time_t now = time(NULL);
        struct tm* tm_info = localtime(&now);
        char timestamp[64];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
        
        const char* state_name = (controller->status.state == NORMAL) ? "NORMAL" : 
                                 (controller->status.state == CAUTION) ? "CAUTION" : 
                                 (controller->status.state == DANGER) ? "DANGER" : "SHUTDOWN";
        
        fprintf(state->log_file, "%s | %.1f°C | %.1f%% | %s | Timer: %ds\n",
                timestamp, reading.temperature, reading.humidity, state_name,
                controller->critical_timer.seconds_at_critical);
        fflush(state->log_file);
    }
    
    // Update GUI display
    gui_display_status(controller);
    
    // Update log display - Show latest 20 entries from 120 total, newest first
    if (state->log_buffer) {
        LogEntry entries[120]; // Read all 120 entries
        int count = get_latest_entries(&controller->log_buffer, entries, 120);
        
        char log_text[4096] = "";
        int display_count = (count > 20) ? 20 : count; // Show only latest 20
        
        for (int i = display_count - 1; i >= 0; i--) { // Reverse order to show newest first
            char entry_text[128];
            const char* state_name = (entries[i].state == NORMAL) ? "NORMAL" : 
                                     (entries[i].state == CAUTION) ? "CAUTION" : 
                                     (entries[i].state == DANGER) ? "DANGER" : "SHUTDOWN";
            
            // More detailed log format with better spacing
            snprintf(entry_text, sizeof(entry_text), 
                     "[%3d] %6.1f°C | %5.1f%% | %-8s\n", 
                     count - i, entries[i].reading.temperature, 
                     entries[i].reading.humidity, 
                     state_name);
            strcat(log_text, entry_text);
        }
        
        gtk_text_buffer_set_text(state->log_buffer, log_text, -1);
        
        // Auto-scroll to top to show newest entries
        GtkTextIter start;
        gtk_text_buffer_get_start_iter(state->log_buffer, &start);
        gtk_text_buffer_place_cursor(state->log_buffer, &start);
    }
    
    // Check for shutdown
    if (controller->status.state == SHUTDOWN) {
        gui_display_alert("CRITICAL SHUTDOWN INITIATED", 2);
        state->simulation_running = false;
        gtk_widget_set_sensitive(state->start_btn, TRUE);
        gtk_widget_set_sensitive(state->stop_btn, FALSE);
        shutdown_system(controller);
        return FALSE; // Stop timer
    }
    
    return TRUE; // Continue timer
}

// Button callbacks
void on_fail_cooling_clicked(GtkWidget* widget, gpointer user_data) {
    (void)widget; // Suppress unused parameter warning
    GuiState* state = (GuiState*)user_data;
    
    UserCommand cmd = {CMD_FAIL_COOLING, "fail_cooling"};
    process_command(state->controller, cmd);
    
    // Force immediate GUI update to show the change
    gui_display_status(state->controller);
    
    gui_display_alert("Cooling system failure simulated", 1);
}

void on_fix_clicked(GtkWidget* widget, gpointer user_data) {
    (void)widget; // Suppress unused parameter warning
    GuiState* state = (GuiState*)user_data;
    
    UserCommand cmd = {CMD_FIX, "fix"};
    process_command(state->controller, cmd);
    
    // Force immediate GUI update to show the change
    gui_display_status(state->controller);
    
    gui_display_alert("System repair applied", 0);
}

void on_humidity_spike_clicked(GtkWidget* widget, gpointer user_data) {
    (void)widget; // Suppress unused parameter warning
    GuiState* state = (GuiState*)user_data;
    
    UserCommand cmd = {CMD_HUMIDITY_SPIKE, "humidity_spike"};
    process_command(state->controller, cmd);
    
    // Force immediate GUI update to show the change
    gui_display_status(state->controller);
    
    gui_display_alert("Humidity spike simulated", 1);
}

// New callback functions
void on_stable_clicked(GtkWidget* widget, gpointer user_data) {
    (void)widget; // Suppress unused parameter warning
    GuiState* state = (GuiState*)user_data;
    
    // Set stable state and fix any issues
    set_generator_state(&state->controller->data_generator, STABLE);
    UserCommand cmd = {CMD_FIX, "stable"};
    process_command(state->controller, cmd);
    
    // Force immediate GUI update to show the change
    gui_display_status(state->controller);
    
    gui_display_alert("System stabilized", 0);
}

void on_heating_clicked(GtkWidget* widget, gpointer user_data) {
    (void)widget; // Suppress unused parameter warning
    GuiState* state = (GuiState*)user_data;
    
    // Simulate heating scenario
    set_generator_state(&state->controller->data_generator, HEATING_UP);
    
    // Force immediate GUI update to show the change
    gui_display_status(state->controller);
    
    gui_display_alert("Heating scenario activated", 1);
}


void on_intermittent_clicked(GtkWidget* widget, gpointer user_data) {
    (void)widget; // Suppress unused parameter warning
    GuiState* state = (GuiState*)user_data;
    
    // Simulate intermittent failure
    set_generator_state(&state->controller->data_generator, INTERMITTENT_FAILURE);
    
    // Force immediate GUI update to show the change
    gui_display_status(state->controller);
    
    gui_display_alert("Intermittent failure simulated", 1);
}

void on_show_log_clicked(GtkWidget* widget, gpointer user_data) {
    (void)widget; // Suppress unused parameter warning
    GuiState* state = (GuiState*)user_data;
    
    // Create log window
    GtkWidget* dialog = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "System Log");
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(state->main_window));
    gtk_window_set_default_size(GTK_WINDOW(dialog), 600, 400);
    
    GtkWidget* main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(main_box, 10);
    gtk_widget_set_margin_bottom(main_box, 10);
    gtk_widget_set_margin_start(main_box, 10);
    gtk_widget_set_margin_end(main_box, 10);
    
    GtkWidget* scroll = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), 
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_widget_set_size_request(scroll, 600, 400);
    
    GtkWidget* text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    
    // Get log entries
    LogEntry entries[20];
    int count = get_latest_entries(&state->controller->log_buffer, entries, 20);
    
    char full_log[2048] = "Recent Log Entries:\n\n";
    for (int i = count - 1; i >= 0; i--) {
        char entry_text[128];
        const char* state_name = (entries[i].state == NORMAL) ? "NORMAL" : 
                                 (entries[i].state == CAUTION) ? "CAUTION" : 
                                 (entries[i].state == DANGER) ? "DANGER" : "SHUTDOWN";
        snprintf(entry_text, sizeof(entry_text), 
                 "Entry %d: %.1f°C, %.1f%%, %s\n", 
                 count - i, entries[i].reading.temperature, 
                 entries[i].reading.humidity, state_name);
        strcat(full_log, entry_text);
    }
    
    gtk_text_buffer_set_text(buffer, full_log, -1);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), text_view);
    gtk_box_append(GTK_BOX(main_box), scroll);
    
    // Add close button
    GtkWidget* close_btn = gtk_button_new_with_label("Close");
    g_signal_connect_swapped(close_btn, "clicked", G_CALLBACK(gtk_window_destroy), dialog);
    gtk_widget_set_halign(close_btn, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(main_box), close_btn);
    
    gtk_window_set_child(GTK_WINDOW(dialog), main_box);
    gtk_window_present(GTK_WINDOW(dialog));
}

void on_exit_clicked(GtkWidget* widget, gpointer user_data) {
    (void)widget; // Suppress unused parameter warning
    GuiState* state = (GuiState*)user_data;
    state->running = false;
    state->controller->status.running = false;
    
    if (state->main_window) {
        gtk_window_destroy(GTK_WINDOW(state->main_window));
    }
    
    g_application_quit(G_APPLICATION(state->app));
}

#else
// Dummy implementations when GUI is not enabled
Interface gui_interface = {
    .initialize = NULL,
    .run_main_loop = NULL,
    .display_status = NULL,
    .display_alert = NULL,
    .cleanup = NULL,
    .name = "GUI Interface (Not Available)"
};

void gui_initialize(Controller* controller) {
    printf("❌ GUI interface not available (compile with -DGUI_INTERFACE)\n");
}

int gui_run_main_loop(Controller* controller) {
    printf("❌ GUI interface not available\n");
    return 1;
}

void gui_display_status(const Controller* controller) {}
void gui_display_alert(const char* message, int severity) {}
void gui_cleanup(void) {}

#endif // GUI_INTERFACE
