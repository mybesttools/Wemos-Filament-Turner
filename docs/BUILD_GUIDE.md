# Filament Turner Controller - Build Guide

## ⚡ Features
- **720°/hour rotation** - Continuous smooth filament turner
- **Complete 360° every 30 minutes** - Full rotation cycle
- **5-minute intervals** - 60° increment per cycle
- **USB powered** - works with any 5V USB charger
- **Easy installation** - no soldering required (optional breadboard method, recommended to solder 6 wires for a clean setup)
- **Open source firmware** - customizable and upgradeable

---

## 📦 Bill of Materials (BOM)

### Essential Components
| Component | Quantity | Notes | Estimated Cost |
|-----------|----------|-------|-----------------|
| **Wemos D1 Mini (ESP8266)** | 1 | Clone is fine (~$1-3 on AliExpress) | $10 |
| **28BYJ-48 Stepper Motor** | 1 | 5V version with gearbox | $3 |
| **ULN2003AN Driver Board** | 1 | Usually comes with motor kit | $2 |
| **USB Micro-B Cable** | 1 | Any 5V USB charger or power bank | $3 |
| **Dupont Jumper Wires** | 8+ | Male-to-female (20cm) | $2 |

I suggest to solder it for in your final build.

**Total: ~$12** (less if you have spare cables)

### Optional
- Breadboard (optional for testing before final build)
- USB power supply (5V/2A recommended)

---

## 🛠️ Assembly Instructions

### Step 1: Identify Your Parts
1. **Wemos D1 Mini** - Small WiFi development board
2. **28BYJ-48 Motor** - Geared stepper motor with 4 coil wires (typically colored brown, orange, pink, yellow)
3. **ULN2003AN Board** - Darlington driver with 4 signal inputs (IN1-IN4) and motor connection terminals

### Step 2: Motor Rotation Direction
The firmware is configured to rotate **720°/hour** - one complete 360° rotation every 30 minutes. If you want to reverse the direction after assembly, swap any two motor coil wires.

### Step 3: Pin Connections
Connect the following Wemos D1 pins to the ULN2003AN driver board:

```
Wemos D1 Pin     ULN2003AN Input
─────────────────────────────────
D1 (GPIO5)  ──→  IN1
D2 (GPIO4)  ──→  IN2
D3 (GPIO0)  ──→  IN3
D4 (GPIO2)  ──→  IN4
GND         ──→  GND
5V          ──→  5V

### Step 3: Motor Connection
The ULN2003AN board has a 4-pin motor connector. Connect your 28BYJ-48 motor coils:
- **Motor wires** (any order, it determines rotation direction) → Motor terminals on ULN2003AN

### Step 4: Power Connection
- **Wemos Micro USB** → 5V USB Power supply/charger
- **ULN2003AN +5V** → Wemos **5V** pin (optional, but recommended for stable motor power)
- **ULN2003AN GND** → Wemos **GND** (required)

---

## 🔌 Wiring Diagram

```
┌──────────────────────────────────────────────────────┐
│         Wemos D1 Mini (ESP8266)                      │
│  [Micro USB] D1 D2 D3 D4                             │
│      ↓       ↓  ↓  ↓  ↓                              │
│     5V       ↓  ↓  ↓  ↓                              │
│   Charger    ↓  ↓  ↓  ↓                              │
│              ↓  ↓  ↓  ↓                              │
│   ┌──────────────────────────────────────┐           │
│   │  ULN2003AN Driver Board              │           │
│   │                                      │           │
│   │  IN1 IN2 IN3 IN4  [Motor Connector]  │           │
│   │  ←   ←   ←   ←         ↓↓↓↓          │           │
│   │                    28BYJ-48 Motor    │           │
│   │                    (rotates 60°      │           │
│   │                     every 5 min)     │           │
│   └──────────────────────────────────────┘           │
│        GND to GND connection required                │
│        5V  to 5V connection required                 │
└──────────────────────────────────────────────────────┘
```

---

## 💻 Firmware Installation

### Option 1: Web Flasher (Easiest for Most People)
1. Visit: **https://mybesttools.github.io/Wemos-Filament-Turner/**
2. Click **"Flash Firmware"**
3. Select your USB port and click **"Connect"**
4. Wait for upload to complete
5. Motor will rotate immediately!

### Option 2: Arduino IDE
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP8266 board support:
   - **Preferences** → **Additional Boards Manager URLs**
   - Add: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
   - **Tools** → **Board Manager** → Search "ESP8266" → **Install**
3. Download firmware from [GitHub](https://github.com/mybesttools/Wemos-Filament-Turner)
4. Open `Filament_Turner.ino`
5. **Tools** → **Board**: "WeMos D1 R1"
6. **Tools** → **Port**: Select your USB port
7. Click **Upload** (→ arrow)

### Option 3: PlatformIO (Recommended for Developers)
1. Install [VS Code](https://code.visualstudio.com/) + [PlatformIO Extension](https://platformio.org/)
2. Clone repo: `git clone https://github.com/mybesttools/Wemos-Filament-Turner.git`
3. Open folder in VS Code
4. Connect Wemos D1 via USB
5. Click **Upload** button in PlatformIO toolbar

