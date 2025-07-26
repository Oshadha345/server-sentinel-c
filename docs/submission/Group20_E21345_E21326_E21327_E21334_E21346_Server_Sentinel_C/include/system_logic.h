#ifndef SYSTEM_LOGIC_H
#define SYSTEM_LOGIC_H

#include "common.h"

/**
 * @brief Holds the state for the critical shutdown timer.
 * is_active is true only when the system is in a DANGER state due to temperature.
 * seconds_at_critical counts the consecutive seconds in this state.
 */
typedef struct {
    int seconds_at_critical;
    bool is_active;
} CriticalTimer;

/**
 * @brief Initializes the critical timer to a safe, inactive state.
 * @param state 
 * @param timer Pointer to the CriticalTimer instance to initialize.
 */
void initialize_timer(CriticalTimer* timer);

/**
 * @brief Determines the system's state based on sensor readings.
 * @param reading The current sensor reading (temperature and humidity).
 * @return The determined SystemState (NORMAL, CAUTION, or DANGER).
 */
SystemState determine_system_state(SensorReading reading);

/**
 * @brief Updates the critical timer based on the current system state and temperature.
 * The timer only advances if the state is DANGER and the temperature is above the danger threshold.
 * Otherwise, the timer is reset.
 * @param state The current system state.
 * @param reading The current sensor reading, used to check the temperature.
 * @param timer Pointer to the CriticalTimer instance to update.
 */
void update_critical_timer(SystemState state, SensorReading reading, CriticalTimer* timer);

#endif // SYSTEM_LOGIC_H
