# Voice-Controlled Smart Home Automation with ESP32, Vosk, and MQTT

This project provides a robust solution for smart home automation using offline voice commands, enabling you to control home appliances like lights, fans, and motors without an internet connection. The system leverages the ESP32 microcontroller, Vosk speech recognition model, and the MQTT protocol for seamless communication between your laptop and the ESP32 devices over a local Wi-Fi network. This project is perfect for IoT enthusiasts, smart home developers, and anyone interested in offline voice-activated automation.

## Project Overview

The goal of this project is to provide an easy-to-implement, offline, voice-controlled home automation system. Using Vosk's offline speech recognition model, voice commands are captured and processed on your laptop. These commands are then sent to the ESP32 microcontroller using the MQTT protocol, allowing you to control connected devices like lights, fans, and motors.

### Key Features:
- **Offline Voice Recognition**: Utilizes Vosk's offline speech recognition model for high accuracy without needing an internet connection.
- **Local MQTT Communication**: Uses the MQTT protocol to send commands to ESP32 devices over the same Wi-Fi network, ensuring low latency.
- **Flexible Device Control**: Supports multiple devices, including lights, fans, and stepper motors, with easy customization to add more devices.
- **User-Friendly Setup**: Provides a detailed guide on setting up the hardware and software, making it suitable for beginners and advanced users alike.

## System Architecture

### Voice Recognition (Laptop Side):
- Captures voice input using a microphone.
- Uses the Vosk speech recognition library to convert spoken commands into text.
- Python processes the text, matching it with predefined keywords (like "on", "off", "fan", "light", etc.).
- If a valid command is recognized, it publishes an MQTT message to the specified topic.

### MQTT Communication:
- The laptop acts as an MQTT client, publishing messages to the ESP32.
- The ESP32 microcontroller subscribes to relevant topics, listening for control messages.

### Device Control (ESP32 Side):
- Receives MQTT messages and controls devices accordingly.
- Uses GPIO pins to control relays for lights or motors, providing flexibility to add more devices.
- Supports controlling both simple devices (like lights) and stepper motors.

## Hardware Requirements:
- ESP32 microcontroller
- Microphone (for voice input)
- Laptop/PC (for running the voice recognition and MQTT client)
- Relay modules for controlling lights or other appliances
- Stepper motor and driver (optional)
- Wi-Fi router (for local network communication)

## Software Requirements:
- Python 3.x
- Vosk Speech Recognition library
- PyAudio for capturing audio input
- paho-mqtt for MQTT communication
- Arduino IDE for ESP32 firmware

## How It Works

### Voice Recognition Script (Laptop)
1. **Speech-to-Text Conversion**: Listens for voice commands using a microphone and converts them to text using Vosk.
2. **Command Matching**: Checks if the recognized text matches any predefined commands.
3. **MQTT Message Publishing**: Sends an MQTT message with the appropriate command (e.g., "on kitchen light", "off fan") to the ESP32.

### ESP32 Firmware
1. **MQTT Subscription**: The ESP32 subscribes to topics like `home/kitchen/light`, `home/fan`, etc.
2. **Device Control**: Based on the received message, it controls the connected devices by toggling GPIO pins.
3. **Feedback Mechanism**: Optional feedback to the laptop or mobile app confirming the action.

## Setup Instructions

### Step 1: Setting Up Vosk for Offline Speech Recognition
- 1. Install Vosk and PyAudio:
   ```bash
   pip install vosk pyaudio
- 2. Download the Vosk English model from Vosk Models.
- 3. Extract the model and update the model_path in the Python script.
### Step 2: Setting Up MQTT on Your Laptop
- 1. Install the paho-mqtt library:
   ```bash
   pip install paho-mqtt
- 2.Run the Keyword_Spotting_speech_to_mqtt.ipynb script to start listening for commands.
### Step 3: Flashing ESP32 with Arduino Code
- 1.Open the provided esp32_mqtt_control.ino file in Arduino IDE.
- 2.Update the Wi-Fi SSID, password, and MQTT broker IP in the code.
- 3.Upload the code to your ESP32.
### Step 4: Wiring ESP32 to Control Devices
- 1.Lights: Connect relay modules to control AC appliances.
- 2.Stepper Motor: Use a driver module to control stepper motors.
- 3.Ensure all components are properly powered and grounded.
## Example Commands:
- "Turn on kitchen light"
- "Turn off bedroom light"
-"Turn on fan"
- "Turn off fan"
= "Terminate" (to stop listening)
## Project Files:
- Keyword_Spotting_speech_to_mqtt.ipynb: Python script for voice recognition and MQTT communication
- ESP32_mqtt_ArduinoIDE.ino: ESP32 Arduino sketch for device control

## Future Enhancements:
- 1.Adding support for more appliances.
- 2.Integrating a mobile app for manual control.
- 3.Implementing custom wake word detection.
- 4.Extending support for additional voice commands.
