# M5Stamp S3 BLE LED Control Project

This repository hosts a basic project that is an outcome of my experiments and learning myself how to program Bluetooth Low Energy (BLE) communication on ESP32 device, specifically using the M5Stamp S3. 
The project demonstrates how to enable BLE communication and control the RGB LED on the ESP32 device via an external  BLE-enabled device (e.g., smartphone)

## Overview

This project provides a fundamental BLE-based feature: the ability to connect to the ESP32 device and remotely change the LED color using an external BLE device. While this is a basic functionality, it covers the essential steps required for BLE communication on the ESP32, allowing you to:

- Set up a basic BLE server on the ESP32
- Manage connections with external BLE clients
- Change LED states based on BLE commands

**M5Stamp S3** was chosen as it is a compact and versatile ESP32 device, ideal for prototyping and experimenting with BLE communication. This device is easy to flash (via USB-C), includes an in-built physical button, and features an RGB LED for real-time visual feedback -- perfect for quickly testing BLE functionality.

Other ESP32 would be equally easy to programm, using the same basic building blocks.


> Note: This repository focuses on implementation rather than BLE theory. Please refer to external resources if you need a primer on BLE fundamentals. Understanding of BLE concepts is strongly recommended, as it can save your time and energy when developing and debugging this type of functionality.


## Getting Started

This project uses [VS Code IDE](https://code.visualstudio.com/) and [PlatformIO extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) as a development environment.

To start, **clone the repository, open the project in VS Code**. 

See [more detailed description](./docs/project-setup.md) of the project setup, if needed.
