#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 6, 5);

// Screen dimensions
const int width = 72;
const int height = 40;
const int xOffset = (132 - width) / 2;
const int yOffset = (64 - height) / 2;

// Snow particles
const int NUM_SNOWFLAKES = 32;
struct Snowflake {
  int x;
  int y;
  int speed;
} snowflakes[NUM_SNOWFLAKES];

// Add these new constants near the top
const bool ANIMATE_STAR = true;  // Animate star brightness
const int STAR_SIZE = 3;
unsigned long starTimer = 0;
int starBrightness = 0;
bool starIncreasing = true;

// Add these variables near the top with other constants
unsigned long armTimer = 0;
int armPosition = 0;
bool armGoingUp = true;

// Add these constants at the top
const char* SCROLL_TEXT = "MERRY XMAS!";
int textX = xOffset + width;  // Start position off-screen
unsigned long textTimer = 0;

// Add these constants near the top with others
const int SANTA_WIDTH = 12;
const int SANTA_HEIGHT = 6;
unsigned long santaTimer = 0;
int santaX = xOffset + width + SANTA_WIDTH;  // Start off-screen
bool santaVisible = false;

// Add these constants near the top
const int FLAME_HEIGHT = 4;
unsigned long flameTimer = 0;
uint8_t flamePattern = 0;

// Add near top with other constants
enum Weather { SNOW, RAIN, CLEAR };
Weather currentWeather = SNOW;
unsigned long weatherTimer = 0;

// Add near top
bool isNightTime = true;
unsigned long dayNightTimer = 0;
const unsigned long DAY_NIGHT_DURATION = 10000; // 10 seconds per cycle

// Add this near the top with other declarations
void drawSinglePresent(int x, int y, int w, int h);

// Add near top with other constants
const unsigned long SCENE_DURATION = 5000; // 5 seconds per scene
unsigned long sceneTimer = 0;
uint8_t currentScene = 0;

// Initialize snowflakes with random positions
void initSnowflakes() {
  for (int i = 0; i < NUM_SNOWFLAKES; i++) {
    snowflakes[i].x = random(xOffset, xOffset + width);
    snowflakes[i].y = random(yOffset, yOffset + height);
    snowflakes[i].speed = random(1, 3);
  }
}

// Draw a simple Christmas tree
void drawTree() {
  int treeX = xOffset + width/2;
  int treeY = yOffset + height - 5;
  
  // Draw tree triangles
  for (int i = 0; i < 3; i++) {
    int triangleSize = 12 - (i * 3);
    u8g2.drawTriangle(
      treeX, treeY - (i * 8) - triangleSize,
      treeX - triangleSize, treeY - (i * 8),
      treeX + triangleSize, treeY - (i * 8)
    );
    
    // Add decorations (baubles) to each level
    int level_y = treeY - (i * 8) - 2;
    int max_width = triangleSize - 2;
    u8g2.drawPixel(treeX - max_width/2, level_y);
    u8g2.drawPixel(treeX + max_width/2, level_y);
  }
  
  // Draw trunk
  u8g2.drawBox(treeX - 2, treeY, 4, 5);
  
  // Add twinkling decorations
  static uint8_t twinkleFrame = 0;
  if (millis() % 500 == 0) twinkleFrame++;
  
  for (int i = 0; i < 3; i++) {
    int y = treeY - (i * 8) - 4;
    // Add decorations that twinkle alternately
    if ((twinkleFrame + i) % 2 == 0) {
      u8g2.drawPixel(treeX, y);
    }
  }
}

// Add this new function to draw a twinkling star
void drawStar() {
  int starX = xOffset + width/2;
  int starY = yOffset + 8;  // Position above tree
  
  if (ANIMATE_STAR) {
    // Update star brightness every 50ms
    if (millis() - starTimer > 50) {
      if (starIncreasing) {
        starBrightness++;
        if (starBrightness >= 3) starIncreasing = false;
      } else {
        starBrightness--;
        if (starBrightness <= 0) starIncreasing = true;
      }
      starTimer = millis();
    }
  }
  
  // Draw star with varying size based on brightness
  for (int i = 0; i <= starBrightness; i++) {
    u8g2.drawPixel(starX, starY - i);     // Top
    u8g2.drawPixel(starX, starY + i);     // Bottom
    u8g2.drawPixel(starX - i, starY);     // Left
    u8g2.drawPixel(starX + i, starY);     // Right
  }
}

