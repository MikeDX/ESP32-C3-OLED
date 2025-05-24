# ESP32-C3 Christmas OLED Animation System

A festive, feature-rich Christmas animation project for ESP32 microcontrollers with SSD1306 OLED displays. This project showcases advanced animation techniques, modular code architecture, and professional embedded systems practices.

## ✨ Features

### 🎄 Animation Scenes
- **Christmas Tree Scene**: Animated twinkling star, decorated tree, moving snowman
- **Santa's Sleigh**: Flying Santa with reindeer across the screen
- **Fireplace Scene**: Flickering flames with presents
- **Weather Display**: Dynamic weather effects with day/night cycle

### 🌨️ Dynamic Effects
- **Weather System**: Snow, rain, and clear sky with particle effects
- **Day/Night Cycle**: Automatic sun/moon transitions
- **Smooth Animations**: Professional easing and interpolation
- **Particle System**: Efficient weather particles and effects

### 🛠️ Technical Features
- **Modular Architecture**: Clean separation of concerns
- **Memory Monitoring**: Real-time heap usage tracking
- **Performance Monitoring**: Frame rate and timing analysis
- **Error Handling**: Comprehensive error reporting and recovery
- **Configurable Parameters**: Easy customization via config files

## 📋 Hardware Requirements

### 🛒 Ready-to-Use Board (Recommended)
For the easiest setup, you can purchase a pre-built ESP32-C3 development board with integrated 0.42" OLED display:

