/*
Defines common macros and utility functions for the project.
*/

#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <time.h>

// system constants


// temerature  thresholds
#define TEMP_CAUTION_THRESHOLD 45.0f
#define TEMP_DANGER_THRESHOLD  60.0f // temperature thresholds in Celsius : this is the main threshold for the system

// humidity thresholds
#define HUMID_LOW_CAUTION      30.0f
#define HUMID_HIGH_CAUTION     70.0f
#define HUMID_LOW_DANGER       20.0f
#define HUMID_HIGH_DANGER      80.0f

// critical shutdown time in seconds
#define CRITICAL_SHUTDOWN_SECONDS 20

// log list size
#define LOG_SIZE 120

// sytem status

typedef enum {
    NORMAL, // all parameters within safe range
    CAUTION, // at least one parameter is in caution range
    DANGER, // at least one parameter is in danger range
    SHUTDOWN // critical temperature sustained for required period
} SystemState;

// single sensor reading structure

typedef struct {
    float temperature;
    float humidity;
} SensorReading;


#endif // COMMON_H