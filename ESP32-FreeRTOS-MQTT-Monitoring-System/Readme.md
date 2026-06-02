# ESP32 Smart Environmental Monitoring System

## Overview

This project is an ESP32-based Smart Environmental Monitoring System developed using FreeRTOS and MQTT.
The system monitors temperature, humidity, gas concentration, and ambient light using DHT11, MQ2, and LDR sensors.
Sensor data is displayed on an OLED display and published to an MQTT broker over WiFi for real-time monitoring through MQTTX.
A relay-based alert mechanism automatically activates when unsafe gas levels are detected.

## Features

* FreeRTOS-based multitasking
* Mutex-protected shared sensor data
* DHT11 temperature and humidity monitoring
* MQ2 gas detection and alert system
* LDR light monitoring
* OLED display visualization
* WiFi connectivity
* MQTT-based sensor data publishing
* Relay/Buzzer alert mechanism

## Hardware Components

* ESP32 Development Board
* DHT11 Sensor
* MQ2 Gas Sensor
* LDR Module
* SSD1306 OLED Display
* Relay Module
* Buzzer
* LEDs

## System Architecture

Sensor Task
→ Reads DHT11, MQ2, and LDR sensor values.

OLED Task
→ Displays sensor values on OLED.

Alert Task
→ Activates relay and LEDs based on gas level.

WiFi/MQTT Task
→ Publishes sensor data to MQTT broker every 5 seconds.

## MQTT Broker

Broker: broker.hivemq.com
Port: 1883

## MQTT Topics

* smart_monitor/temperature
* smart_monitor/humidity
* smart_monitor/gas
* smart_monitor/ldr

## Project Output

* Real-time OLED monitoring
* Gas leakage alert system
* MQTT-based IoT monitoring using MQTTX
* Live sensor data publishing over WiFi