**ESP32-C3 OLED Development Board**
- **Where to buy**: [AliExpress - ESP32-C3 OLED Board](https://www.aliexpress.com/item/1005007342383107.html)
- **Features**: ESP32-C3 supermini with built-in 0.42" OLED, ceramic antenna, WiFi & Bluetooth
- **Advantages**: No wiring required, compact form factor, plug-and-play setup

> 💡 **Note**: While we don't currently have an affiliate partnership, this link helps you find the exact board this project was designed for. Most users discover this repository after purchasing the board!

#### 📋 Detailed Specifications
- **MCU**: ESP32-C3FN4/FH4 with 4MB Flash
- **Connectivity**: WiFi & Bluetooth with ceramic antenna
- **Display**: 0.42″ OLED with 72×40 pixel animation area
- **Programming**: USB download support
- **Power**: USB-C connection

#### ⚠️ **Important Technical Note**
This project uses a **72×40 pixel animation area** centered on the display. All the Christmas scenes, animations, and effects are designed for this area. The display driver handles the technical details automatically.

If you're using a different 0.42″ OLED display and the animations appear off-center, you may need to adjust the `SCREEN_WIDTH` constant in `config.h`.

#### 🔧 **Real User Experiences & Tips**
Based on feedback from actual AliExpress buyers, here are important setup notes:

**✅ Working U8g2 Constructors:**
```cpp
// Option 1: Direct 72x40 support (recommended)
U8G2_SH1106_72X40_WISE_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 6, 5);

// Option 2: Alternative 72x40 
U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 6, 5);

// Option 3: Standard 128x64 with manual offsets
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 6, 5);
// Then use offsets: xOffset = 28-30, yOffset = 12
```

**⚠️ Common Issues & Solutions:**
- **Low brightness**: Set `u8g2.setContrast(255);` for maximum brightness
- **Poor WiFi**: Antenna is close to display - expected ~20% weaker signal
- **Arduino IDE**: Select "ESP32C3 Dev Module" as board type
- **Misaligned overlay**: Cosmetic only, doesn't affect functionality

**🔌 Confirmed Pin Layout:**
- **I2C**: SCL=6, SDA=5 (confirmed by multiple users)
- **Blue LED**: Pin 8
- **Boot Button**: Pin 9
- **Power**: ~200mA @ 5V via USB-C

### 🔧 DIY Component Assembly
Alternatively, you can build your own setup with individual components:

| Component | Specification | Notes |
|-----------|---------------|-------|
| **MCU** | ESP32-C3 (or compatible) | ESP32, ESP32-S2, ESP32-S3 also supported |
| **Display** | SSD1306 128x64 OLED | I2C interface, 0.42" to 1.3" supported |
| **Power** | 3.3V/5V | Via USB or external supply |

### 🔌 Wiring Diagram (DIY Setup Only)

*Note: If using the integrated AliExpress board, no wiring is needed!*

```
ESP32-C3    <->    SSD1306 OLED
--------          --------------
GPIO6 (SDA)  <->  SDA
GPIO5 (SCL)  <->  SCL
3.3V         <->  VCC
GND          <->  GND
```

## 🚀 Quick Start

### Prerequisites
- [PlatformIO](https://platformio.org/) installed
- ESP32 board drivers installed
- USB cable for programming

### Installation
```bash
# Clone the repository
git clone https://github.com/MikeDX/ESP32-C3-OLED.git
cd ESP32-C3-OLED

# Open in PlatformIO (VSCode)
code .

# Or build/upload via command line
pio run -t upload
pio device monitor -b 115200
```

### Configuration
Edit `src/config.h` to customize:
```cpp
// Animation timing
constexpr unsigned long SCENE_DURATION = 5000;      // Scene change interval
constexpr unsigned long ANIMATION_FRAME_DELAY = 50; // Frame rate (20 FPS)

// Feature toggles
constexpr bool ENABLE_STAR_ANIMATION = true;
constexpr bool ENABLE_WEATHER_EFFECTS = true;
constexpr bool ENABLE_DAY_NIGHT_CYCLE = true;

// I2C pins (if different)
constexpr uint8_t I2C_SDA_PIN = 6;
constexpr uint8_t I2C_SCL_PIN = 5;
```

## 📁 Project Structure

```
ESP32-C3-OLED/
├── src/
│   ├── main.cpp              # Main application with Christmas animations
│   ├── config.h              # Configuration constants and parameters
│   ├── animation.h           # Animation system declarations
│   ├── AnimationManager.h    # Animation classes and utilities
│   └── DebugUtils.h          # Debug and monitoring utilities
├── .vscode/                  # VSCode configuration
├── .pio/                     # PlatformIO build files
├── platformio.ini            # PlatformIO configuration
├── .gitignore                # Git ignore rules
└── README.md                 # This file
```

## 🔧 Advanced Usage

**📝 Note**: This project is specifically optimized for the AliExpress ESP32-C3 OLED board and uses the `U8G2_SSD1306_128X64_NONAME_F_HW_I2C` constructor with calculated offsets. Based on user reviews, you may get better results with the direct `U8G2_SH1106_72X40_WISE_F_HW_I2C` constructor, but this project's approach works reliably across different board revisions.

### Performance Monitoring
Enable debug output to see performance metrics:
```cpp
// In config.h
constexpr bool ENABLE_SERIAL_DEBUG = true;
```

Monitor output shows:
- Average frame rate (FPS)
- Memory usage and leak detection
- Scene transition timing
- Error reporting

### Custom Animations
Extend the system by adding new scenes:

```cpp
// In main.cpp
enum Scene {
    SCENE_CHRISTMAS_TREE = 0,
    SCENE_SANTA_SLEIGH,
    SCENE_FIREPLACE,
    SCENE_WEATHER_DISPLAY,
    SCENE_YOUR_CUSTOM_SCENE,  // Add here
    SCENE_COUNT
};

void drawYourCustomScene() {
    // Your animation code here
}
```

### Memory Optimization
For constrained environments:
- Reduce `MAX_PARTICLES` in config.h
- Disable unused features via feature flags
- Use PROGMEM for large string constants

## 🐛 Troubleshooting

### Common Issues

| Problem | Cause | Solution |
|---------|--------|----------|
| Blank display | Wiring/I2C | Check connections, try different U8g2 constructor |
| Display too dark | Low contrast | Add `u8g2.setContrast(255);` in setup() |
| Animations off-center | Wrong display driver | Try `U8G2_SH1106_72X40_WISE_F_HW_I2C` constructor |
| Poor WiFi signal | Antenna near display | Expected behavior - signal ~20% weaker |
| Arduino IDE issues | Wrong board selection | Select "ESP32C3 Dev Module" |
| Memory errors | Heap exhaustion | Reduce `MAX_PARTICLES`, enable monitoring |
| Compilation errors | Missing dependencies | Run `pio lib install` |

### Alternative Firmware Options
This board works with multiple firmware options:

**🔸 Arduino IDE**
```cpp
// Minimal working example from user reviews
#include <U8g2lib.h>
#include <Wire.h>
U8G2_SH1106_72X40_WISE_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 6, 5);

void setup() {
  u8g2.begin();
  u8g2.setContrast(255);
  u8g2.setFont(u8g2_font_6x10_tf);
}

void loop() {
  u8g2.clearBuffer();
  u8g2.drawStr(0, 15, "Hello OLED");
  u8g2.sendBuffer();
  delay(1000);
}
```

**🔸 ESPHome**
```yaml
i2c:
  sda: 5
  scl: 6

display:
  - platform: ssd1306_i2c
    model: "SH1106 128x64"  # Use with offset compensation
    # Actual usable area: 72x40 with offset 28,12
```

**🔸 Tasmota**
Compatible with standard Tasmota firmware (confirmed by users).

**🔸 MicroPython**
```python
from machine import Pin, I2C
from sh1106 import SH1106_I2C

W,H = 72,40
X0,Y0 = 28,12
i2c = I2C(0, scl=Pin(6), sda=Pin(5), freq=400000)
oled = SH1106_I2C(X0+W, (Y0+H+7) & 0xf8, i2c, rotate=180)
```

## 📊 Performance Benchmarks

Typical performance on ESP32-C3:
- **Frame Rate**: 20 FPS (50ms per frame)
- **Memory Usage**: ~45KB heap (32 particles)
- **I2C Frequency**: 400kHz
- **Animation Smoothness**: 60+ interpolation steps

## 🤝 Contributing

We welcome contributions! Areas for improvement:
- Additional animation scenes
- New particle effects
- Performance optimizations
- Hardware support (different displays)
- Sound integration

### Development Setup
1. Fork the repository
2. Create a feature branch
3. Test on hardware
4. Submit a pull request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🎯 Future Enhancements

- [ ] WiFi connectivity for remote control
- [ ] Multiple display support
- [ ] Sound/music synchronization
- [ ] Mobile app companion
- [ ] Real-time weather integration
- [ ] Custom animation scripting

## 👨‍💻 Author

**MikeDX** - [GitHub Profile](https://github.com/MikeDX)

## 🙏 Acknowledgments

- [U8g2 Library](https://github.com/olikraus/u8g2) for excellent OLED support
- [PlatformIO](https://platformio.org/) for the development platform
- ESP32 community for hardware support and documentation

---

*Made with ❤️ for the maker community* 