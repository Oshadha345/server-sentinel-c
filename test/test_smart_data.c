#include <stdio.h>
#include "../include/smart_data.h"

// Helper function to print a sensor reading
void print_reading(const char* state_name, int cycle, SensorReading reading) {
    printf("[%s, Cycle %d] Temp: %.2f C, Humidity: %.2f %%\n",
           state_name, cycle, reading.temperature, reading.humidity);
}

int main() {
    SmartDataGenerator generator;

    printf("--- Initializing Generator ---\n");
    init_generator(&generator);
    SensorReading reading = generate_reading(&generator);
    print_reading("INITIAL", 0, reading);
    printf("\n");

    // --- Test STABLE state ---
    printf("--- Testing STABLE State ---\n");
    set_generator_state(&generator, STABLE);
    for (int i = 1; i <= 5; i++) {
        reading = generate_reading(&generator);
        print_reading("STABLE", i, reading);
    }
    printf("\n");

    // --- Test HEATING_UP state ---
    printf("--- Testing HEATING_UP State ---\n");
    set_generator_state(&generator, HEATING_UP);
    for (int i = 1; i <= 5; i++) {
        reading = generate_reading(&generator);
        print_reading("HEATING_UP", i, reading);
    }
    printf("\n");

    // --- Test COOLING_DOWN state ---
    printf("--- Testing COOLING_DOWN State ---\n");
    set_generator_state(&generator, COOLING_DOWN);
    for (int i = 1; i <= 5; i++) {
        reading = generate_reading(&generator);
        print_reading("COOLING_DOWN", i, reading);
    }
    printf("\n");

    // --- Test HUMIDITY_SPIKE state ---
    printf("--- Testing HUMIDITY_SPIKE State ---\n");
    set_generator_state(&generator, HUMIDITY_SPIKE);
    for (int i = 1; i <= 5; i++) {
        reading = generate_reading(&generator);
        print_reading("HUMIDITY_SPIKE", i, reading);
    }
    printf("\n");

    // --- Test INTERMITTENT_FAILURE state ---
    printf("--- Testing INTERMITTENT_FAILURE State ---\n");
    set_generator_state(&generator, INTERMITTENT_FAILURE);
    for (int i = 1; i <= 20; i++) { // Run for more cycles to see the pattern
        reading = generate_reading(&generator);
        print_reading("INTERMITTENT", i, reading);
    }
    printf("\n");

    return 0;
}