// Modify snowflakes to be more interesting
void updateSnow() {
  static uint8_t frame = 0;
  frame++;
  
  for (int i = 0; i < NUM_SNOWFLAKES; i++) {
    snowflakes[i].y += snowflakes[i].speed;
    
    // Add slight horizontal movement
    if ((frame + i) % 4 == 0) {
      snowflakes[i].x += (i % 2) ? 1 : -1;
    }
    
    // Reset snowflake if it goes below or outside the frame
    if (snowflakes[i].y > yOffset + height || 
        snowflakes[i].x < xOffset || 
        snowflakes[i].x > xOffset + width) {
      snowflakes[i].y = yOffset;
      snowflakes[i].x = random(xOffset + 2, xOffset + width - 2);
    }
    
    // Draw larger snowflakes (2x2 pixels) for some
    if (i % 4 == 0) {
      u8g2.drawPixel(snowflakes[i].x, snowflakes[i].y);
      u8g2.drawPixel(snowflakes[i].x + 1, snowflakes[i].y);
      u8g2.drawPixel(snowflakes[i].x, snowflakes[i].y + 1);
      u8g2.drawPixel(snowflakes[i].x + 1, snowflakes[i].y + 1);
    } else {
      u8g2.drawPixel(snowflakes[i].x, snowflakes[i].y);
    }
  }
}

// Replace the drawSnowman function with this enhanced version
void drawSnowman() {
  int snowmanX = xOffset + 12;  // Position on the left side
  int snowmanY = yOffset + height - 5;  // Near bottom
  
  // Bottom circle (larger)
  u8g2.drawDisc(snowmanX, snowmanY, 4);
  
  // Middle circle (smaller)
  u8g2.drawDisc(snowmanX, snowmanY - 6, 3);
  
  // Head (smallest)
  u8g2.drawDisc(snowmanX, snowmanY - 11, 2);
  
  // Eyes (make them empty to stand out against filled head)
  u8g2.setDrawColor(0);  // Set to black
  u8g2.drawPixel(snowmanX - 1, snowmanY - 12);
  u8g2.drawPixel(snowmanX + 1, snowmanY - 12);
  u8g2.setDrawColor(1);  // Reset to white
  
  // Animate arms every 200ms
  if (millis() - armTimer > 200) {
    if (armGoingUp) {
      armPosition++;
      if (armPosition >= 2) armGoingUp = false;
    } else {
      armPosition--;
      if (armPosition <= -1) armGoingUp = true;
    }
    armTimer = millis();
  }
  
  // Draw animated arms
  // Left arm
  u8g2.drawLine(snowmanX - 4, snowmanY - 6, 
                snowmanX - 6, snowmanY - 8 + armPosition);
  // Right arm
  u8g2.drawLine(snowmanX + 4, snowmanY - 6, 
                snowmanX + 6, snowmanY - 8 - armPosition);
  
  // Add a small carrot nose
  u8g2.drawPixel(snowmanX, snowmanY - 11);
  u8g2.drawPixel(snowmanX + 1, snowmanY - 11);
  
  // Add a simple scarf
  u8g2.drawLine(snowmanX - 2, snowmanY - 8, 
                snowmanX + 2, snowmanY - 8);
  u8g2.drawLine(snowmanX + 2, snowmanY - 8, 
                snowmanX + 2, snowmanY - 6);
}

// First declare drawSinglePresent
void drawSinglePresent(int x, int y, int w, int h) {
  // Box
  u8g2.drawBox(x - w/2, y - h, w, h);
  
  // Ribbon
  u8g2.drawLine(x, y - h, x, y - h - 2);
  u8g2.drawLine(x - w/2 + 1, y - h/2, x + w/2 - 1, y - h/2);
  
  // Bow
  u8g2.drawPixel(x - 1, y - h - 2);
  u8g2.drawPixel(x + 1, y - h - 2);
}

