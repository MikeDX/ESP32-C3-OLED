#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#include <Arduino.h>
#include "config.h"

// Debug levels
enum DebugLevel {
    DEBUG_ERROR = 0,
    DEBUG_WARN = 1,
    DEBUG_INFO = 2,
    DEBUG_VERBOSE = 3
};

// Forward declare the debug print function
void debugPrint(DebugLevel level, const char* format, ...);

// Memory monitoring
class MemoryMonitor {
public:
    static void printMemoryUsage() {
        if (!ENABLE_SERIAL_DEBUG) return;
        
        #ifdef ESP32
        Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());
        Serial.printf("Min free heap: %d bytes\n", ESP.getMinFreeHeap());
        Serial.printf("Heap size: %d bytes\n", ESP.getHeapSize());
        #endif
    }
    
    static bool checkMemoryLeaks() {
        #ifdef ESP32
        static uint32_t lastFreeHeap = ESP.getFreeHeap();
        uint32_t currentFreeHeap = ESP.getFreeHeap();
        
        if (currentFreeHeap < lastFreeHeap - 1000) { // 1KB threshold
            debugPrint(DEBUG_WARN, "Potential memory leak detected!");
            lastFreeHeap = currentFreeHeap;
            return true;
        }
        lastFreeHeap = currentFreeHeap;
        #endif
        return false;
    }
};

// Performance monitoring
class PerformanceMonitor {
private:
    unsigned long frameStartTime;
    unsigned long maxFrameTime;
    unsigned long frameCount;
    float averageFrameTime;
    
public:
    PerformanceMonitor() : frameStartTime(0), maxFrameTime(0), frameCount(0), averageFrameTime(0) {}
    
    void startFrame() {
        frameStartTime = micros();
    }
    
    void endFrame() {
        if (frameStartTime == 0) return;
        
        unsigned long frameTime = micros() - frameStartTime;
        frameCount++;
        
        // Update max
        if (frameTime > maxFrameTime) {
            maxFrameTime = frameTime;
        }
        
        // Update average (rolling average)
        averageFrameTime = (averageFrameTime * (frameCount - 1) + frameTime) / frameCount;
        
        // Report if frame time is excessive
        if (frameTime > 100000) { // > 100ms
            debugPrint(DEBUG_WARN, "Slow frame detected: %lu us", frameTime);
        }
        
        frameStartTime = 0;
    }
    
    void printStats() {
        if (!ENABLE_SERIAL_DEBUG) return;
        
        Serial.printf("Performance Stats:\n");
        Serial.printf("  Average frame time: %.2f us (%.1f FPS)\n", 
                     averageFrameTime, 1000000.0f / averageFrameTime);
        Serial.printf("  Max frame time: %lu us\n", maxFrameTime);
        Serial.printf("  Total frames: %lu\n", frameCount);
    }
    
    float getAverageFPS() const {
        return averageFrameTime > 0 ? 1000000.0f / averageFrameTime : 0;
    }
};

// Error handling
class ErrorHandler {
private:
    static uint8_t errorCount;
    static unsigned long lastErrorTime;
    
public:
    enum ErrorCode {
        ERROR_NONE = 0,
        ERROR_DISPLAY_INIT,
        ERROR_I2C_TIMEOUT,
        ERROR_MEMORY_LOW,
        ERROR_ANIMATION_OVERFLOW
    };
    
    static void reportError(ErrorCode code, const char* message = nullptr) {
        errorCount++;
        lastErrorTime = millis();
        
        if (ENABLE_SERIAL_DEBUG) {
            Serial.printf("ERROR %d: %s\n", code, message ? message : "Unknown error");
        }
        
        // Flash LED or display error indicator if needed
        handleErrorDisplay(code);
    }
    
    static bool hasRecentErrors() {
        return (millis() - lastErrorTime) < 5000; // 5 second window
    }
    
    static uint8_t getErrorCount() { return errorCount; }
    
private:
    static void handleErrorDisplay(ErrorCode code) {
        // Could flash an LED or show error on display
        // For now, just increment error counter
    }
};

// Debug printing with levels - implementation
inline void debugPrint(DebugLevel level, const char* format, ...) {
    if (!ENABLE_SERIAL_DEBUG) return;
    
    // Simple level filtering (could be made configurable)
    #ifdef DEBUG_LEVEL
    if (level > DEBUG_LEVEL) return;
    #endif
    
    const char* levelStr[] = {"ERROR", "WARN", "INFO", "VERBOSE"};
    
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    Serial.printf("[%s] %s\n", levelStr[level], buffer);
}

// Initialize static members
uint8_t ErrorHandler::errorCount = 0;
unsigned long ErrorHandler::lastErrorTime = 0;

#endif // DEBUG_UTILS_H 