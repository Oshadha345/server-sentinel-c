#include "../include/main_controller.h"
#include "../include/smart_data.h"
#include <stdio.h>
#include <unistd.h>

// Test specifically for fix button functionality
void test_fix_button_logic() {
    printf("=== Testing Fix Button Logic ===\n");
    
    // Initialize controller
    Controller controller;
    initialize_system(&controller);
    
    printf("1. Initial state:\n");
    printf("   Temperature: %.1f°C\n", controller.status.last_reading.temperature);
    printf("   Generator state: %d (STABLE)\n", controller.data_generator.state);
    
    // First heat up the system to create a situation that needs fixing
    printf("\n2. Heating up system to create overheating condition...\n");
    set_generator_state(&controller.data_generator, HEATING_UP);
    
    // Heat up for several cycles to reach caution/danger level
    for (int i = 0; i < 15; i++) {
        SensorReading reading = generate_reading(&controller.data_generator);
        controller.status.last_reading = reading;
        
        if (i % 5 == 0) {
            printf("   Heating cycle %d: %.1f°C\n", i+1, reading.temperature);
        }
    }
    
    printf("   Final heated temperature: %.1f°C\n", controller.status.last_reading.temperature);
    printf("   Generator state: %d (HEATING_UP)\n", controller.data_generator.state);
    
    // Now test the fix button
    printf("\n3. Testing fix button click (should start cooling)...\n");
    UserCommand fix_cmd = {CMD_FIX, "fix_test"};
    process_command(&controller, fix_cmd);
    printf("   Generator state after fix command: %d (should be %d for COOLING_DOWN)\n", 
           controller.data_generator.state, COOLING_DOWN);
    
    // Generate readings to see cooling effect
    printf("\n4. Generating readings to test cooling effect:\n");
    for (int i = 0; i < 20; i++) {
        SensorReading reading = generate_reading(&controller.data_generator);
        controller.status.last_reading = reading;
        
        if (i % 3 == 0) {
            printf("   Cooling cycle %d: %.1f°C (should be decreasing)\n", i+1, reading.temperature);
        }
        
        // Check if auto-stabilized
        if (controller.data_generator.state == STABLE) {
            printf("   ✓ Auto-stabilized at: %.1f°C\n", reading.temperature);
            break;
        }
        
        usleep(50000); // 0.05 seconds
    }
    
    printf("\n5. Final state after fix:\n");
    printf("   Temperature: %.1f°C\n", controller.status.last_reading.temperature);
    printf("   Generator state: %d (should be %d for STABLE)\n", 
           controller.data_generator.state, STABLE);
    
    printf("\n=== Test Complete ===\n");
}

// Test intermittent failure fix
void test_intermittent_fix() {
    printf("\n=== Testing Intermittent Failure Fix ===\n");
    
    Controller controller;
    initialize_system(&controller);
    
    // Start intermittent failure
    printf("1. Starting intermittent failure...\n");
    set_generator_state(&controller.data_generator, INTERMITTENT_FAILURE);
    
    // Let it run for a few cycles
    for (int i = 0; i < 10; i++) {
        SensorReading reading = generate_reading(&controller.data_generator);
        controller.status.last_reading = reading;
        
        if (i % 3 == 0) {
            printf("   Intermittent cycle %d: %.1f°C\n", i+1, reading.temperature);
        }
    }
    
    printf("   Temperature before fix: %.1f°C\n", controller.status.last_reading.temperature);
    
    // Apply fix
    printf("\n2. Applying fix to intermittent failure...\n");
    UserCommand fix_cmd = {CMD_FIX, "fix_intermittent"};
    process_command(&controller, fix_cmd);
    
    // Check result
    for (int i = 0; i < 10; i++) {
        SensorReading reading = generate_reading(&controller.data_generator);
        controller.status.last_reading = reading;
        
        if (i % 3 == 0) {
            printf("   Post-fix cycle %d: %.1f°C\n", i+1, reading.temperature);
        }
        
        if (controller.data_generator.state == STABLE) {
            printf("   ✓ Intermittent failure fixed at: %.1f°C\n", reading.temperature);
            break;
        }
    }
    
    printf("\n=== Intermittent Test Complete ===\n");
}

int main() {
    printf("Fix Button Debug Test\n");
    printf("====================\n\n");
    
    test_fix_button_logic();
    test_intermittent_fix();
    
    return 0;
}
