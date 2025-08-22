# F-35 VTOL Radio Troubleshooting Log

## Issue Summary
**Problem**: Matek ELRS R24-P6V receiver not providing valid radio channel data to Teensy 4.0 flight controller
**Date**: August 21, 2025
**Hardware**: F-35 VTOL Tricopter with Teensy 4.0, MPU6050 IMU, ELRS R24-P6V receiver

## Hardware Configuration
- **Flight Controller**: Teensy 4.0 microcontroller
- **Receiver**: Matek ELRS R24-P6V PWM/SBUS capable
- **Radio**: ExpressLRS transmitter (confirmed working - telemetry functional)
- **Original Setup**: PWM on 6 individual pins (15, 16, 17, 20, 21, 22)
- **Target Setup**: SBUS on single Serial5 connection (pin 21)

## Troubleshooting Timeline

### Initial Problem Discovery
**Issue**: PWM signals reading 0.24V instead of expected 3.3V logic levels
- **Measured**: R24 PWM outputs with multimeter = 0.24V
- **Expected**: 3.3V logic levels for reliable Teensy 4.0 input detection
- **Diagnosis**: Voltage too low for reliable digital input (VIH ~2.0V minimum)

### Root Cause Analysis
**Discovery**: R24 configured for CRSF protocol, not PWM
- **ELRS Configurator showed**: Serial Protocol = CRSF
- **Problem**: CRSF is digital serial protocol, not PWM analog
- **Explanation**: 0.24V readings were digital CRSF data, not PWM signals

### Migration to SBUS Protocol

#### Code Changes Made
1. **Updated platformio.ini**:
   ```ini
   # Changed from:
   -DUSE_PWM_RX          # PWM receiver
   # To:
   -DUSE_SBUS_RX         # SBUS receiver
   ```

2. **Modified main.cpp**:
   - Commented out PWM pin definitions (pins 15-22)
   - Added SBUS library includes and variables
   - Updated `getCommands()` function for SBUS reading
   - Enhanced `printRadioData()` for SBUS debugging

3. **Updated radioComm.cpp**:
   - Commented out PWM interrupt handlers
   - Added SBUS initialization in `radioSetup()`
   - Modified `getRadioPWM()` to convert SBUS to PWM-like values

#### Physical Wiring Change
- **Removed**: 6 PWM wires from pins 15, 16, 17, 20, 21, 22
- **Added**: Single wire from R24 Output 1 pad → Teensy pin 21 (Serial5 RX)
- **Retained**: Power (VCC/GND) connections

### SBUS Protocol Testing

#### Test 1: CRSF Protocol (Initial R24 Configuration)
**Configuration**: R24 Serial Protocol = CRSF
**Results**:
```
Serial5_Avail:63 RawBytes:0x0 0x0 0x0 0x0 0x0
NewFrame:N FS:N Lost:N
```
**Analysis**: 
- ✅ Data flowing (63 bytes received)
- ❌ All bytes are zeros (0x0)
- ❌ SBUS library cannot parse CRSF frames

#### Test 2: SBUS Protocol
**Configuration**: R24 Serial Protocol = SBUS
**Results**:
```
Serial5_Avail:0 RawBytes: NewFrame:N FS:N Lost:N
```
**Analysis**:
- ❌ No data received
- ❌ SBUS protocol not supported or configured incorrectly

#### Test 3: Inverted SBUS Protocol
**Configuration**: R24 Serial Protocol = Inverted SBUS
**Results**:
```
Serial5_Avail:0 RawBytes: NewFrame:N FS:N Lost:N
```
**Analysis**:
- ❌ No data received
- ❌ Inverted SBUS not working

#### Test 4: Return to SBUS Protocol (Verification)
**Configuration**: R24 Serial Protocol = SBUS (reverted from Inverted)
**Results**:
```
Serial5_Avail:63 RawBytes:0x0 0x0 0x0 0x0 0x0
NewFrame:N FS:N Lost:N
```
**Analysis**:
- ✅ Data flowing again (63 bytes)
- ❌ Still all zeros
- ❌ Pattern suggests hardware/signal issue

#### Test 5: Return to CRSF Protocol (Final Test)
**Configuration**: R24 Serial Protocol = CRSF
**Results**:
```
Serial5_Avail:63 RawBytes:0x0 0x0 0x0 0x0 0x0
NewFrame:N FS:N Lost:N
```
**Analysis**:
- ✅ Data flowing consistently (63 bytes)
- ❌ All bytes remain zeros
- ❌ Signal/hardware issue confirmed

## Current Status: UNRESOLVED