// Then declare drawPresents which uses it
void drawPresents() {
  // First present (existing one)
  int presentX = xOffset + width - 12;
  int presentY = yOffset + height - 6;
  drawSinglePresent(presentX, presentY, 6, 4);
  
  // Second present (smaller)
  presentX -= 8;
  presentY += 1;
  drawSinglePresent(presentX, presentY, 4, 3);
  
  // Third present (tiny)
  presentX += 10;
  presentY -= 3;
  drawSinglePresent(presentX, presentY, 3, 2);
}

// Add this function
void drawScrollingText() {
  u8g2.setFont(u8g2_font_4x6_tf);  // Use a tiny font
  
  // Update text position every 100ms
  if (millis() - textTimer > 100) {
    textX--;
    if (textX < xOffset - 50) textX = xOffset + width;  // Reset position
    textTimer = millis();
  }
  
  u8g2.drawStr(textX, yOffset + height - 2, SCROLL_TEXT);
  u8g2.setFont(u8g2_font_ncenB10_tr);  // Reset to default font
}

// Add this function
void drawMoon() {
  // Draw in top left corner
  int moonX = xOffset + 6;
  int moonY = yOffset + 6;
  
  // Full moon
  u8g2.drawDisc(moonX, moonY, 3);
  
  // Shadow to make crescent
  u8g2.setDrawColor(0);
  u8g2.drawDisc(moonX + 1, moonY, 2);
  u8g2.setDrawColor(1);
}

// Add this new function
void drawSanta() {
  if (santaVisible == false) {
    santaVisible = true;
    santaX = xOffset - SANTA_WIDTH - 10;  // Start off-screen on the left
    santaTimer = millis();
  }
  
  if (santaVisible) {
    int santaY = yOffset + 15;
    santaX++;  // Move right instead of left
    
    // Draw sleigh first (now behind)
    int sleighX = santaX;  // Base position
    u8g2.drawLine(sleighX, santaY, sleighX + 8, santaY);     // Base
    u8g2.drawLine(sleighX, santaY, sleighX + 2, santaY - 2); // Front curve
    u8g2.drawLine(sleighX + 8, santaY, sleighX + 6, santaY - 2); // Back curve
    
    // Draw Santa in sleigh
    u8g2.drawBox(sleighX + 3, santaY - 5, 4, 5);    // Body
    u8g2.drawDisc(sleighX + 5, santaY - 6, 1);      // Head
    // Santa's hat
    u8g2.drawLine(sleighX + 4, santaY - 7, sleighX + 6, santaY - 7);
    u8g2.drawPixel(sleighX + 6, santaY - 8);
    
    // Draw reindeer in front
    int deerX = sleighX + 10;  // Position reindeer in front of sleigh
    int deerY = santaY - 2;
    
    // Draw harness connecting to sleigh
    u8g2.drawLine(sleighX + 8, santaY - 1, deerX, deerY);
    
    // Reindeer body
    u8g2.drawLine(deerX, deerY, deerX + 6, deerY);
    // Legs (animated)
    int legOffset = ((santaX / 2) % 2) ? 1 : 0;  // Alternate leg positions
    u8g2.drawLine(deerX + 1, deerY, deerX + 1, deerY + 2 + legOffset);
    u8g2.drawLine(deerX + 4, deerY, deerX + 4, deerY + 2 + !legOffset);
    
    // Reindeer head and antlers
    u8g2.drawLine(deerX + 6, deerY, deerX + 8, deerY - 2); // Neck
    u8g2.drawDisc(deerX + 8, deerY - 2, 1);  // Head
    u8g2.drawPixel(deerX + 9, deerY - 3);    // Nose (Rudolph!)
    // Antlers
    u8g2.drawLine(deerX + 8, deerY - 3, deerX + 7, deerY - 4);
    u8g2.drawLine(deerX + 8, deerY - 3, deerX + 9, deerY - 4);
    
    // Reset when completely off screen (right side)
    if (santaX > xOffset + width + 10) {
      santaVisible = false;
    }
  }
}

