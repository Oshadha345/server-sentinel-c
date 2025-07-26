#include <stdio.h>
#include <assert.h>
#include <unistd.h> // For sleep() function

// Include all necessary module headers
#include "../include/smart_data.h"
#include "../include/logger.h"
#include "../include/system_logic.h"

void test_full_cycle_integration() {
    printf("--- Running Full Cycle Integration Test ---\n\n");

    // 1. Initialize all modules
    SmartDataGenerator data_generator;
    LogBuffer log_buffer;
    CriticalTimer critical_timer;
    SystemState current_state = NORMAL;

    // Use the EXACT function names from the header files
    init_generator(&data_generator);        // From smart_data.h
    initialize_logger(&log_buffer);         // From logger.h
    initialize_timer(&critical_timer);      // From system_logic.h

    printf("Step 1: Simulating a cooling failure (HEATING_UP)...\n");
    set_generator_state(&data_generator, HEATING_UP);  // From smart_data.h

    bool reached_danger = false;
    int simulation_cycles = 40;

    for (int i = 0; i < simulation_cycles; i++) {
        // 2. Generate data
        SensorReading reading = generate_reading(&data_generator);  // From smart_data.h

        // 3. Determine state based on data
        current_state = determine_system_state(reading);  // From system_logic.h

        // 4. Update the critical timer with the correct 3-parameter signature
        update_critical_timer(current_state, reading, &critical_timer);  // From system_logic.h

        // 5. Log the event
        log_reading(&log_buffer, reading, current_state);  // From logger.h

        // --- Print current status for visual verification ---
        printf("Cycle %2d: Temp: %5.1f°C, Hum: %4.1f%% -> State: %-7s, Critical Timer: %2d s\n",
               i + 1,
               reading.temperature,
               reading.humidity,
               (current_state == NORMAL) ? "NORMAL" : (current_state == CAUTION) ? "CAUTION" : "DANGER",
               critical_timer.seconds_at_critical);

        // --- Automated Assertions and Scenario Changes ---
        if (current_state == DANGER && !reached_danger) {
            printf("\n!!! DANGER STATE REACHED. Critical timer is active. !!!\n\n");
            reached_danger = true;
        }

        // Simulate a "fix" after 5 seconds in DANGER state
        if (reached_danger && critical_timer.seconds_at_critical >= 5) {
            printf("\nStep 2: Simulating a successful fix (COOLING_DOWN)...\n");
            set_generator_state(&data_generator, COOLING_DOWN);
        }
    }

    // --- Final Verification ---
    printf("\n--- Final System State Verification ---\n");
    assert(current_state == NORMAL && "System should have returned to NORMAL state after the fix.");
    assert(critical_timer.is_active == false && "Critical timer should be inactive at the end.");
    assert(log_buffer.count > 0 && "Log buffer should contain entries.");
    printf("Final state is NORMAL as expected.\n");

    // 6. Print the final log using get_latest_entries from logger.h
    printf("\n--- Final Log History ---\n");
    printf("Displaying last 10 entries:\n");
    LogEntry entries[10];
    int count = get_latest_entries(&log_buffer, entries, 10);  // From logger.h
    for (int i = 0; i < count; i++) {
        printf("Entry %d: Temp: %.1f°C, Humidity: %.1f%%, State: %d\n", 
               i + 1, entries[i].reading.temperature, entries[i].reading.humidity, entries[i].state);
    }
}

int main() {
    test_full_cycle_integration();
    printf("\n--- All integration tests passed successfully! ---\n");
    return 0;
}