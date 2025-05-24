#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Memory optimization - store strings in PROGMEM
const char PROGMEM SCROLL_TEXT[] = "MERRY XMAS!";
const char PROGMEM STARTUP_MSG[] = "Christmas Demo initialized";

// Display configuration
constexpr int SCREEN_WIDTH = 132;  // Effective usable width for this specific 0.42" OLED
constexpr int SCREEN_HEIGHT = 64;

constexpr int FRAME_WIDTH = 72;
constexpr int FRAME_HEIGHT = 40;
constexpr int X_OFFSET = (SCREEN_WIDTH - FRAME_WIDTH) / 2;  // Now calculates to 30
constexpr int Y_OFFSET = (SCREEN_HEIGHT - FRAME_HEIGHT) / 2;

// Animation timing (using constexpr for compile-time constants)
constexpr unsigned long SCENE_DURATION = 5000;          // 5 seconds
constexpr unsigned long DAY_NIGHT_DURATION = 10000;     // 10 seconds
constexpr unsigned long WEATHER_CHANGE_DURATION = 10000; // 10 seconds
constexpr unsigned long ANIMATION_FRAME_DELAY = 50;     // 50ms = 20 FPS
constexpr unsigned long STAR_ANIMATION_SPEED = 50;      // Star twinkle speed
constexpr unsigned long ARM_ANIMATION_SPEED = 200;      // Snowman arm speed
constexpr unsigned long TEXT_SCROLL_SPEED = 100;        // Text scroll speed
constexpr unsigned long FLAME_ANIMATION_SPEED = 100;    // Flame flicker speed

// Particle system configuration
constexpr int MAX_PARTICLES = 32;
constexpr int MIN_PARTICLE_SPEED = 1;
constexpr int MAX_PARTICLE_SPEED = 3;

// Drawing configuration
constexpr int STAR_MAX_BRIGHTNESS = 3;
constexpr int FLAME_MAX_HEIGHT = 4;
constexpr int SANTA_WIDTH = 12;
constexpr int SANTA_HEIGHT = 6;

// I2C Configuration
constexpr uint8_t I2C_SDA_PIN = 6;
constexpr uint8_t I2C_SCL_PIN = 5;
constexpr uint32_t I2C_FREQUENCY = 400000;  // 400kHz

// Serial configuration
constexpr uint32_t SERIAL_BAUD_RATE = 115200;

// Feature flags
constexpr bool ENABLE_SERIAL_DEBUG = true;
constexpr bool ENABLE_STAR_ANIMATION = true;
constexpr bool ENABLE_WEATHER_EFFECTS = true;
constexpr bool ENABLE_DAY_NIGHT_CYCLE = true;

#endif // CONFIG_H 