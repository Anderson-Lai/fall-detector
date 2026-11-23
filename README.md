# Fall Detector Monorepo

This monorepo contains all the code for a fall detector. The backend (`./backend`) is written in Go, and the firmware for the microcontroller (`./firmware`) is written in C++. The microcontroller is an ESP32-C3 SuperMini.

Documentation is available at [./docs](./docs). The firmware component of the projection ([./firmware](./firmware/)) has its own `README.md` for information pertinent to the specific board used for the project and other firmware concerns.

For proper functionality, ensure there is a copy of `.env` in `./backend` and a copy of `credentials.hpp` in `./firmware/include` with appropriate entries.

## Firmware Features

- [x] Implement fall detection
  - [x] Read accelerometer and caculate acceleration in g's and m/s^2
  - [ ] Possible estimation of the **position** of the sensor via approximating the second-order differential equation
- [x] Sending POST request on fall detection
  - [x] Connect to WiFi (phone hotspot)
  - [x] Trust TLS certificate
- [x] Implement button functionality
  - [x] SOS button when fall is **not** detected
  - [x] Canceling SOS when fall **is** detected
    -  [x] Either cancel on server side (delaying notifications) or client side (RTOS + semaphores)
- [x] Implement buzzer functionality
  - [x] Activate buzzer when waiting to send an alert

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
- [ ] Website to easily upload wifi credentials, API key, and device ID onto ESP32 via bluetooth
- [ ] Website for CCCARE staff to get all logs and device IDs