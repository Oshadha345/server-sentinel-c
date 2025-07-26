#include "../include/main_controller.h"
#include "../include/smart_data.h"
#include <stdio.h>
#include <unistd.h>

//------------ FIX BUTTON TEST FUNCTION ------------
// This function tests if our fix button actually works when things get too hot!
// We make the system overheat on purpose, then click fix to cool it down
void test_fix_button_logic() {
    printf("=== Testing Fix Button Logic ===\n");
    
    //------------ SYSTEM INITIALIZATION ------------
    // Start up our controller - this is like turning on the computer
    Controller controller;
    initialize_system(&controller);
    
    // Show what the system looks like when we first start it
    printf("1. Initial state:\n");
    printf("   Temperature: %.1f°C\n", controller.status.last_reading.temperature);
    printf("   Generator state: %d (STABLE)\n", controller.data_generator.state);
    
    //------------ HEATING UP SECTION ------------
    //------------ HEATING UP SECTION ------------
    // First heat up the system to create a situation that needs fixing
    printf("\n2. Heating up system to create overheating condition...\n");
    set_generator_state(&controller.data_generator, HEATING_UP);
    
    //------------ TEMPERATURE INCREASE LOOP ------------
    // Heat up for several cycles to reach caution/danger level - like turning up the thermostat!
    for (int i = 0; i < 15; i++) {
        SensorReading reading = generate_reading(&controller.data_generator);
        controller.status.last_reading = reading;
        
        // Print temperature every 5 cycles so we can see whats happening
        if (i % 5 == 0) {
            printf("   Heating cycle %d: %.1f°C\n", i+1, reading.temperature);
        }
    }
    
    // Show how hot we got - should be pretty toasty by now!
    printf("   Final heated temperature: %.1f°C\n", controller.status.last_reading.temperature);
    printf("   Generator state: %d (HEATING_UP)\n", controller.data_generator.state);
    
    //------------ FIX BUTTON TESTING ------------
    // Now test the fix button - this is the important part!
    printf("\n3. Testing fix button click (should start cooling)...\n");
    UserCommand fix_cmd = {CMD_FIX, "fix_test"};
    process_command(&controller, fix_cmd);
    printf("   Generator state after fix command: %d (should be %d for COOLING_DOWN)\n", 
           controller.data_generator.state, COOLING_DOWN);
    
    //------------ COOLING EFFECT VERIFICATION ------------
    // Generate readings to see cooling effect - temperature should go down now!
    printf("\n4. Generating readings to test cooling effect:\n");
    for (int i = 0; i < 20; i++) {
        SensorReading reading = generate_reading(&controller.data_generator);
        controller.status.last_reading = reading;
        
        // Print temperature every 3 cycles to see the cooling progress
        if (i % 3 == 0) {
            printf("   Cooling cycle %d: %.1f°C (should be decreasing)\n", i+1, reading.temperature);
        }
        
        // Check if auto-stabilized (cooling stopped when temperature is good again)
        if (controller.data_generator.state == STABLE) {
            printf("   ✓ Auto-stabilized at: %.1f°C\n", reading.temperature);
            break;
        }
        
        usleep(50000); // 0.05 seconds (tiny pause so we can see changes)
    }
    
    //------------ FINAL RESULTS CHECK ------------
    // Show what happened after we tried to fix everything
    printf("\n5. Final state after fix:\n");
    printf("   Temperature: %.1f°C\n", controller.status.last_reading.temperature);
    printf("   Generator state: %d (should be %d for STABLE)\n", 
           controller.data_generator.state, STABLE);
    
    printf("\n=== Test Complete ===\n");
}

//------------ INTERMITTENT FAILURE TEST FUNCTION ------------
// This tests fixing random problems that come and go (like flickering lights)
void test_intermittent_fix() {
    printf("\n=== Testing Intermittent Failure Fix ===\n");
    
    //------------ SETUP ANOTHER CONTROLLER ------------
    // Create a fresh controller for this test
    Controller controller;
    initialize_system(&controller);
    
    //------------ START RANDOM PROBLEMS ------------
    // Make the system have unpredictable issues
    printf("1. Starting intermittent failure...\n");
    set_generator_state(&controller.data_generator, INTERMITTENT_FAILURE);
    
    //------------ WATCH THE CHAOS ------------
    // Let it run for a few cycles to see weird behavior
    for (int i = 0; i < 10; i++) {
        SensorReading reading = generate_reading(&controller.data_generator);
        controller.status.last_reading = reading;
        
        // Show whats happening every few cycles
        if (i % 3 == 0) {
            printf("   Intermittent cycle %d: %.1f°C\n", i+1, reading.temperature);
        }
    }
    
    printf("   Temperature before fix: %.1f°C\n", controller.status.last_reading.temperature);
    
    //------------ TRY TO FIX THE RANDOM PROBLEMS ------------
    // Apply fix to see if we can stop the weirdness
    printf("\n2. Applying fix to intermittent failure...\n");
    UserCommand fix_cmd = {CMD_FIX, "fix_intermittent"};
    process_command(&controller, fix_cmd);
    
    //------------ CHECK IF FIX WORKED ------------
    // See if the random problems stopped
    for (int i = 0; i < 10; i++) {
        SensorReading reading = generate_reading(&controller.data_generator);
        controller.status.last_reading = reading;
        
        // Show post-fix readings
        if (i % 3 == 0) {
            printf("   Post-fix cycle %d: %.1f°C\n", i+1, reading.temperature);
        }
        
        // Hooray! If system becomes stable, our fix worked!
        if (controller.data_generator.state == STABLE) {
            printf("   ✓ Intermittent failure fixed at: %.1f°C\n", reading.temperature);
            break;
        }
    }
    
    printf("\n=== Intermittent Test Complete ===\n");
}

//------------ MAIN TEST RUNNER ------------
// This is where our testing program starts - runs all the tests!
int main() {
    printf("Fix Button Debug Test\n");
    printf("====================\n\n");
    
    // Run the heating/cooling fix test first
    test_fix_button_logic();
    
    // Then run the intermittent failure test
    test_intermittent_fix();
    
    return 0; // All done - tests finished!
}
