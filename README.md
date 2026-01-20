An Arduino-based temperature and humidity monitoring project using a DHT11 sensor and an Ethernet Shield.
The system provides a real-time web interface and triggers a buzzer alarm when the temperature changes by ±1°C compared to the previous reading.

🔧 Hardware Requirements

Arduino Uno / Mega

Ethernet Shield (W5100 / W5500)

DHT11 Temperature & Humidity Sensor

Active Buzzer

Jumper Wires

🔌 Pin Configuration
Component	Arduino Pin
DHT11 Data	D2
Buzzer	D7
Ethernet Shield	SPI (Pins 10–13)
⚙️ Features

Real-time temperature and humidity measurement

Built-in web server (HTTP)

Auto-refresh web page (every 2 seconds)

Alarm triggered when temperature change ≥ 1°C

Visual alarm status on web interface

Audible buzzer alert

🌐 Web Interface

The web page displays:

Temperature (°C)

Humidity (%)

Alarm Status (NORMAL / ALARM ACTIVE)

Each value is shown inside a bordered box for clarity.

🚀 How to Run

Open Arduino IDE

Install required libraries:

DHT sensor library

Ethernet

Connect the hardware as listed above

Upload the code to Arduino

Open Serial Monitor to see the IP address

Open your browser and visit:

http://192.168.1.177

🧠 Logic Summary

First valid reading initializes the system

Each new temperature is compared with the previous measurement

If the difference ≥ 1°C:

Buzzer turns ON

Alarm status becomes ALARM ACTIVE

Otherwise:

Buzzer turns OFF

Alarm status remains NORMAL



📜 License

This project is released for educational and personal use.
Feel free to modify and enhance it.

⭐ Repository Description

Arduino Ethernet-based temperature and humidity monitoring system with DHT11, buzzer alarm, and auto-refresh web interface.
