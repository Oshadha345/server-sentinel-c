# Server-Sentinel-C

A C-based simulation of a mission-critical environmental controller for data centers, featuring a state-driven design, escalating alerts, and an emergency shutdown protocol based on ASHRAE standards.

## Project Overview
This project simulates an embedded system for monitoring temperature and humidity in a data center environment with the following features:
- Temperature and humidity monitoring with threshold-based alerts
- State-driven design (NORMAL, CAUTION, DANGER, SHUTDOWN)
- Circular buffer logging system (120 entries)
- Simulated environmental scenarios

## Key Parameters
- Caution Temperature: > 45°C
- Critical Temperature: > 60°C
- Caution Humidity: > 70% or < 30%
- Critical Humidity: > 80% or < 20%
- Time to Shutdown: If Critical Temperature is sustained for 20 simulated seconds

## Repository Structure
- `/docs`: Project documentation and architecture
- `/include`: Header files
- `/src`: Source code files
- `/bin`: Compiled binaries

## Building and Running
(To be added during Phase 2)
