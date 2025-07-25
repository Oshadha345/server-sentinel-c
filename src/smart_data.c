#include "../include/smart_data.h"
#include <stdlib.h>
#include <time.h>

// Private function to apply small random fluctuations for STABLE state
static float add_fluctuation(float value, float max_fluctuation) {
    float fluctuation = ((float)rand() / (float)RAND_MAX) * max_fluctuation * 2.0f - max_fluctuation;
    return value + fluctuation;
}

// Initializes the data generator to a stable state.
void init_generator(SmartDataGenerator* generator) {
    if (!generator) return;

    srand(time(NULL)); // Seed the random number generator
    generator->current_temp = 22.5f;  // Start in nominal range
    generator->current_humidity = 50.0f;
    generator->stable_cycles = 0;
    set_generator_state(generator, STABLE);
}

// Sets the data generator to a new simulation state.
void set_generator_state(SmartDataGenerator* generator, MockDataState new_state) {
    if (!generator) return;

    generator->state = new_state;
    generator->stable_cycles = 0; // Reset cycle count on state change

    switch (new_state) {
        case STABLE:
            generator->temp_drift = 0.1f;
            generator->humidity_drift = 0.1f;
            break;
        case HEATING_UP:
            generator->temp_drift = 2.0f;
            generator->humidity_drift = -0.5f;
            break;
        case COOLING_DOWN:
            generator->temp_drift = -2.0f;  // Cool down at same rate as heating up
            generator->humidity_drift = 0.5f;  // Humidity normalizes
            break;
        case HUMIDITY_SPIKE:
            generator->temp_drift = 0.0f;
            generator->humidity_drift = 4.0f;
            break;
        case INTERMITTENT_FAILURE:
            // Start with heating phase
            generator->temp_drift = 0.8f;
            generator->humidity_drift = -0.32f;
            break;
    }
}

// Generates the next sensor reading based on the current state.
SensorReading generate_reading(SmartDataGenerator* generator) {
    if (!generator) {
        SensorReading empty_reading = {0.0f, 0.0f};
        return empty_reading;
    }

    switch (generator->state) {
        case STABLE:
            generator->current_temp = add_fluctuation(generator->current_temp, generator->temp_drift);
            generator->current_humidity = add_fluctuation(generator->current_humidity, generator->humidity_drift);
            // Keep values within a typical stable range (20-25°C nominal)
            if (generator->current_temp > 25.0f) generator->current_temp = 25.0f;
            if (generator->current_temp < 20.0f) generator->current_temp = 20.0f;
            if (generator->current_humidity > 55.0f) generator->current_humidity = 55.0f;
            if (generator->current_humidity < 45.0f) generator->current_humidity = 45.0f;
            break;

        case HEATING_UP:
            generator->current_temp += generator->temp_drift;
            generator->current_humidity += generator->humidity_drift;
            
            // Add upper bound for heating scenario (90-110°C fluctuation)
            if (generator->current_temp > 110.0f) {
                generator->current_temp = 90.0f + ((float)rand() / (float)RAND_MAX) * 20.0f; // 90-110°C range
            }
            
            // Prevent temperature from going too low (minimum 10°C for server room)
            if (generator->current_temp < 10.0f) {
                generator->current_temp = 10.0f;
            }
            break;

        case COOLING_DOWN:
            generator->current_temp += generator->temp_drift;  // temp_drift is negative (-2.0f)
            generator->current_humidity += generator->humidity_drift;
            
            // Auto-stabilize when temperature reaches nominal range (20-25°C)
            if (generator->current_temp >= 20.0f && generator->current_temp <= 25.0f) {
                set_generator_state(generator, STABLE);
                generator->current_temp = 22.5f; // Set to middle of nominal range
                generator->current_humidity = 50.0f; // Normalize humidity
            }
            
            // Prevent temperature from going too low (minimum 10°C)
            if (generator->current_temp < 10.0f) {
                generator->current_temp = 10.0f;
            }
            
            // Keep humidity in reasonable range
            if (generator->current_humidity > 80.0f) generator->current_humidity = 80.0f;
            if (generator->current_humidity < 30.0f) generator->current_humidity = 30.0f;
            break;
            
        case HUMIDITY_SPIKE:
            generator->current_temp += generator->temp_drift;
            generator->current_humidity += generator->humidity_drift;
            
            // Prevent temperature from going too low (minimum 10°C for server room)
            if (generator->current_temp < 10.0f) {
                generator->current_temp = 10.0f;
            }
            
            // Auto-stabilize when temperature reaches nominal range during fix operations
            if ( generator->current_temp <= 25.0f && generator->current_temp >= 20.0f) {
                set_generator_state(generator, STABLE);
                generator->current_temp = 22.5f; // Set to middle of nominal range
            }
            break;

        case INTERMITTENT_FAILURE:
            generator->stable_cycles++;
            if (generator->stable_cycles <= 5) { // Heating phase
                if (generator->temp_drift < 0) { // Change to heating
                    generator->temp_drift = 0.8f + ((float)rand() / (float)RAND_MAX) * 0.25f;
                    generator->humidity_drift = -0.32f;
                }
            } else if (generator->stable_cycles <= 8) { // Cooling phase
                 if (generator->temp_drift > 0) { // Change to cooling
                    generator->temp_drift = -0.8f + ((float)rand() / (float)RAND_MAX) * 0.25f;  // Reduced cooling rate
                    generator->humidity_drift = 0.32f;
                }
            } else { // Reset cycle
                generator->stable_cycles = 1;
                generator->temp_drift = 0.8f;
                generator->humidity_drift = -0.32f;
            }
            generator->current_temp += generator->temp_drift;
            generator->current_humidity += generator->humidity_drift;
            
            // Prevent temperature from going too low (minimum 10°C for server room)
            if (generator->current_temp < 10.0f) {
                generator->current_temp = 10.0f;
            }
            break;
    }

    // Clamp humidity to a realistic 0-100 range
    if (generator->current_humidity > 100.0f) generator->current_humidity = 100.0f;
    if (generator->current_humidity < 0.0f) generator->current_humidity = 0.0f;

    SensorReading reading = {generator->current_temp, generator->current_humidity};
    return reading;
}
