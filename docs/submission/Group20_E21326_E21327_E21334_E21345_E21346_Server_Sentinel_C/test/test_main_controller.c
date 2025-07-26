#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/main_controller.h"

void test_system_initialization() {
    printf("=== Testing System Initialization ===\n");
    
    Controller controller;
    initialize_system(&controller);
    
    // Verify initial state
    assert(controller.status.state == NORMAL);
    assert(controller.status.running == true);
    assert(controller.status.critical_time == 0);
    assert(controller.status.last_reading.temperature == 22.0f);
    assert(controller.status.last_reading.humidity == 50.0f);
    
    printf("✅ System initialization test passed\n\n");
}

void test_command_parsing() {
    printf("=== Testing Command Parsing ===\n");
    
    // Test various command inputs
    UserCommand cmd1 = parse_user_input("fail_cooling");
    assert(cmd1.type == CMD_FAIL_COOLING);
    
    UserCommand cmd2 = parse_user_input("FIX");
    assert(cmd2.type == CMD_FIX);
    
    UserCommand cmd3 = parse_user_input("help");
    assert(cmd3.type == CMD_HELP);
    
    UserCommand cmd4 = parse_user_input("exit");
    assert(cmd4.type == CMD_EXIT);
    
    UserCommand cmd5 = parse_user_input("unknown_command");
    assert(cmd5.type == CMD_NONE);
    
    printf("✅ Command parsing test passed\n\n");
}

void test_system_state_updates() {
    printf("=== Testing System State Updates ===\n");
    
    Controller controller;
    initialize_system(&controller);
    
    // Test normal reading
    SensorReading normal_reading = {25.0f, 50.0f};
    update_system_state(&controller, normal_reading);
    assert(controller.status.state == NORMAL);
    assert(controller.status.critical_time == 0);
    
    // Test caution reading
    SensorReading caution_reading = {50.0f, 50.0f};
    update_system_state(&controller, caution_reading);
    assert(controller.status.state == CAUTION);
    
    // Test danger reading
    SensorReading danger_reading = {65.0f, 50.0f};
    update_system_state(&controller, danger_reading);
    assert(controller.status.state == DANGER);
    assert(controller.critical_timer.is_active == true);
    
    printf("✅ System state update test passed\n\n");
}

void test_command_processing() {
    printf("=== Testing Command Processing ===\n");
    
    Controller controller;
    initialize_system(&controller);
    
    // Test fail_cooling command
    UserCommand fail_cmd = {CMD_FAIL_COOLING, "fail_cooling"};
    process_command(&controller, fail_cmd);
    // Should change data generator state to HEATING_UP
    
    // Test fix command
    UserCommand fix_cmd = {CMD_FIX, "fix"};
    process_command(&controller, fix_cmd);
    // Should change data generator state to COOLING_DOWN
    
    // Test exit command
    UserCommand exit_cmd = {CMD_EXIT, "exit"};
    process_command(&controller, exit_cmd);
    assert(controller.status.running == false);
    
    printf("✅ Command processing test passed\n\n");
}

void test_shutdown_condition() {
    printf("=== Testing Shutdown Condition ===\n");
    
    Controller controller;
    initialize_system(&controller);
    
    // Simulate critical temperature for extended period
    SensorReading critical_reading = {70.0f, 50.0f};
    
    for (int i = 0; i < CRITICAL_SHUTDOWN_SECONDS + 1; i++) {
        update_system_state(&controller, critical_reading);
    }
    
    // Should trigger shutdown
    assert(controller.status.state == SHUTDOWN);
    
    printf("✅ Shutdown condition test passed\n\n");
}

void test_integrated_scenario() {
    printf("=== Testing Integrated Scenario ===\n");
    
    Controller controller;
    initialize_system(&controller);
    
    // Simulate a cooling failure scenario
    set_generator_state(&controller.data_generator, HEATING_UP);
    
    bool reached_danger = false;
    int simulation_cycles = 30;
    
    for (int i = 0; i < simulation_cycles; i++) {
        // Generate reading
        SensorReading reading = generate_reading(&controller.data_generator);
        
        // Update system state
        update_system_state(&controller, reading);
        
        // Log the reading
        log_reading(&controller.log_buffer, reading, controller.status.state);
        
        // Check if we reached danger state
        if (controller.status.state == DANGER && !reached_danger) {
            reached_danger = true;
            printf("🔴 DANGER state reached at cycle %d\n", i + 1);
        }
        
        // Simulate fix after 5 cycles in danger
        if (reached_danger && controller.status.critical_time >= 5) {
            set_generator_state(&controller.data_generator, COOLING_DOWN);
            printf("🔧 Fix applied at cycle %d\n", i + 1);
        }
        
        // Break if system shuts down
        if (controller.status.state == SHUTDOWN) {
            printf("💀 System shutdown at cycle %d\n", i + 1);
            break;
        }
    }
    
    // Verify log contains entries
    assert(controller.log_buffer.count > 0);
    
    printf("✅ Integrated scenario test completed\n\n");
}

int main() {
    printf("🧪 Running Main Controller Tests...\n");
    printf("====================================\n\n");
    
    test_system_initialization();
    test_command_parsing();
    test_system_state_updates();
    test_command_processing();
    test_shutdown_condition();
    test_integrated_scenario();
    
    printf("🎉 All main controller tests passed successfully!\n");
    printf("System is ready for full integration.\n");
    
    return 0;
}
