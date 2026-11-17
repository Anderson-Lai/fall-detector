# Fall Detector Monorepo

This monorepo contains all the code for a fall detector. The backend (`./backend`) is written in Go, and the firmware for the microcontroller (`./firmware`) is written in C++. The microcontroller is an ESP32-C3 SuperMini.

Documentation is available at [./docs](./docs). Each component of the project (the backend and the firmware) *may* each have their own `README.md` for less pertinent notes and documentation. 

For proper functionality, ensure there is a copy of `.env` in `./backend` and a copy of `credentials.hpp` in `./firmware/include` with appropriate entries.

## Firmware Features

- [x] Implement fall detection
  - [x] Read accelerometer and caculate acceleration in g's and m/s^2
  - [ ] Possible estimation of the **position** of the sensor via approximating the second-order differential equation
- [x] Sending POST request on fall detection
  - [x] Connect to WiFi (phone hotspot)
  - [x] Trust TLS certificate
- [ ] Implement button functionality
  - [ ] SOS button when fall is **not** detected
  - [ ] Canceling SOS when fall **is** detected
    -  [ ] Either cancel on server side (delaying notifications) or client side (RTOS + semaphores)
- [ ] Implement buzzer functionality
  - [ ] Activate buzzer on fall detection

## Backend Features

- [x] Implement endpoint to post alert requests
  - [x] Implement basic functionality without authentication
  - [x] Implement alert logging
  - [x] Authenticate request using an API key + device ID
  - [x] Generate API keys + device ID using a provisioning secret
    - [x] Rate limit endpoint
- [ ] Implement automatic notifications
  - [x] Email notifications
  - [ ] SMS notifications
- [ ] Implement endpoint for CCCARE staff to get all logs
  - [ ] Proper authentication with username + password

## Frontend Features
- [ ] App to easily upload wifi credentials onto ESP32
- [ ] Website for CCCARE staff to get all longs