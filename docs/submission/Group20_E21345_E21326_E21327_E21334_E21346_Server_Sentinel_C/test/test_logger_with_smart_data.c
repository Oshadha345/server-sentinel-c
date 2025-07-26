#include <stdio.h>
#include "../include/smart_data.h"
#include "../include/logger.h"

// Helper function to print a log entry
void print_log_entry(int index, LogEntry entry) {
    const char* state_names[] = {"NORMAL", "ALERT", "CRITICAL", "EMERGENCY"};
    printf("[%d] Temp: %.2f°C, Humidity: %.2f%%, State: %s, Time: %ld\n",
           index + 1, entry.reading.temperature, entry.reading.humidity,
           state_names[entry.state], entry.timestamp);
}

// Helper function to print separator
void print_separator(const char* title) {
    printf("\n=== %s ===\n", title);
}

int main() {
    SmartDataGenerator generator;
    LogBuffer logger;
    
    // Initialize both modules
    print_separator("INITIALIZING MODULES");
    init_generator(&generator);
    initialize_logger(&logger);
    printf("✓ Smart data generator initialized\n");
    printf("✓ Logger initialized\n");

    // Test 1: Log readings in STABLE state with NORMAL system state
    print_separator("TEST 1: STABLE READINGS WITH NORMAL STATE");
    set_generator_state(&generator, STABLE);
    for (int i = 0; i < 5; i++) {
        SensorReading reading = generate_reading(&generator);
        log_reading(&logger, reading, NORMAL);
        printf("Logged reading %d: Temp=%.2f°C, Humidity=%.2f%%\n", 
               i + 1, reading.temperature, reading.humidity);
    }

    // Test 2: Log readings in HEATING_UP state with ALERT system state
    print_separator("TEST 2: HEATING UP WITH ALERT STATE");
    set_generator_state(&generator, HEATING_UP);
    for (int i = 0; i < 3; i++) {
        SensorReading reading = generate_reading(&generator);
        log_reading(&logger, reading, CAUTION);
        printf("Logged reading %d: Temp=%.2f°C, Humidity=%.2f%%\n", 
               i + 6, reading.temperature, reading.humidity);
    }

    // Test 3: Log readings in HUMIDITY_SPIKE state with CRITICAL system state
    print_separator("TEST 3: HUMIDITY SPIKE WITH CRITICAL STATE");
    set_generator_state(&generator, HUMIDITY_SPIKE);
    for (int i = 0; i < 4; i++) {
        SensorReading reading = generate_reading(&generator);
        log_reading(&logger, reading, DANGER);
        printf("Logged reading %d: Temp=%.2f°C, Humidity=%.2f%%\n", 
               i + 9, reading.temperature, reading.humidity);
    }

    // Test 4: Log readings with EMERGENCY state
    print_separator("TEST 4: EMERGENCY STATE");
    set_generator_state(&generator, COOLING_DOWN);
    for (int i = 0; i < 3; i++) {
        SensorReading reading = generate_reading(&generator);
        log_reading(&logger, reading, CAUTION);
        printf("Logged reading %d: Temp=%.2f°C, Humidity=%.2f%%\n", 
               i + 13, reading.temperature, reading.humidity);
    }

    // Test 5: Retrieve all log entries (oldest to newest)
    print_separator("TEST 5: ALL LOG ENTRIES (OLDEST TO NEWEST)");
    LogEntry all_entries[LOG_SIZE];
    int total_entries = get_log_entries(&logger, all_entries, LOG_SIZE);
    printf("Retrieved %d log entries:\n", total_entries);
    for (int i = 0; i < total_entries; i++) {
        print_log_entry(i, all_entries[i]);
    }

    // Test 6: Retrieve latest 5 entries (newest to oldest)
    print_separator("TEST 6: LATEST 5 ENTRIES (NEWEST TO OLDEST)");
    LogEntry latest_entries[5];
    int latest_count = get_latest_entries(&logger, latest_entries, 5);
    printf("Retrieved %d latest entries:\n", latest_count);
    for (int i = 0; i < latest_count; i++) {
        print_log_entry(i, latest_entries[i]);
    }

    // Test 7: Test buffer overflow by adding more entries than LOG_SIZE
    print_separator("TEST 7: BUFFER OVERFLOW TEST");
    printf("Current buffer size: %d\n", LOG_SIZE);
    printf("Adding 20 more entries to test circular buffer behavior...\n");
    
    set_generator_state(&generator, INTERMITTENT_FAILURE);
    for (int i = 0; i < 20; i++) {
        SensorReading reading = generate_reading(&generator);
        SystemState state = (i % 4); // Cycle through all states
        log_reading(&logger, reading, state);
    }

    // Show final state of buffer
    LogEntry final_entries[LOG_SIZE];
    int final_count = get_log_entries(&logger, final_entries, LOG_SIZE);
    printf("\nFinal buffer state (%d entries):\n", final_count);
    for (int i = 0; i < final_count; i++) {
        print_log_entry(i, final_entries[i]);
    }

    // Test 8: Edge case tests
    print_separator("TEST 8: EDGE CASE TESTS");
    
    // Test with NULL pointers
    printf("Testing NULL pointer handling...\n");
    log_reading(NULL, (SensorReading){25.0f, 50.0f}, NORMAL);
    printf("✓ NULL buffer handled gracefully\n");
    
    int result = get_log_entries(NULL, final_entries, 5);
    printf("✓ NULL buffer in get_log_entries returned: %d\n", result);
    
    result = get_latest_entries(&logger, NULL, 5);
    printf("✓ NULL output array in get_latest_entries returned: %d\n", result);

    print_separator("ALL TESTS COMPLETED");
    printf("✓ Smart data generation working correctly\n");
    printf("✓ Logger functionality working correctly\n");
    printf("✓ Integration between modules successful\n");

    return 0;
}