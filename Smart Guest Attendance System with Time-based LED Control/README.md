# Smart Guest Attendance System (ESP32)

A smart IoT solution for monitoring guest traffic and automating room lighting. This project uses an ESP32 to track entries/exits, manage LED brightness based on time-of-day/ambient light, and sync data to **Blynk** and **ThingSpeak**.

---

## 🌐 Live Simulation & Circuit
You can interact with the logic of this project virtually. This allows for testing the ultrasonic triggers and the RTC-based light logic without hardware.

* **Wokwi Simulation:** [Click here to view the project on Wokwi](https://wokwi.com/projects/417800600758961153)
* **Circuit Diagram:**
    ![Circuit Diagram](![alt text](![alt text](image.png)))
    *(Note: Refer to the `/images` folder for high-resolution wiring schematics)*

---

## 🚀 Features
* **Dual-Sensor Counting:** Uses two HC-SR04 ultrasonic sensors to determine if a guest is entering or exiting.
* **Blynk Permission Gate:** A virtual switch in the Blynk app acts as a "security gate" to allow or deny entry.
* **Time-Aware Lighting:** Integrated DS1307 RTC adjusts LED brightness presets (Morning, Noon, Evening, Night).
* **Ambient Light Sensing:** An LDR fine-tunes the LED brightness based on actual room lighting (0-4095 lux mapping).
* **Cloud Logging:** Real-time data visualization on ThingSpeak and remote control via Blynk IoT.

---

## 🛠️ Hardware Requirements
* **ESP32** (NodeMCU or DevKit V1)
* **2x HC-SR04** Ultrasonic Sensors
* **DS1307 RTC** Module (I2C)
* **LDR** (Photoresistor)
* **LED** (with 220Ω resistor)
* Connecting wires & Breadboard

---

## 📂 Project Structure
* `smartguest.ino`: Main logic for sensors, lighting, and cloud connectivity.
* `config.h`: **(Required but not uploaded)** You must create this file locally to store your private credentials.

### ⚙️ Local Configuration
To run this project, create a `config.h` tab in your Arduino IDE:
```cpp
#ifndef CONFIG_H
#define CONFIG_H

#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN"
#define WIFI_NETWORK        "YOUR_WIFI_NAME"
#define WIFI_PASS           "YOUR_WIFI_PASS"
#define CHANNEL_ID          000000 
#define CHANNEL_API_KEY     "YOUR_API_KEY"

#endif