---

## ✅ Verification

After flashing firmware:

1. **Motor rotates immediately** - The device will perform an initial rotation on startup
2. **Every 5 minutes** - Motor rotates 60° continuously
3. **Full 360° rotation** - Completed every 30 minutes (720°/hour)

### Serial Monitor Output (Optional)
To see detailed status, open Serial Monitor at **115200 baud**:
- "Filament Turner Started"
- "Rotating at 720°/hour (360° every 30 minutes)"
- "Performing initial rotation..."
- "Rotation complete"
- Then logs every 5 minutes

---

## 🔧 Customization

Edit `src/main.cpp` to customize:

```cpp
// Change rotation interval (in milliseconds)
#define ROTATION_INTERVAL 5 * 60 * 1000  // Currently 5 minutes

// Change steps per rotation
#define STEPS_FOR_60 679  // Currently 60° (679 steps out of 4076 total)

// Change motor speed (lower = slower & more torque)
#define DELAY_BETWEEN_STEPS 2  // Currently 2ms between steps
```

---

## 🐛 Troubleshooting

| Problem | Solution |
|---------|----------|
| **Motor doesn't turn** | • Check USB power supply (5V, ≥1A) • Verify pin connections • Check motor coil wires are seated |
| **Upload fails** | • Try different USB cable • Hold GPIO0 to GND while plugging in USB • Verify correct COM port selected |
| **Rotation is jerky** | • Increase `DELAY_BETWEEN_STEPS` (e.g., to 3-5ms) • Check power supply voltage under load |
| **Motor runs in wrong direction** | • Swap any two motor coil wires on the ULN2003AN board |
| **Partial rotation** | • Increase `DELAY_BETWEEN_STEPS` • Check USB power supply amperage |

---

## 📐 3D Printing Tips

This design works great with 3D printed brackets/mounts:
- Mount motor vertically to filament spool
- Print coupling to attach motor shaft to spool
- Check GitHub for STL files (coming soon!)

---

## 📚 Additional Resources

- **GitHub Repo**: https://github.com/mybesttools/Wemos-Filament-Turner
- **Wemos D1 Pinout**: https://www.wemos.cc/en/latest/d1/d1_mini_3.1.0.html
- **28BYJ-48 Specs**: 4076 steps/revolution, 1:64 gear ratio
- **ULN2003AN Datasheet**: https://www.ti.com/product/ULN2003A

---

## 🤝 Support

- Found a bug? Report on [GitHub Issues](https://github.com/mybesttools/Wemos-Filament-Turner/issues)
- Have an improvement? Submit a [Pull Request](https://github.com/mybesttools/Wemos-Filament-Turner/pulls)

---

**Happy Printing! 🎞️**
