# final-project-Soha18

# 🌡️ Smart Industrial Human-Machine Interface (HMI) System

> A real-time monitoring and control system for industrial environments using sensors, actuators, and a touchscreen HMI interface — built on Embedded Linux (Yocto) and Raspberry Pi.

---

## 📋 Overview

This project implements a **Smart Industrial HMI System** that:

- Reads temperature and humidity data from I2C sensors.
- Controls a fan through a relay based on sensor thresholds or manual button input.
- Displays real-time system status on a touchscreen using a custom Qt GUI.
- Uses a character device driver to interface kernel space and user space.

---

## ✨ Features

- Real-time display of humidity and temperature.
- Auto and manual fan control with safety logic.
- Touchscreen GUI interface with sensor status.
- Modular architecture with character device driver.

---

## 🛠️ Hardware Used

| Component              | Interface | Purpose                  |
|------------------------|-----------|---------------------------|
| Raspberry Pi 4         | -         | Main controller           |
| DHT20/SHT31 Sensor     | I2C       | Humidity & Temp reading   |
| Relay Module           | GPIO      | Fan control               |
| Push Buttons (x2)      | GPIO      | Manual fan ON/OFF         |
| Cooling Fan            | -         | Controlled actuator       |
| Touchscreen Display    | HDMI/GPIO | GUI interface             |

---

## 💻 Software Used

- **Yocto Project**: Custom Embedded Linux Image
- **Qt (C++/QML)**: GUI Development
- **C/C++**: Kernel module and application logic
- **Character Device Driver**: User-Kernel communication

---

