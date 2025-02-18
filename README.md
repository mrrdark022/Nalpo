# AskMe - Voice Assistant Using ESP32 and Gemini AI

## Overview
AskMe is a voice assistant system that uses an **ESP32** and an **INMP441 microphone** to capture audio. The captured audio is sent to a server, processed to detect speech, and then sent to **Gemini AI** for a response. The response is converted back into speech and played through a Bluetooth speaker connected to the server.

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
git clone https://github.com/mrrdark022/askme