### Confirmed Working
- ✅ **Code compilation**: All SBUS modifications build successfully
- ✅ **Radio link**: ExpressLRS telemetry working (transmitter ↔ R24 communication verified)
- ✅ **Data flow**: Serial5.available() shows bytes being received
- ✅ **Wiring continuity**: Teensy receiving serial data from R24

### Identified Problems
- ❌ **All received bytes are 0x00**: No valid protocol data
- ❌ **SBUS library parsing**: Cannot decode frames (NewFrame:N)
- ❌ **Protocol mismatch**: SBUS library cannot parse CRSF, CRSF library not implemented

### Potential Root Causes

#### 1. Hardware/Signal Issues (Most Likely)
- **Wrong R24 output pad**: Connected to GND, VCC, or non-functional pin
- **Signal level incompatibility**: R24 output voltage incompatible with Teensy input
- **Ground loop**: Poor ground connection causing signal corruption
- **Physical connection**: Loose wire, cold solder joint, or incorrect pin

#### 2. R24 Configuration Issues
- **Output mapping**: Output 1 pad might not be the serial output
- **Protocol support**: R24-P6V might have limited SBUS support
- **Firmware compatibility**: ELRS firmware version might not support selected protocols properly

#### 3. R24 Hardware Limitations
- **Limited protocol support**: Some ELRS receivers don't support all protocols
- **Pad functionality**: Output pads might be configured for PWM only
- **Version differences**: Different R24 variants have different capabilities

## Debug Output Evolution

### Initial Debug (10ms intervals - too frequent)
```
[SBUS] CH1:1000 CH2:1500 CH3:1500 CH4:1500 CH5:2000 CH6:2000 |FS:N Lost:N
```

### Enhanced Debug (Added raw data and serial status)
```
[SBUS] RAW: CH1:0 CH2:0 CH3:0 CH4:0 CH5:0 CH6:0 | PWM: CH1:1000 CH2:1500 CH3:1500 CH4:1500 CH5:2000 CH6:2000 | Status: FS:N Lost:N Serial5_Avail:63 RawBytes:0x0 0x0 0x0 0x0 0x0 NewFrame:N
```

### Current Debug (1-second intervals - readable)
```
[SBUS] RAW: CH1:0 CH2:0 CH3:0 CH4:0 CH5:0 CH6:0 | PWM: CH1:1000 CH2:1500 CH3:1500 CH4:1500 CH5:2000 CH6:2000 | Status: FS:N Lost:N Serial5_Avail:63 RawBytes:0x0 0x0 0x0 0x0 0x0 NewFrame:N
```

## Recommended Next Steps

### Immediate Actions
1. **Verify physical connections**:
   - Use multimeter to confirm R24 Output 1 pad → Teensy pin 21 continuity
   - Check voltage levels on R24 Output 1 pad with oscilloscope/multimeter
   - Verify ground connection integrity

2. **Test alternative R24 outputs**:
   - Try connecting Output 2 (TX) pad to Teensy pin 21
   - Try connecting Output 3 (RX) pad to Teensy pin 21
   - Configure all R24 outputs to Serial2 and test each

3. **R24 configuration verification**:
   - Set ALL outputs (1-6) to `Serial2` in ELRS Configurator
   - Test each output pad individually
   - Try different ELRS firmware versions if available

### Alternative Solutions
1. **Implement CRSF protocol support**:
   - Since CRSF consistently shows data availability, implement CRSF parsing
   - CRSF offers better performance than SBUS (faster updates, more channels)
   - Requires custom protocol implementation

2. **Return to PWM with signal conditioning**:
   - Add signal level translation (0.24V → 3.3V)
   - Use op-amp or logic level converter
   - More complex but proven to work

3. **Different receiver**:
   - Try SBUS-native receiver (FrSky, FlySky, etc.)
   - Verify R24-P6V model specifications for protocol support

## Lessons Learned
1. **Protocol verification crucial**: Always verify receiver output protocol matches flight controller expectations
2. **Signal level validation**: Check electrical compatibility before assuming digital compatibility
3. **Debug output evolution**: Start simple, add detail progressively to avoid information overload
4. **Hardware documentation**: ELRS receiver capabilities vary significantly between models

## Code Rollback Instructions
If needed to return to PWM configuration:

1. **Revert platformio.ini**:
   ```ini
   -DUSE_PWM_RX          # Uncomment
   # -DUSE_SBUS_RX       # Comment out
   ```

2. **Restore main.cpp**:
   - Uncomment PWM pin definitions
   - Remove SBUS includes and variables

3. **Restore radioComm.cpp**:
   - Uncomment PWM interrupt handlers
   - Remove SBUS code

4. **Physical wiring**:
   - Reconnect 6 PWM wires to pins 15-22
   - Remove single SBUS wire from pin 21

---
*Troubleshooting log maintained during F-35 VTOL development*
*Last updated: August 21, 2025*