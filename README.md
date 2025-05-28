# esp32-gps-simulator# ESP32 GPS Simulator

This project simulates an ESP32 device sending dummy GPS, battery, and timestamp data to a Node-RED dashboard.

## Features

- Generates random latitude, longitude, battery %, and timestamp
- Sends data every 1 hour (configurable)
- View data on Node-RED dashboard
- Download CSV of all data

## How to Run

1. Clone the repo
2. Open `.ino` in Arduino IDE or VS Code
3. Run Node-RED locally, in command prompt run:
4. npm install -g --unsafe-perm node-red
5. node-red
6. Access dashboard at `http://localhost:1880/ui`
## License

MIT