# flask-socketio-iot

ESP32 Real-Time Motion Detection System (IoT Project)
## Overview

This project is a real-time IoT Motion Detection System using ESP32, PIR sensor, Flask, and Socket.IO. The ESP32 detects motion and sends data to a Flask server via HTTP. The server stores the data and instantly pushes updates to a web dashboard using WebSockets (Socket.IO), enabling real-time monitoring without page refresh.

## Features

Real-time motion detection using PIR sensor
ESP32 WiFi communication
HTTP data transmission to server
Flask backend with database storage
Real-time updates using Socket.IO (no polling)
Live dashboard with instant status change
Efficient data sending (only on state change)

## Technologies Used

ESP32 (Arduino IDE)
PIR Motion Sensor
WiFi + HTTPClient
Python
Flask
Flask-SQLAlchemy
Flask-SocketIO
SQLite
HTML + JavaScript
WebSockets (Socket.IO)

## Project Structure

esp32-realtime-motion-dashboard/
│
├── esp32/
│ └── main.ino
│
├── server/
│ └── app.py
│ └── iot.db
│
├── templates/
│ └── index.html
│
└── README.md

## How to Run

install python (VS Code)

Install required libraries:
pip install flask flask_sqlalchemy flask_socketio

Upload code to ESP32

Update server IP address in ESP32 code

Run Flask server:
python app.py

Open browser:
http://localhost:5001

## How It Works

ESP32 reads PIR sensor value:
1 → Motion detected
0 → No motion

ESP32 sends data to Flask server only when state changes

Flask server:
Receives data via POST request
Stores data in SQLite database

Real-time system:
Server emits event using Socket.IO
Frontend listens to event

Dashboard:
Updates instantly without refresh

##  API Endpoints

POST /add → Receive motion data from ESP32
GET / → Dashboard UI

## Future Improvements

Add alert system (Telegram / Email)
Add camera integration for security system
Deploy on cloud server
Add multi-sensor support
Add user authentication
Add historical data graphs

## Author
Harsha G
Learning Python | Embedded Systems | IoT
