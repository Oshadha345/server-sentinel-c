#include "../include/main_controller.h"
#include "../include/smart_data.h"
#include <stdio.h>
#include <unistd.h>

// Test specifically for heating button functionality
void test_heating_button_logic() {
    printf("=== Testing Heating Button Logic ===\n");
    
    // Initialize controller
    Controller controller;
    initialize_system(&controller);
    
    printf("1. Initial state:\n");
    printf("   Temperature: %.1f°C\n", controller.status.last_reading.temperature);
    printf("   Generator state: %d\n", controller.data_generator.state);
    
    // Simulate heating button click
    printf("\n2. Simulating heating button click...\n");
    set_generator_state(&controller.data_generator, HEATING_UP);
    printf("   Generator state after heating command: %d (should be %d for HEATING_UP)\n", 
           controller.data_generator.state, HEATING_UP);
    
    // Generate some readings to see if temperature increases
    printf("\n3. Generating readings to test heating effect:\n");
    for (int i = 0; i < 10; i++) {
        SensorReading reading = generate_reading(&controller.data_generator);
        controller.status.last_reading = reading;
        
        printf("   Reading %d: %.1f°C (should be increasing)\n", i+1, reading.temperature);
        
        // Small delay to simulate real conditions
        usleep(100000); // 0.1 seconds
    }
    
    // Test the bounds
    printf("\n4. Testing heating bounds (should reach 90-110°C range):\n");
    for (int i = 0; i < 50; i++) {
        SensorReading reading = generate_reading(&controller.data_generator);
        controller.status.last_reading = reading;
        
        if (i % 10 == 0) {
            printf("   Reading %d: %.1f°C\n", i+1, reading.temperature);
        }
        
        // Check if we reached expected heating range
        if (reading.temperature >= 90.0f) {
            printf("   ✓ Reached heating range: %.1f°C\n", reading.temperature);
            break;
        }
        
        usleep(50000); // 0.05 seconds
    }
    
    printf("\n5. Final temperature: %.1f°C\n", controller.status.last_reading.temperature);
    
    // Test process_command function specifically
    printf("\n6. Testing process_command with heating scenario:\n");
    UserCommand heating_cmd = {CMD_FAIL_COOLING, "heating_test"};
    process_command(&controller, heating_cmd);
    printf("   Generator state after process_command: %d\n", controller.data_generator.state);
    
    printf("\n=== Test Complete ===\n");
}

int main() {
    printf("Heating Button Debug Test\n");
    printf("========================\n\n");
    
    test_heating_button_logic();
    
    return 0;
}
