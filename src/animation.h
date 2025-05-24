#ifndef ANIMATION_H
#define ANIMATION_H

#include <Arduino.h>
#include <U8g2lib.h>

// Screen configuration
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int FRAME_WIDTH;
extern const int FRAME_HEIGHT;
extern const int X_OFFSET;
extern const int Y_OFFSET;

// Animation timing
extern const unsigned long SCENE_DURATION;
extern const unsigned long DAY_NIGHT_DURATION;
extern const unsigned long WEATHER_CHANGE_DURATION;

// Weather system
enum Weather { SNOW, RAIN, CLEAR };

// Particle system
struct Particle {
    float x, y;
    float vx, vy;
    uint8_t type;
    bool active;
};

// Animation state management
struct AnimationState {
    unsigned long lastUpdate;
    uint8_t frame;
    int position;
    bool direction;
};

// Scene management
enum Scene {
    SCENE_CHRISTMAS_TREE = 0,
    SCENE_SANTA_SLEIGH,
    SCENE_FIREPLACE,
    SCENE_WEATHER_DISPLAY,
    SCENE_COUNT
};

// Function declarations
void initDisplay();
void initAnimationSystem();
void updateSceneManager();
void updateWeatherSystem();
void updateDayNightCycle();

// Drawing functions
void drawChristmasScene();
void drawSantaScene();
void drawFireplaceScene();
void drawWeatherScene();
void drawScrollingText();
void drawFrameBorder();

// Animation helpers
void updateParticleSystem();
void updateAnimationTimers();
void resetScene(Scene scene);

#endif // ANIMATION_H 