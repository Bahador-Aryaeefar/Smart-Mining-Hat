# Smart Mining Hat – Wearable IoT Safety Device

A **wearable safety device** designed for miners, built with **ESP32** and various environmental sensors, to monitor critical factors such as gas concentration, temperature, humidity, pressure, and altitude in real-time.

![photo_2025-04-25_11-42-48](https://github.com/user-attachments/assets/93e6997e-6375-4913-aa8b-f488ea41c643)

## Features

- 📡 **Wi-Fi hotspot** and **web server** setup for local communication with connected users.
- 🌡️ Monitors **temperature** (DHT22), **humidity** (DHT22), **pressure** (BMP180), **altitude** (BMP180), and **gas concentration** (MQ-9B).
- 🚨 **Real-time danger notifications** via a **web interface** built with **React**, with alerts for hazardous gas levels.
- 💡 Uses **LED indicators** and a **piezo buzzer** for local alerts when gas levels exceed safe thresholds.
- 🔄 Data is served through a **REST API** in JSON format for easy integration with external systems.
- 🧪 **Proteus simulations** were performed to ensure the accuracy of sensor data integration and device behavior.

## How It Works

1. The device connects to a local **Wi-Fi network** via ESP32, creating a hotspot for user access.
2. Sensor data is continuously read and made available through a simple web server.
3. A **React web interface** displays real-time data and sends notifications if any parameter exceeds safe limits.
4. The device uses **LED indicators** and a **buzzer** to alert the user in case of unsafe conditions.

## Technologies

- **ESP32** (microcontroller)
- **DHT22**, **BMP180**, **MQ-9B** (sensors)
- **React** (front-end for displaying data and sending notifications)
- **Arduino Framework** (for firmware development)
- **Proteus** (for simulations)
