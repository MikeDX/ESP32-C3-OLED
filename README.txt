ESP32 Christmas OLED Animation
=============================

A festive Christmas animation project for ESP32 microcontrollers using a 128x64 OLED display (SSD1306).

Features
--------
- Multiple animated Christmas scenes including:
  * Christmas tree with twinkling decorations
  * Animated snowman with moving arms
  * Santa's sleigh with reindeer
  * Fireplace with animated flames
  * Presents under the tree
  * Scrolling "MERRY XMAS!" text
- Dynamic weather effects (snow, rain, clear sky)
- Day/night cycle with sun and moon
- Scene transitions every 5 seconds

Hardware Requirements
-------------------
- ESP32-C3 board (or compatible ESP32 board)
- SSD1306 128x64 OLED Display
- I2C connection:
  * SDA - GPIO6
  * SCL - GPIO5

Software Dependencies
-------------------
- PlatformIO
- Arduino framework
- U8g2 library (for OLED display)

Setup Instructions
----------------
1. Install PlatformIO in your IDE
2. Clone this repository
3. Connect the OLED display to your ESP32 board
4. Build and upload the project
5. Monitor serial output at 115200 baud

Display Connection
----------------
- Connect SDA to GPIO6
- Connect SCL to GPIO5
- Connect VCC to 3.3V
- Connect GND to GND

Notes
-----
- The animation runs in a 72x40 pixel frame centered on the display
- Scene changes occur automatically every 5 seconds
- Day/night cycle changes every 10 seconds
- Weather effects cycle between snow, rain, and clear sky

Created by: MikeDX
License: MIT
