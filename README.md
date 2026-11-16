# ECE198 Medical Device Monorepo

This monorepo contains all the code for group 26's ECE198 medical device project. The backend (`./backend`) is written in Go, and the firmware for the microcontroller (`./firmware`) is written in C++. The microcontroller is an ESP32-C3 SuperMini.

Documentation is available at [./docs](./docs). For proper functionality, ensure there is a copy of `.env` in `./backend` and a copy of `credentials.hpp` in `./firmware/include` with appropriate entries.

## Firmware Features

- [x] Implement fall detection
  - [x] Read accelerometer and caculate acceleration in g's and m/s^2
  - [ ] Possible estimation of the **position** of the sensor via approximating the second-order differential equation
- [ ] Sending POST request on fall detection
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