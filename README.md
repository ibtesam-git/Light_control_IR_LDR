#Project Description – LDR & IR Controlled LED System (ESP-IDF v5.4.1, ESP32-S3)

This project implements a simple light control system on the ESP32-S3 using ESP-IDF v5.4.1, combining input from an LDR (Light Dependent Resistor) and an IR (Infrared) sensor to control an LED.

The IR sensor acts as a toggle switch: each time motion or obstruction is detected, it enables or disables the LDR-based control logic.

When LDR control is active, the system continuously monitors ambient light:

🌑 Dark environment → LED remains OFF

💡 Bright environment → LED turns ON

If the IR sensor disables LDR mode, the LED is forced OFF, regardless of light conditions.

The project demonstrates:

Use of GPIO inputs and outputs in ESP-IDF

Real-time sensor polling with FreeRTOS tasks

Simple state toggling and debouncing logic

Use of ESP_LOGI for serial debug logging

Pin configuration (default):

GPIO12 – LDR sensor input

GPIO5 – IR sensor input

GPIO2 – LED output

This project is ideal as a starting point for smart lighting systems, sensor fusion demos, or embedded automation projects on ESP32-S3.
