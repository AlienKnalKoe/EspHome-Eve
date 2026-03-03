# EspHome-Eve

This repository contains the ESPHome configuration for **EspHome-Eve**, based on the ESP32-4848S040 (Guition) hardware.

## Hardware Requirements
- **Display:** ESP32-4848S040 (4-inch 480x480 RGB MIPI LCD)
- **Touch:** GT911
- **Board:** ESP32-S3 DevKitC-1

## Features
- MIPI RGB Display integration
- LVGL UI framework
- GT911 Touch controller
- Custom UI pages (Face, Info, Controls, Settings)

## Setup
1. Install [ESPHome](https://esphome.io/).
2. Create a `secrets.yaml` file based on the provided template.
3. Place required fonts in a `fonts/` directory.
4. Compile and flash:
   ```bash
   esphome run eve.yaml
   ```

## Project Structure
- `eve.yaml`: Main ESPHome configuration.
- `secrets.yaml`: WiFi and API credentials (not included in repo).
- `fonts/`: Custom fonts for the UI.
