#include "../include/main_controller.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Initializes the entire system with all modules.
void initialize_system(Controller* controller) {
    if (!controller) return;

    // Initialize all modules
    init_generator(&controller->data_generator);
    initialize_logger(&controller->log_buffer);
    initialize_timer(&controller->critical_timer);

    // Initialize system status
    controller->status.state = NORMAL;
    controller->status.last_reading.temperature = 22.0f;
    controller->status.last_reading.humidity = 50.0f;
    controller->status.critical_time = 0;
    controller->status.running = true;
}

// Processes a user command and updates the system accordingly.
void process_command(Controller* controller, UserCommand command) {
    if (!controller) return;

    switch (command.type) {
        case CMD_FAIL_COOLING:
            set_generator_state(&controller->data_generator, HEATING_UP);
            break;

        case CMD_FIX:
            // Check current temperature to determine appropriate action
            if (controller->status.last_reading.temperature > 25.0f) {
                set_generator_state(&controller->data_generator, COOLING_DOWN);
            } else if (controller->status.last_reading.temperature < 20.0f) {
                set_generator_state(&controller->data_generator, HEATING_UP);
            } else {
                set_generator_state(&controller->data_generator, STABLE);
            }
            break;

        case CMD_HUMIDITY_SPIKE:
            set_generator_state(&controller->data_generator, HUMIDITY_SPIKE);
            break;

        case CMD_INTERMITTENT:
            set_generator_state(&controller->data_generator, INTERMITTENT_FAILURE);
            break;

        case CMD_SHOW_LOG:
            // Log display is handled by GUI
            break;

        case CMD_EXIT:
            controller->status.running = false;
            break;

        case CMD_HELP:
        case CMD_NONE:
        default:
            // Command handling is done by GUI
            break;
    }
}

// Updates the system state based on current readings.
void update_system_state(Controller* controller, SensorReading reading) {
    if (!controller) return;

    // Determine new state based on reading
    SystemState new_state = determine_system_state(reading);
    controller->status.state = new_state;

    // Update critical timer
    update_critical_timer(new_state, reading, &controller->critical_timer);
    controller->status.critical_time = controller->critical_timer.seconds_at_critical;

    // Check for shutdown condition
    if (controller->critical_timer.seconds_at_critical >= CRITICAL_SHUTDOWN_SECONDS) {
        controller->status.state = SHUTDOWN;
    }
}

// Handles system shutdown procedures.
void shutdown_system(Controller* controller) {
    if (!controller) return;

    // Log the shutdown event
    log_reading(&controller->log_buffer, controller->status.last_reading, SHUTDOWN);
    
    controller->status.running = false;
}
