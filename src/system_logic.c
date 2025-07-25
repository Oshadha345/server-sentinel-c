#include "../include/system_logic.h"

/**
 * @brief Initializes the critical timer to a safe, inactive state.
 */
void initialize_timer(CriticalTimer* timer) {
    if (timer == NULL) {
        return;
    }
    timer->seconds_at_critical = 0;
    timer->is_active = false;
}

/**
 * @brief Determines the system's state based on sensor readings.
 *
 * The function checks for conditions in order of severity: DANGER, then CAUTION.
 * If no alert conditions are met, the state is NORMAL.
 */
SystemState determine_system_state(SensorReading reading) {
    // Check for DANGER conditions first
    if (reading.temperature > TEMP_DANGER_THRESHOLD ||
        reading.humidity < HUMID_LOW_DANGER ||
        reading.humidity > HUMID_HIGH_DANGER) {
        return DANGER;
    }

    // If not in DANGER, check for CAUTION conditions
    if (reading.temperature > TEMP_CAUTION_THRESHOLD ||
        reading.humidity < HUMID_LOW_CAUTION ||
        reading.humidity > HUMID_HIGH_CAUTION) {
        return CAUTION;
    }

    // Otherwise, the system is in a NORMAL state
    return NORMAL;
}

/**
 * @brief Updates the critical timer based on the current system state and temperature.
 *
 * The shutdown timer is a critical feature that should only be active when the system
 * is in a DANGER state specifically because of high temperature. A DANGER state
 * triggered by humidity alone should not start the shutdown countdown.
 */
// Updates the critical timer based on the system state and reading.
void update_critical_timer(SystemState state, SensorReading reading, CriticalTimer* timer) {
    if (!timer) return;

    // The timer is only active if the state is DANGER due to temperature
    if (state == DANGER && reading.temperature > TEMP_DANGER_THRESHOLD) {
        if (!timer->is_active) {
            timer->is_active = true;
            timer->seconds_at_critical = 0; // Start the timer
        }
        timer->seconds_at_critical++;
    } else {
        // If conditions are not temperature-based DANGER, reset the timer
        initialize_timer(timer);
    }
}
