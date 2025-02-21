# Nalpo - Voice Assistant Using ESP32 and Gemini AI

## Overview
Nalpo is a voice assistant system that uses an **ESP32** and an **INMP441 microphone** to capture audio. The captured audio is sent to a server, processed to detect speech, and then sent to **Gemini AI** for a response. The response is converted back into speech and played through a Bluetooth speaker connected to the server.

## Features
- **ESP32** sends audio bytes to the server.
- **Speech Detection**: Server listens to audio and starts recording when speech is detected.
- **Gemini AI Integration**: Processes the transcribed audio and generates a response.
- **Text-to-Speech (TTS)**: Converts the Gemini AI response back to speech.
- **Bluetooth Speaker Support**: Plays the response through a Bluetooth speaker.

## Installation

### Clone the Repository
To get started, first clone the repository to your local machine:

```bash
git clone https://github.com/mrrdark022/Nalpo
```
### PIN Connection
```bash
  Download all the needed Drivers

               +------------------+
               |   INMP441 Mic    |
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
                     | 32  |
                     +-----+
                        |
       Wi-Fi / UDP Connection (to server)

Make sure to copy your ESP32.ino code into your IDE, and if everything is good, flash it.
```
### SERVER Configuration
```bash
cd askme
pip install -r requirement.txt #(In newer systems you need to have a python env)
python server.py
```
## The full code was not written by me; most of it was done using ChatGPT. If you need a straightforward solution, you can use it.
