# Hardware Checklist - F-35 Tricopter VTOL

## Flight Controller
- [x] **Teensy 4.0** microcontroller

## IMU/Sensors
- [x] **GY-521 MPU6050** 6DOF IMU

## Radio System (Modified from Original)
- [x] **Matek ELRS R24-P6V** PWM Vario receiver (ExpressLRS 2.4GHz)
- [x] **ExpressLRS transmitter** (compatible)

## Motors & Propulsion
- [x] **3x 2306 brushless motors** (~2450 KV)
  - Example: iFlight XING-E Pro 2306 (or similar)
- [x] **iFlight BLITZ E55S 4-IN-1 ESC** - 55A continuous, 65A burst per channel
  - **Voltage**: 2-6S LiPo support (14.8V-25.2V)
  - **Protocol Support**: OneShot125, DShot150/300/600, MultiShot
  - **Firmware**: BLHeli_S (Target: Q-H-25 16.7) + Bluejay available
  - **Configuration**: 4-in-1 design (will use 3 outputs for tricopter)
  - **Features**: Thermal management, integrated BEC, 30.5×30.5mm mounting
- [x] **3x 5-inch Propellers** for tricopter setup

## Control Surfaces
- [x] **5x SG90 micro servos** for control surfaces/thrust vectoring
- [x] **5x Servo control rods and horns** (one per servo)
  - Includes servo horns, control rods/pushrods

## Power System
- [x] **4S LiPo Battery** for flight power
  - Example: 4S LiPo Battery 2200mAh
  - Voltage: 14.8V nominal (16.8V fully charged)
  - Capacity: 2200mAh+ recommended for F-35 tricopter
  - C-rating: 25C+ for adequate current delivery
- [ ] **Power distribution board** for tricopter configuration
- ~~**5V regulator** for Teensy 4.0~~ (ESC BEC provides 5V @ 0.6A - sufficient)