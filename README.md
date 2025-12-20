# Wemos Filament Turner Controller

A firmware for controlling a filament turner using a Wemos D1 clone, 28BYJ-48 stepper motor, and ULN2003AN driver. The device rotates 180 degrees every 30 minutes automatically.

## Features

- ✅ Automatic 360° rotation every 30 minutes
- ✅ Immediate startup rotation
- ✅ Smooth half-step motor control
- ✅ Low power coil de-energization
- ✅ Serial monitoring for debugging

## Hardware Requirements

- **Microcontroller:** Wemos D1 R1 (or compatible D1 clone)
- **Motor:** 28BYJ-48 stepper motor (5V)
- **Driver:** ULN2003AN Darlington Array
- **Power:** 5V power supply

## Wiring Diagram

```
Wemos D1          ULN2003AN         28BYJ-48
---------         ----------        --------
D1 (GPIO5)  ----> IN1
D2 (GPIO4)  ----> IN2
D3 (GPIO0)  ----> IN3
D4 (GPIO2)  ----> IN4
GND         ----> GND
5V          ----> 5V       ----> Motor Power
                          ----> Common (A, B, C, D coils)
```

## Installation

### Option 1: Web Flasher (Easiest)
1. Visit the [download page](https://mybesttools.github.io/Wemos-Filament-Turner/)
2. Click "Flash Firmware"
3. Select your USB port and click "Connect"
4. Wait for upload to complete

### Option 2: PlatformIO
1. Clone this repository
2. Install [VS Code](https://code.visualstudio.com/) and [PlatformIO Extension](https://platformio.org/)
3. Open the project folder
4. Connect Wemos D1 via USB
5. Click the upload button (→) in PlatformIO toolbar

### Option 3: Arduino IDE
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP8266 board: Preferences → Additional Boards Manager URLs → `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
3. Tools → Board Manager → Search "ESP8266" → Install
4. Open `Filament_Turner.ino`
5. Select Board: "WeMos D1 R1" and your USB port
6. Click Upload

## Configuration

Edit `src/main.cpp` to customize:

```cpp
#define STEPS_FOR_180 2048           // Steps for 180° rotation
#define DELAY_BETWEEN_STEPS 2        // Milliseconds (slower = more torque)
#define ROTATION_INTERVAL 30 * 60 * 1000  // Rotation interval (30 minutes)
```

## Monitoring

Open Serial Monitor at **115200 baud** to see:
- Startup messages
- Rotation events
- Completion status

## Project Structure

```
.
├── src/
│   └── main.cpp              # Main firmware code
├── docs/                     # GitHub Pages content
│   ├── index.html           # Web flasher interface
│   └── firmware/            # Binary files
├── platformio.ini           # PlatformIO configuration
└── README.md                # This file
```

## Troubleshooting

**Motor doesn't turn:**
- Check USB power supply is adequate (5V, ≥1A recommended)
- Verify pin connections match `src/main.cpp`
- Test with Serial Monitor to confirm code is running

**Upload fails:**
- Try different USB cable
- Hold GPIO0 to GND while plugging in USB for boot mode
- Check COM port selection matches your device

**Rotation incomplete:**
- Increase `DELAY_BETWEEN_STEPS` (slower = more reliable)
- Check power supply voltage under load

## License

MIT License

## Author

Created with Platform IO
