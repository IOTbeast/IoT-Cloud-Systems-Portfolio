# 🌐 IoT & Smart Systems Portfolio
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Profile](https://img.shields.io/badge/Developer-Portfolio-blue)](https://github.com/IOTbeast)

Welcome to my comprehensive collection of **IoT (Internet of Things)** and **Embedded Systems** solutions. This repository serves as a professional showcase of my ability to design, simulate, and deploy smart hardware systems using **ESP32**, **Arduino**, and **MicroPython**.

---

## 🚀 Featured Projects
Each folder in this repository contains the source code, circuit diagrams, and full documentation for a specific real-world problem.

| Project Name | Technology Stack | Core Functionality | Quick Link |
| :--- | :--- | :--- | :--- |
| **Smart Campus Waste Management** | ESP32, Ultrasonic, Blynk | Real-time bin level tracking with cloud alerts. | [Explore](Smart-Campus-Waste-Management) |
| **Smart Guest Attendance** | ESP32, RFID, LCD | Automated logging system via Blynk IoT. | [Explore](Smart-Guest-Attendance) |
| **Tuberculosis Wearable** | ESP32, MPU6050, MicroPython | Health tech monitoring for respiratory vitals. | [Explore](./Tuberculosis-Wearable) |
| **Public Toilet Usage Tracker** | Arduino, IR, Usage Analytics | Smart city data tracking for facility management. | [Explore](./Public-Toilet-Tracker) |
| **Weather & Air Pollution** | ESP32, MQ2, DHT22 | Environmental monitoring & air quality indexing. | [Explore](./Air-Pollution-Monitoring) |
| **Smart Agriculture System** | ESP32, Soil Moisture, LDR | Intelligent irrigation and crop environment control. | [Explore](./Smart-Agriculture) |

---

## 🛠️ Technical Expertise
### **Hardware & Microcontrollers**
* **Microcontrollers:** ESP32 (NodeMCU), Arduino Uno/Nano/Mega.
* **Connectivity:** Wi-Fi, Bluetooth (BLE), Blynk IoT, ThinkSpeak, MQTT.
* **Protocols:** I2C, SPI, UART (Optimized for hardware stability).
* **Sensor Integration:** IMU (MPU6050), Ultrasonic, DHT22, MQ-Series Gas Sensors.

### **Software & Tools**
* **Languages:** C++, MicroPython.
* **Simulation:** Wokwi (Hardware-accurate browser simulations).
* **Tools:** Arduino IDE, Thonny, Git/GitHub.

---

## 🔌 Hardware Stability Standards
All projects in this repository adhere to professional wiring standards:
* **I2C Bus Integrity:** Use of $4.7\text{ k}\Omega$ pull-up resistors for multi-device stability (SSD1306 + MPU6050).
* **Power Management:** Decoupling capacitors and stable voltage regulation for ESP32 Wi-Fi bursts.

---

## 📂 Repository Structure
```plaintext
├── [Project-Name]/
│   ├── [Project-File].ino/.py   <-- Clean, commented source code
│   ├── README.md                <-- Project-specific manual
│   └── images/                  <-- High-res circuit diagrams/schematics
├── .gitignore                   <-- Clean build filter
└── README.md                    <-- Master Index (This file)
