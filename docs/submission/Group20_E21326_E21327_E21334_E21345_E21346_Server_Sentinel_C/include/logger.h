#ifndef LOGGER_H
#define LOGGER_H

#include "common.h"

// Represents a single entry in the system log.
typedef struct {
    SensorReading reading;    // Temperature and humidity values
    time_t timestamp;         // When the reading was recorded
    SystemState state;        // System state at time of reading
} LogEntry;

// A circular buffer to store recent log entries.
typedef struct {
    LogEntry entries[LOG_SIZE]; // Fixed array of 120 entries
    int head;                  // Index of oldest entry
    int tail;                  // Index of newest entry
    int count;                 // Number of entries currently stored
} LogBuffer;

// Function prototypes
void initialize_logger(LogBuffer* buffer);
void log_reading(LogBuffer* buffer, SensorReading reading, SystemState state);
int get_log_entries(const LogBuffer* buffer, LogEntry* out_entries, int max_entries);
int get_latest_entries(const LogBuffer* buffer, LogEntry* out_entries, int num_entries);

#endif // LOGGER_H