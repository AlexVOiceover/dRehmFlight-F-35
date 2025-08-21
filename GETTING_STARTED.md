# Getting Started with PlatformIO

## Opening the Project in VS Code

1. **Open VS Code** and make sure the PlatformIO extension is installed and enabled

2. **Open the project folder**:
   - File → Open Folder
   - Navigate to `dRehmFlight-F35-PlatformIO/`
   - Click "Select Folder"

3. **Wait for PlatformIO to initialize**:
   - You'll see PlatformIO initializing in the status bar
   - Wait for intelliSense indexing to complete

## Building and Testing

### Using the VS Code PlatformIO Extension

1. **Build the project**:
   - Click the checkmark (✓) in the PlatformIO toolbar at the bottom
   - Or use Ctrl+Alt+B
   - Or open Command Palette (Ctrl+Shift+P) → "PlatformIO: Build"

2. **Upload to Teensy 4.0**:
   - Connect your Teensy 4.0 via USB
   - Click the arrow (→) in the PlatformIO toolbar
   - Or use Command Palette → "PlatformIO: Upload"

3. **Serial Monitor**:
   - Click the plug icon in the PlatformIO toolbar
   - Or use Command Palette → "PlatformIO: Serial Monitor"
   - Baud rate is set to 115200

### Using PlatformIO Core Commands (if available)

If you have PlatformIO Core installed, you can also use terminal commands:

```bash
# Build
pio run

# Upload  
pio run --target upload

# Serial monitor
pio device monitor --baud 115200

# Clean build
pio run --target clean
```

## Project Structure Overview

```
dRehmFlight-F35-PlatformIO/
├── platformio.ini          # PlatformIO configuration
├── src/
│   ├── main.cpp            # Main flight controller code
│   └── radioComm.cpp       # Radio communication functions
├── include/
│   ├── main.h              # Main function declarations
│   └── radioComm.h         # Radio function declarations
├── lib/
│   ├── MPU6050/           # MPU6050 IMU library
│   ├── MPU9250/           # MPU9250 IMU library (alternative)
│   └── SBUS/              # SBUS receiver library (alternative)
└── docs/                  # Hardware and wiring documentation
```

## Hardware Configuration

Current F-35 VTOL configuration is set in `platformio.ini`:
- **Receiver**: PWM (Matek ELRS R24-P6V)
- **IMU**: MPU6050 via I2C
- **Gyro Range**: 500°/s
- **Accelerometer**: 2G

To change hardware, modify the `build_flags` in `platformio.ini`.

## Troubleshooting

### Build Errors
1. Make sure all libraries are in the `lib/` directory
2. Check that all `#include` statements are correct
3. Verify `platformio.ini` configuration matches your hardware

### Upload Issues
1. Ensure Teensy 4.0 is connected and drivers are installed
2. Close any serial monitors before uploading
3. Press the reset button on Teensy if upload fails

### Serial Monitor Issues
1. Make sure the correct port is selected
2. Verify baud rate is set to 115200
3. Close other applications using the serial port

## Next Steps

1. **Test Build**: Build the project to verify everything compiles
2. **Hardware Check**: Verify all pin connections match `docs/wiring.md`
3. **Bench Test**: Upload and test basic functionality without propellers
4. **Calibration**: Run IMU calibration and radio setup
5. **Flight Test**: Only after thorough bench testing

## Debug Output

To enable debug output, uncomment the desired print functions in `main.cpp`:
- `printRadioData()` - Radio PWM values
- `printGyroData()` - IMU sensor data  
- `printServoCommands()` - Servo positions
- `printMotorCommands()` - Motor commands
- `printLoopRate()` - Control loop timing

**Happy Flying! 🚁**