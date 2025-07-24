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
    generator->current_temp = 22.0f;
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
            generator->temp_drift = -3.0f;
            generator->humidity_drift = 1.0f;
            break;
        case HUMIDITY_SPIKE:
            generator->temp_drift = 0.0f;
            generator->humidity_drift = 4.0f;
            break;
        case INTERMITTENT_FAILURE:
            // Start with heating phase
            generator->temp_drift = 2.0f;
            generator->humidity_drift = -0.5f;
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
            // Keep values within a typical stable range
            if (generator->current_temp > 25.0f) generator->current_temp = 25.0f;
            if (generator->current_temp < 21.0f) generator->current_temp = 21.0f;
            if (generator->current_humidity > 55.0f) generator->current_humidity = 55.0f;
            if (generator->current_humidity < 45.0f) generator->current_humidity = 45.0f;
            break;

        case HEATING_UP:
        case COOLING_DOWN:
        case HUMIDITY_SPIKE:
            generator->current_temp += generator->temp_drift;
            generator->current_humidity += generator->humidity_drift;
            break;

        case INTERMITTENT_FAILURE:
            generator->stable_cycles++;
            if (generator->stable_cycles <= 10) { // Heating phase
                if (generator->temp_drift < 0) { // Change to heating
                    generator->temp_drift = 2.0f;
                    generator->humidity_drift = -0.5f;
                }
            } else if (generator->stable_cycles <= 15) { // Cooling phase
                 if (generator->temp_drift > 0) { // Change to cooling
                    generator->temp_drift = -3.0f;
                    generator->humidity_drift = 1.0f;
                }
            } else { // Reset cycle
                generator->stable_cycles = 1;
                generator->temp_drift = 2.0f;
                generator->humidity_drift = -0.5f;
            }
            generator->current_temp += generator->temp_drift;
            generator->current_humidity += generator->humidity_drift;
            break;
    }

    // Clamp humidity to a realistic 0-100 range
    if (generator->current_humidity > 100.0f) generator->current_humidity = 100.0f;
    if (generator->current_humidity < 0.0f) generator->current_humidity = 0.0f;

    SensorReading reading = {generator->current_temp, generator->current_humidity};
    return reading;
}