// Add this new function
void drawFireplace() {
    int fireX = xOffset + width - 15;
    int fireY = yOffset + height - 5;
    
    // Draw chimney
    u8g2.drawBox(fireX - 4, fireY - 8, 8, 8);
    
    // Animate flames every 100ms
    if (millis() - flameTimer > 100) {
        flamePattern = random(0, 4);
        flameTimer = millis();
    }
    
    // Draw animated flames
    for (int i = 0; i < FLAME_HEIGHT; i++) {
        int flameWidth = max(1, 3 - i);
        int xOffset = (flamePattern + i) % 2;
        u8g2.drawHLine(fireX - flameWidth/2 + xOffset, fireY - 8 - i, flameWidth);
    }
}

// Modify updateSnow() to updateWeather()
void updateWeather() {
    // Change weather every 10 seconds
    if (millis() - weatherTimer > 10000) {
        currentWeather = (Weather)((currentWeather + 1) % 3);
        weatherTimer = millis();
    }
    
    switch(currentWeather) {
        case SNOW:
            updateSnow();
            break;
        case RAIN:
            // Draw rain drops as vertical lines
            for (int i = 0; i < NUM_SNOWFLAKES; i++) {
                u8g2.drawVLine(snowflakes[i].x, snowflakes[i].y, 2);
                snowflakes[i].y += 2;
                if (snowflakes[i].y > yOffset + height) {
                    snowflakes[i].y = yOffset;
                    snowflakes[i].x = random(xOffset, xOffset + width);
                }
            }
            break;
        case CLEAR:
            // Draw stars
            for (int i = 0; i < 5; i++) {
                int x = xOffset + (width * i / 4);
                int y = yOffset + 5 + (i % 2) * 3;
                u8g2.drawPixel(x, y);
            }
            break;
    }
}

// Add this function
void updateDayNight() {
    if (millis() - dayNightTimer > DAY_NIGHT_DURATION) {
        isNightTime = !isNightTime;
        dayNightTimer = millis();
    }
    
    if (!isNightTime) {
        // Draw sun instead of moon
        int sunX = xOffset + 6;
        int sunY = yOffset + 6;
        u8g2.drawCircle(sunX, sunY, 3);
        // Draw rays
        for (int i = 0; i < 4; i++) {
            u8g2.drawPixel(sunX + 4*cos(i*PI/2), sunY + 4*sin(i*PI/2));
        }
    } else {
        drawMoon();
    }
}

// Add this function
void updateScene() {
    if (millis() - sceneTimer > SCENE_DURATION) {
        currentScene = (currentScene + 1) % 4; // Cycle through 4 scenes
        sceneTimer = millis();
    }
    
    switch(currentScene) {
        case 0: // Christmas scene
            drawTree();
            drawStar();
            drawSnowman();
            drawPresents();
            break;
        case 1: // Santa scene
            drawSanta();
            updateWeather();
            break;
        case 2: // Fireplace scene
            drawFireplace();
            drawPresents();
            break;
        case 3: // Weather scene
            updateWeather();
            drawMoon();
            break;
    }
    
    // Always show scrolling text
    drawScrollingText();
}

void setup(void) {
  Serial.begin(115200);
  delay(1000);
  
  u8g2.begin();
  u8g2.setContrast(255);
  u8g2.setBusClock(400000);
  
  // Initialize random seed
  randomSeed(analogRead(0));
  initSnowflakes();
  
  Serial.println("Christmas Demo initialized");
}

void loop(void) {
    u8g2.clearBuffer();
    
    // Draw frame
    u8g2.drawFrame(xOffset, yOffset, width, height);
    
    updateDayNight();  // Keep day/night cycle
    updateScene();     // Draw current scene
    
    u8g2.sendBuffer();
    delay(50);
} 