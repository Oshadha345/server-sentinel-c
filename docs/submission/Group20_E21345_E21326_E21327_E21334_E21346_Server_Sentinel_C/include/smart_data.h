#ifndef SMART_DATA_H
#define SMART_DATA_H

#include "common.h"

// Represents the different simulation scenarios for generating mock data.
typedef enum {
    STABLE,
    HEATING_UP,
    COOLING_DOWN,
    HUMIDITY_SPIKE,
    INTERMITTENT_FAILURE
} MockDataState;

// Maintains the state of the data generator.
typedef struct {
    MockDataState state;        // Current simulation state
    float current_temp;         // Last generated temperature
    float current_humidity;     // Last generated humidity
    float temp_drift;           // Rate of temperature change per cycle
    float humidity_drift;       // Rate of humidity change per cycle
    int stable_cycles;          // Counter for tracking alternating states
} SmartDataGenerator;

// Function prototypes
void init_generator(SmartDataGenerator* generator);
void set_generator_state(SmartDataGenerator* generator, MockDataState new_state);
SensorReading generate_reading(SmartDataGenerator* generator);

#endif // SMART_DATA_H
