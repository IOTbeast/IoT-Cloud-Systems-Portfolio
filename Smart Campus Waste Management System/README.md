# 🗑️ Smart Campus Waste Management System

## 📖 Overview
This project is an IoT-based solution designed to optimize waste collection on a college campus. Using an **ESP32** and **Ultrasonic sensors**, the system monitors the "fill-level" of trash bins in real-time. When a bin reaches a specific threshold, it triggers an alert via the **Blynk IoT platform**, allowing facility managers to empty bins only when necessary—reducing fuel costs and preventing overflow.

## 🕹️ Live Simulation
You can test the logic and sensor interaction directly in your browser:
[![Run on Wokwi](https://img.shields.io/badge/Wokwi-Simulation-blue?style=for-the-badge&logo=virtualbox&logoColor=white)](https://wokwi.com/projects/464006323508858881)

---

## 🔌 Circuit Diagram & Hardware
The system utilizes an ESP32 for Wi-Fi connectivity and an HC-SR04 sensor to measure the distance from the bin lid to the trash.

![Circuit Diagram](![alt text](![alt text](image.png)))

### Components List
* **Microcontroller:** ESP32 (NodeMCU)
* **Sensor:** HC-SR04 Ultrasonic Sensor (measures bin depth)
* **Indicator:** LED / Buzzer (Local alert for full status)
* **Platform:** Blynk IoT (Mobile/Web Dashboard)
* **Power:** 5V USB or Li-ion Battery

### 🛠️ Hardware Logic
1. The **Ultrasonic Sensor** sends a pulse and measures the time it takes to bounce back.
2. The code converts this time into **distance (cm)**.
3. If the distance is small (e.g., < 10cm), the bin is **Full**.
4. If the distance is large (e.g., > 50cm), the bin is **Empty**.
5. Data is pushed to the Blynk Cloud every 5 seconds.

---

## 💻 Software Setup

### Required Libraries
Ensure you have these libraries installed in your Arduino IDE:
* `BlynkSimpleEsp32.h`
* `WiFi.h` / `WiFiClient.h`
* `HCSR04.h` (or standard pulseIn logic)

### Installation & Configuration
1. Clone this folder to your machine.
2. Open `Smart-Campus-Waste-Management.ino`.
3. Locate the **Blynk Template ID** and **Auth Token** in the code and replace them with your own from the Blynk Developer Console.
4. Update your Wi-Fi credentials:
   ```cpp
   char ssid[] = "Your_WiFi_Name";
   char pass[] = "Your_WiFi_Password";