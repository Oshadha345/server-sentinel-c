#include "../include/logger.h"
#include <string.h>
#include <time.h>

// Initializes the log buffer to an empty state.
void initialize_logger(LogBuffer* buffer) {
    if (!buffer) return;

    buffer->head = 0;
    buffer->tail = 0;
    buffer->count = 0;
    // Zero out all entries to prevent garbage data
    memset(buffer->entries, 0, sizeof(buffer->entries));
}

// Adds a new sensor reading to the log buffer.
void log_reading(LogBuffer* buffer, SensorReading reading, SystemState state) {
    if (!buffer) return;

    // Create a new log entry
    LogEntry new_entry;
    new_entry.reading = reading;
    new_entry.state = state;
    new_entry.timestamp = time(NULL);

    // If the buffer is full, advance the head to overwrite the oldest entry
    if (buffer->count == LOG_SIZE) {
        buffer->head = (buffer->head + 1) % LOG_SIZE;
    } else {
        buffer->count++;
    }

    // Add the new entry at the tail
    buffer->entries[buffer->tail] = new_entry;
    buffer->tail = (buffer->tail + 1) % LOG_SIZE;
}

// Retrieves all log entries from oldest to newest.
int get_log_entries(const LogBuffer* buffer, LogEntry* out_entries, int max_entries) {
    if (!buffer || !out_entries || max_entries <= 0) {
        return 0;
    }

    int entries_to_copy = (buffer->count < max_entries) ? buffer->count : max_entries;
    int current = buffer->head;

    for (int i = 0; i < entries_to_copy; i++) {
        out_entries[i] = buffer->entries[current];
        current = (current + 1) % LOG_SIZE;
    }

    return entries_to_copy;
}

// Retrieves the most recent log entries, from newest to oldest.
int get_latest_entries(const LogBuffer* buffer, LogEntry* out_entries, int num_entries) {
    if (!buffer || !out_entries || num_entries <= 0) {
        return 0;
    }

    int entries_to_copy = (buffer->count < num_entries) ? buffer->count : num_entries;
    int current = (buffer->tail - 1 + LOG_SIZE) % LOG_SIZE;

    for (int i = 0; i < entries_to_copy; i++) {
        out_entries[i] = buffer->entries[current];
        current = (current - 1 + LOG_SIZE) % LOG_SIZE;
    }

    return entries_to_copy;
}


