#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include <Arduino.h>
#include <U8g2lib.h>
#include "config.h"

// Forward declarations
void debugPrint(int level, const char* format, ...);

class AnimationTimer {
private:
    unsigned long lastUpdate;
    unsigned long interval;
    bool enabled;

public:
    AnimationTimer(unsigned long intervalMs = 100) 
        : lastUpdate(0), interval(intervalMs), enabled(true) {}
    
    bool shouldUpdate() {
        if (!enabled) return false;
        
        unsigned long currentTime = millis();
        if (currentTime - lastUpdate >= interval) {
            lastUpdate = currentTime;
            return true;
        }
        return false;
    }
    
    void setInterval(unsigned long intervalMs) { interval = intervalMs; }
    void enable() { enabled = true; }
    void disable() { enabled = false; }
    void reset() { lastUpdate = millis(); }
    
    // Get progress as a float between 0.0 and 1.0
    float getProgress() const {
        if (!enabled) return 0.0f;
        unsigned long elapsed = millis() - lastUpdate;
        return min(1.0f, (float)elapsed / (float)interval);
    }
};

class AnimationValue {
private:
    float currentValue;
    float targetValue;
    float startValue;
    float speed;
    bool animating;

public:
    AnimationValue(float initialValue = 0.0f) 
        : currentValue(initialValue), targetValue(initialValue), 
          startValue(initialValue), speed(1.0f), animating(false) {}
    
    void animateTo(float target, float animationSpeed = 1.0f) {
        startValue = currentValue;
        targetValue = target;
        speed = animationSpeed;
        animating = true;
    }
    
    void update() {
        if (!animating) return;
        
        float diff = targetValue - currentValue;
        if (abs(diff) < 0.01f) {
            currentValue = targetValue;
            animating = false;
            return;
        }
        
        currentValue += diff * speed * (ANIMATION_FRAME_DELAY / 1000.0f);
    }
    
    float getValue() const { return currentValue; }
    bool isAnimating() const { return animating; }
    void setValue(float value) { 
        currentValue = value; 
        targetValue = value;
        animating = false;
    }
};

class ParticleSystem {
private:
    struct Particle {
        float x, y;
        float vx, vy;
        uint8_t type;
        float life;
        bool active;
    };
    
    Particle particles[MAX_PARTICLES];
    int activeCount;
    
public:
    ParticleSystem() : activeCount(0) {
        for (int i = 0; i < MAX_PARTICLES; i++) {
            particles[i].active = false;
        }
    }
    
    void addParticle(float x, float y, float vx, float vy, uint8_t type = 0) {
        for (int i = 0; i < MAX_PARTICLES; i++) {
            if (!particles[i].active) {
                particles[i] = {x, y, vx, vy, type, 1.0f, true};
                activeCount++;
                break;
            }
        }
    }
    
    void update() {
        for (int i = 0; i < MAX_PARTICLES; i++) {
            if (!particles[i].active) continue;
            
            particles[i].x += particles[i].vx;
            particles[i].y += particles[i].vy;
            particles[i].life -= 0.01f;
            
            // Remove particles that are off-screen or dead
            if (particles[i].life <= 0 || 
                particles[i].x < X_OFFSET || particles[i].x > X_OFFSET + FRAME_WIDTH ||
                particles[i].y < Y_OFFSET || particles[i].y > Y_OFFSET + FRAME_HEIGHT) {
                particles[i].active = false;
                activeCount--;
            }
        }
    }
    
    void draw(U8G2 &display) {
        for (int i = 0; i < MAX_PARTICLES; i++) {
            if (!particles[i].active) continue;
            
            int x = (int)particles[i].x;
            int y = (int)particles[i].y;
            
            switch (particles[i].type) {
                case 0: // Snow
                    if (i % 4 == 0) {
                        display.drawBox(x, y, 2, 2);
                    } else {
                        display.drawPixel(x, y);
                    }
                    break;
                case 1: // Rain
                    display.drawVLine(x, y, 2);
                    break;
                case 2: // Stars
                    display.drawPixel(x, y);
                    break;
            }
        }
    }
    
    void clear() {
        for (int i = 0; i < MAX_PARTICLES; i++) {
            particles[i].active = false;
        }
        activeCount = 0;
    }
    
    int getActiveCount() const { return activeCount; }
};

#endif // ANIMATION_MANAGER_H 