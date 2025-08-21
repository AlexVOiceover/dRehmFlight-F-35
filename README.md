# dRehmFlight F-35 VTOL - PlatformIO Port

PlatformIO port of the dRehmFlight F-35 Lightning II inspired VTOL tricopter flight controller.

## Project Overview

This is a specialized flight controller for an F-35 tricopter VTOL (Vertical Take-Off and Landing) vehicle based on the Teensy 4.0 microcontroller. The project has been converted from Arduino IDE to PlatformIO for better development workflow and dependency management.

**Original Project**: [dRehmFlight F-35](https://github.com/nickrehm/dRehmFlight-F-35)  
**Author**: Nicholas Rehm, University of Maryland

## Hardware Configuration

### F-35 VTOL Specific Hardware (Current Configuration)
- **Flight Controller**: Teensy 4.0 microcontroller
- **IMU**: GY-521 MPU6050 6DOF IMU
- **Radio**: Matek ELRS R24-P6V PWM receiver (ExpressLRS 2.4GHz)
- **Motors**: 3x 2306 brushless motors (~2450 KV)
- **ESC**: iFlight BLITZ E55S 4-in-1 ESC (OneShot125 protocol)
- **Servos**: 5x SG90 micro servos for control surfaces
- **Power**: 4S LiPo battery with WANGCL 5V/3A UBEC

### Pin Assignments
```
Radio (PWM):
- CH1 (Throttle) → Pin 15
- CH2 (Aileron)  → Pin 16  
- CH3 (Elevator) → Pin 17
- CH4 (Rudder)   → Pin 20
- CH5 (Gear)     → Pin 21
- CH6 (Aux1)     → Pin 22

IMU (I2C):
- MPU6050 SDA → Pin 18
- MPU6050 SCL → Pin 19

Motors (OneShot125):
- M1 (Nose)  → Pin 0
- M2 (Right) → Pin 1  
- M3 (Left)  → Pin 2

Servos:
- S1-S7 → Various pins for control surfaces
```

## Development Setup

### Prerequisites
- [PlatformIO Core](https://platformio.org/install/cli) or [PlatformIO IDE](https://platformio.org/install/ide)
- [Visual Studio Code](https://code.visualstudio.com/) (recommended)

### Building the Project
```bash
# Build the project
pio run

# Upload to Teensy 4.0
pio run --target upload

# Monitor serial output
pio device monitor --baud 115200
```

### Hardware Configuration Options

The flight controller supports multiple hardware configurations through `platformio.ini` build flags:

#### Current F-35 Configuration
```ini
build_flags = 
    -DUSE_PWM_RX          # PWM receiver
    -DUSE_MPU6050_I2C     # MPU6050 IMU
    -DGYRO_500DPS         # 500°/s gyro range
    -DACCEL_2G            # 2G accelerometer
```

#### Alternative Configurations
To use different hardware, modify the build flags in `platformio.ini`:

**Receiver Options:**
- `-DUSE_PWM_RX` - PWM receiver (current)
- `-DUSE_PPM_RX` - PPM receiver  
- `-DUSE_SBUS_RX` - SBUS receiver

**IMU Options:**
- `-DUSE_MPU6050_I2C` - MPU6050 via I2C (current)
- `-DUSE_MPU9250_SPI` - MPU9250 via SPI

**Gyro Range:**
- `-DGYRO_250DPS` - 250°/s
- `-DGYRO_500DPS` - 500°/s (current)
- `-DGYRO_1000DPS` - 1000°/s
- `-DGYRO_2000DPS` - 2000°/s

**Accelerometer Range:**
- `-DACCEL_2G` - 2G (current)
- `-DACCEL_4G` - 4G
- `-DACCEL_8G` - 8G
- `-DACCEL_16G` - 16G

## Flight Modes

The F-35 VTOL controller features three distinct flight modes:

1. **Hover Mode** (CH6 > 1700): Standard multicopter hover control
2. **Transition Mode** (1300 < CH6 < 1700): Gradual transition between hover and forward flight
3. **Forward Flight** (CH6 < 1300): Airplane-like forward flight with elevon control

## Control Features

- **Thrust Vectoring**: Rear tilt servo for yaw control
- **Elevon Control**: Wing control surfaces for pitch/roll in forward flight
- **Flight Mode Switching**: Dynamic PID gains and control limits per mode
- **Smooth Transitions**: Gradual motor mixing during mode changes

## Debugging

Enable debug output by uncommenting print functions in the main loop:
- `printRadioData()` - Radio PWM values
- `printGyroData()` - IMU gyro data
- `printServoCommands()` - Servo positions
- `printMotorCommands()` - Motor commands
- `printLoopRate()` - Control loop timing

## Safety

⚠️ **IMPORTANT SAFETY NOTES**
- This is experimental flight controller software
- Always test thoroughly on the bench before flight
- Use appropriate safety measures and failsafes
- Follow all local regulations for RC aircraft operation
- Never fly over people or property

## License

This code is entirely free to use. See `COPYING.txt` for license details.

## Credits

- **Original Author**: Nicholas Rehm (nrehm@umd.edu)
- **Institution**: University of Maryland, Department of Aerospace Engineering
- **PlatformIO Port**: Community contribution

## Support

- [Original dRehmFlight Repository](https://github.com/nickrehm/dRehmFlight)
- [RC Groups Support Thread](https://www.rcgroups.com/forums/showthread.php?3706571-dRehmFlight-VTOL-Teensy-Flight-Controller-and-Stabilization)
- [F-35 Tutorial Video](https://www.youtube.com/watch?v=RqdcZD0ZoUk)