# Wiring Diagram - F-35 TRICOPTER VTOL

## Matek ELRS R24-P6V to Teensy 4.0 Wiring

### Power Connections
- R24-P6V **VCC** → Teensy **5V** (or 3.3V if using 3.3V power)
- R24-P6V **GND** → Teensy **GND**

### PWM Signal Connections
- R24-P6V **CH1** → Teensy **Pin 15** (Throttle)
- R24-P6V **CH2** → Teensy **Pin 16** (Aileron)  
- R24-P6V **CH3** → Teensy **Pin 17** (Elevator)
- R24-P6V **CH4** → Teensy **Pin 20** (Rudder)
- R24-P6V **CH5** → Teensy **Pin 21** (Gear/Throttle Cut)
- R24-P6V **CH6** → Teensy **Pin 22** (Aux1)

### Important Notes
- The flight controller is configured for `USE_PWM_RX` mode
- Pins 18 and 19 are reserved for MPU6050 I2C communication (SDA/SCL)
- Pin 13 is reserved for onboard LED
- The receiver outputs standard PWM signals (1000-2000μs pulse width)
- This setup provides 6-channel control for the F-35 tricopter VTOL with ExpressLRS

## MPU6050 IMU to Teensy 4.0 Wiring

### I2C Connections
- MPU6050 **VCC** → Teensy **3.3V**
- MPU6050 **GND** → Teensy **GND**
- MPU6050 **SDA** → Teensy **Pin 18** (SDA)
- MPU6050 **SCL** → Teensy **Pin 19** (SCL)

### Important Notes
- The flight controller is configured for `USE_MPU6050_I2C` mode
- No additional pullup resistors needed (Teensy has internal pullups)
- MPU6050 operates at 3.3V logic level

## iFlight BLITZ E55S 4-in-1 ESC to Teensy 4.0 Wiring

### Motor Signal Connections (OneShot125 Protocol)
- ESC **M1** signal → Teensy **Pin 0** (m1Pin)
- ESC **M2** signal → Teensy **Pin 1** (m2Pin)  
- ESC **M3** signal → Teensy **Pin 2** (m3Pin)
- ESC **M4** signal → Unused (tricopter uses only 3 motors)

### Power Connections
- ESC **GND** → Teensy **GND**
- ESC **BAT+** → 4S LiPo **Positive**
- ESC **BAT-** → 4S LiPo **Negative**

### ESC Configuration
- **Protocol:** OneShot125 (125-250μs pulse width)
- **Voltage:** 4S LiPo (14.8V nominal, 16.8V fully charged)
- **Current:** 55A continuous, 65A burst per channel
- **BEC Output:** None (typical for 4-in-1 ESCs)

## Power Supply - WANGCL 5V/3A UBEC

### UBEC Power Distribution
- 4S LiPo **BAT+** → UBEC **Input +** (5.5V-26V range)
- 4S LiPo **BAT-** → UBEC **Input -**
- UBEC **5V Output** → Teensy **VIN**
- UBEC **GND** → Teensy **GND**

### Components Powered by UBEC (5V)
- **Teensy 4.0** flight controller (~100mA)
- **MPU6050** IMU (~5mA) 
- **Matek R24-P6V** receiver (~50mA)
- **5x SG90 servos** (~200mA each, 1000mA total under load)
- **Total current draw**: ~1.2A typical, 1.5A max

### UBEC Specifications
- **Model**: WANGCL RC Receiver Power Switch
- **Input**: 5.5V-26V (supports 2-6S LiPo)
- **Output**: 5V/3A regulated
- **Protections**: Over-current, over-temperature, reverse polarity
- **Dimensions**: 43x17x7mm
- **EMI Shielding**: Reduces interference

### Alternative: USB Power (Testing Only)
- USB cable → Teensy (for bench testing only)
- Not suitable for actual flight

### Reserved Pins Summary
- **Pin 13:** Onboard LED (reserved)
- **Pin 18:** MPU6050 SDA (I2C)
- **Pin 19:** MPU6050 SCL (I2C)
- **Pins 0-2:** Motor/ESC outputs (m1Pin through m3Pin for tricopter)
- **Pins 3-5:** Available for servos/additional actuators