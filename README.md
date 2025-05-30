# esp32-gps-simulator# ESP32 GPS Simulator

This project simulates an ESP32 device sending dummy GPS, battery, and timestamp data to a Node-RED dashboard.

## Features

- Generates random latitude, longitude, battery %, and timestamp
- Sends data every 1 hour (configurable)
- View data on Node-RED dashboard
- Download CSV of all data

## How to Run Http

1. Clone the repo
2. Open `.ino` in Arduino IDE or VS Code and change const char* serverUrl with your_ip:1880/gpsdata
3. Run Node-RED locally, in command prompt run:
4. npm install -g --unsafe-perm node-red
5. node-red
6. Access editor at `http://<your_ip>:1880`
7. Import flow by copying /import/import.txt and using import function in editor top-right hamburger menu > import 
8. In manage palette in hamburger menu, install node-red-contrib-uibuilder, node-red-dashboard and node-red-node-ui-table
9. Change path to download csv in download to CSV function the path msg.filename = "C:\\Users\\micky\\Downloads\\gps_data.csv";
10. alternatively, it is possible to test using postman
11. POST http://*your_ip_here*:1880/gpsdata
12. In body raw JSON add { "timestamp": "2025-05-28 24:41:00","lat": 16.346,"lon": 70.391,"battery": 58}
13. OR can use esp32 simulator like wokwi to run the esp32_gps_simulator.ino 
14. Access dashboard at `http://<ypur_ip>:1880/ui`

## How to Run Mqtt

1. Clone the repo
2. Open `.ino` in Arduino IDE or VS Code
3. Run Node-RED locally, in command prompt run:
4. npm install -g --unsafe-perm node-red
5. node-red
6. Install mosquitto from mosquitto.org
7. Install MQTTX from `https://mqttx.app/`
8. Open MQTTX and click on connect
9. Access editor at `http://<ypur_ip>:1880/`
10. Import flow by copying /import/import.txt and using import function in editor top-right hamburger menu > import 
11. In manage palette in hamburger menu, install node-red-contrib-uibuilder, node-red-dashboard, node-red-node-ui-table and node-red-contrib-web-worldmap
12. Change path to download csv in download to CSV function the path msg.filename = "C:\\Users\\micky\\Downloads\\gps_data.csv";
13. alternatively, it is possible to test using postman
14. POST http://*your_ip_here*:1880/gpsdata
15. In body raw JSON add { "timestamp": "2025-05-28 24:41:00","lat": 16.346,"lon": 70.391,"battery": 58}
16. OR can use esp32 simulator like wokwi to run the esp32_gps_simulator.ino 
17. Access dashboard at `http://<ypur_ip>:1880/ui`
18. Access Map at `http://<ypur_ip>:1880/worldmap`


## License

MIT