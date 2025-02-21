# Nalpo - Voice Assistant Using ESP32 and Gemini AI

## Overview
Nalpo is a voice assistant system that uses an **ESP32** and an **INMP441 microphone** to capture audio. The captured audio is sent to a server, where speech is detected and transcribed. The text is then processed by **Gemini AI** to generate a response, which is converted back into speech and played through a Bluetooth speaker connected to the server.

Additionally, Nalpo features an expressive face with **four LEDs and two servos** controlled by an **ESP8266**. The face synchronizes with the assistant’s voice, displaying different movements based on the interaction state:
- **Idle Mode**: The face moves randomly.
- **Recording Mode**: The face stops moving, and the mouth LEDs glow.
- **Speaking Mode**: The mouth LEDs blink with a 50ms delay to simulate speech.

## Features
- **ESP32 Audio Streaming**: Captures and sends live audio data to the server.
- **Speech Detection**: Server listens for speech and starts recording automatically.
- **Gemini AI Integration**: Processes transcribed text and generates responses.
- **Text-to-Speech (TTS)**: Converts AI-generated text to speech.
- **Bluetooth Speaker Output**: Plays the synthesized speech output.
- **Animated Face (ESP8266)**: Expressive face with servo and LED-based mouth movement.

## Installation

### Clone the Repository
To get started, clone the repository to your local machine:
```bash
git clone https://github.com/mrrdark022/Nalpo
```

### Hardware Setup
#### Pin Connections
Ensure the **INMP441 microphone** is properly connected to the **ESP32**:
```
+------------------+
|   INMP441 Mic   |
+------------------+
|  VCC   ------------+------------>  3.3V (ESP32)
|  GND   ------------+------------>  GND (ESP32)
|  SD    ------------+------------>  I2S_SD (GPIO 32)
|  SCK   ------------+------------>  I2S_SCK (GPIO 33)
|  WS    ------------+------------>  I2S_WS (GPIO 25)
+------------------+
       |
    +-----+
    | ESP |
    |  32 |
    +-----+
       |
Wi-Fi / UDP Connection (to server)
```
Ensure that your **ESP32** firmware is correctly flashed using the provided `.ino` code in your preferred IDE.

### Server Setup
1. Navigate to the server directory:
```bash
cd askme
```
2. Install required dependencies:
```bash
pip install -r requirements.txt  # (Use a virtual environment if needed)
```
3. Start the server:
```bash
python server.py
```

## Acknowledgments
The majority of the code was generated with the help of ChatGPT. Feel free to modify and improve it as needed!

For any issues or contributions, visit the repository: [Nalpo GitHub](https://github.com/mrrdark022/Nalpo)

