#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "common.h"
#include "smart_data.h"
#include "logger.h"
#include "system_logic.h"

// Represents the overall status of the system
typedef struct {
    SystemState state;
    SensorReading last_reading;
    int critical_time;
    bool running;
} SystemStatus;

// Main controller that coordinates all modules
typedef struct {
    SystemStatus status;
    SmartDataGenerator data_generator;
    LogBuffer log_buffer;
    CriticalTimer critical_timer;
} Controller;

// Command types for user input
typedef enum {
    CMD_NONE,
    CMD_FAIL_COOLING,
    CMD_FIX,
    CMD_HUMIDITY_SPIKE,
    CMD_INTERMITTENT,
    CMD_EXIT,
    CMD_HELP,
    CMD_SHOW_LOG
} CommandType;

// User command structure
typedef struct {
    CommandType type;
    char raw_input[64];
} UserCommand;

/**
 * @brief Initializes the entire system with all modules.
 * @param controller Pointer to the Controller instance.
 */
void initialize_system(Controller* controller);

/**
 * @brief Processes a user command and updates the system accordingly.
 * @param controller Pointer to the Controller instance.
 * @param command The user command to process.
 */
void process_command(Controller* controller, UserCommand command);

/**
 * @brief Updates the system state based on current readings.
 * @param controller Pointer to the Controller instance.
 * @param reading The current sensor reading.
 */
void update_system_state(Controller* controller, SensorReading reading);

/**
 * @brief Handles system shutdown procedures.
 * @param controller Pointer to the Controller instance.
 */
void shutdown_system(Controller* controller);

#endif // MAIN_CONTROLLER_H
