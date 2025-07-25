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
 * @brief Runs the main application loop.
 * @param controller Pointer to the Controller instance.
 * @return Exit code (0 for normal exit, 1 for error).
 */
int run_main_loop(Controller* controller);

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

/**
 * @brief Parses raw input string into a UserCommand.
 * @param input Raw input string from user.
 * @return UserCommand structure with parsed command type.
 */
UserCommand parse_user_input(const char* input);

/**
 * @brief Displays current system status and alerts.
 * @param controller Pointer to the Controller instance.
 */
void display_system_status(const Controller* controller);

/**
 * @brief Displays help information for available commands.
 */
void display_help();

#endif // MAIN_CONTROLLER_H
