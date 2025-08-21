# EdgeTX Radio Configuration - dRehmFlight F-35 VTOL

## Overview
This guide covers setting up a RadioMaster TX16S (EdgeTX) for the dRehmFlight F-35 VTOL project. The F-35 VTOL uses a unique 3-motor tricopter configuration with flight mode switching capabilities.

## Required Hardware
- **Radio**: RadioMaster TX16S with EdgeTX firmware
- **Receiver**: ExpressLRS 2.4GHz compatible (e.g., Matek ELRS R24-P6V PWM)
- **Flight Controller**: Teensy 4.0 with dRehmFlight F-35 firmware

## Channel Assignment

### Channel Functions
| Channel | Function | Stick/Switch | Range | Notes |
|---------|----------|--------------|-------|-------|
| CH1 | Throttle | Left Stick Vertical | 1000-2000 | Motor power control |
| CH2 | Aileron (Roll) | Right Stick Horizontal | 1000-2000 | Roll control |
| CH3 | Elevator (Pitch) | Right Stick Vertical | 1000-2000 | Pitch control |
| CH4 | Rudder (Yaw) | Left Stick Horizontal | 1000-2000 | Yaw control |
| CH5 | Throttle Cut | 3-Position Switch | 1000/1500/2000 | Motor arming/disarming |
| CH6 | Flight Mode | 3-Position Switch | 1000/1500/2000 | Hover/Transition/Forward Flight |

## EdgeTX Configuration Steps

### 1. Create New Model
1. **Power on TX16S** and navigate to **Model Selection**
2. **Create new model**: Press **[MENU]** → **Create model**
3. **Name**: `F35_VTOL`
4. **Type**: Select **Custom** or **Plane**

### 2. Model Setup Page
```
Model name: F35_VTOL
Model image: (optional)
Labels: VTOL, F-35
```

### 3. Inputs Configuration
Navigate to **INPUTS** page and configure:

**Input 1 - Throttle (I1)**
```
Name: Thr
Source: Thr (Left stick vertical)
Weight: 100%
Offset: 0
Min: -100
Max: 100
```

**Input 2 - Aileron (I2)**
```
Name: Ail
Source: Ail (Right stick horizontal)  
Weight: 100%
Offset: 0
Min: -100
Max: 100
```

**Input 3 - Elevator (I3)**
```
Name: Ele
Source: Ele (Right stick vertical)
Weight: 100%
Offset: 0
Min: -100
Max: 100
```

**Input 4 - Rudder (I4)**
```
Name: Rud
Source: Rud (Left stick horizontal)
Weight: 100%
Offset: 0
Min: -100
Max: 100
```

**Input 5 - Throttle Cut (I5)**
```
Name: TCut
Source: SA (3-position switch)
Weight: 100%
Offset: 0
```

**Input 6 - Flight Mode (I6)**
```
Name: FMode
Source: SB (3-position switch)  
Weight: 100%
Offset: 0
```

### 4. Mixes Configuration
Navigate to **MIXES** page:

**Mix 1 - Channel 1 (Throttle)**
```
Name: CH1
Source: Thr
Weight: 100%
Offset: 0%
Switch: !SA↑ (Throttle cut when SA up)
```

**Mix 2 - Channel 2 (Aileron)**
```
Name: CH2
Source: Ail
Weight: 100%
Offset: 0%
```

**Mix 3 - Channel 3 (Elevator)**
```
Name: CH3
Source: Ele
Weight: -100% (reverse if needed)
Offset: 0%
```

**Mix 4 - Channel 4 (Rudder)**
```
Name: CH4
Source: Rud  
Weight: 100%
Offset: 0%
```

**Mix 5 - Channel 5 (Throttle Cut)**
```
Name: CH5
Source: SA (3-position switch)
Weight: 100%
Offset: 0%
```

**Mix 6 - Channel 6 (Flight Mode)**
```
Name: CH6  
Source: SB (3-position switch)
Weight: 100%
Offset: 0%
```

### 5. Outputs Configuration
Navigate to **OUTPUTS** page and set ranges:

```
CH1 (Throttle):  Min: 1000  Center: 1500  Max: 2000
CH2 (Aileron):   Min: 1000  Center: 1500  Max: 2000  
CH3 (Elevator):  Min: 1000  Center: 1500  Max: 2000
CH4 (Rudder):    Min: 1000  Center: 1500  Max: 2000
CH5 (Gear):      Min: 1000  Center: 1500  Max: 2000
CH6 (Aux1):      Min: 1000  Center: 1500  Max: 2000
```

### 6. Flight Modes Setup

The F-35 VTOL uses **Channel 6** for flight mode switching:

| Switch Position | PWM Range | Flight Mode | Description |
|----------------|-----------|-------------|-------------|
| SB↑ (Up) | 1700-2000 | **Hover** | Multicopter-style hovering |
| SB- (Middle) | 1300-1700 | **Transition** | Gradual mode transition |
| SB↓ (Down) | 1000-1300 | **Forward Flight** | Airplane-style flight |

### 7. Switch Assignment Recommendations

**Physical Switch Layout:**
```
SA (3-pos): Throttle Cut/Arming
SB (3-pos): Flight Mode  
SC (2-pos): Auxiliary function
SD (2-pos): Auxiliary function
SE (2-pos): Auxiliary function
SF (momentary): Bind/Emergency
```

**Critical Switch Functions:**
- **SA**: Motor arming/disarming (SAFETY CRITICAL)
- **SB**: Flight mode selection (OPERATIONAL CRITICAL)

### 8. Servo/Motor Outputs

**F-35 VTOL Actuator Layout:**
```
M1 (Motor 1): Nose propeller - Pitch control
M2 (Motor 2): Right propeller - Roll/Pitch mixing  
M3 (Motor 3): Left propeller - Roll/Pitch mixing
S1 (Servo 1): Right elevon - Pitch/Roll in forward flight
S2 (Servo 2): Left elevon - Pitch/Roll in forward flight  
S3 (Servo 3): Right aileron - Mode-dependent positioning
S4 (Servo 4): Left aileron - Mode-dependent positioning
S5 (Servo 5): Thrust vector tilt - Yaw control
```

## Calibration Procedure

### 1. Center Point Calibration
1. **Center all sticks** including throttle
2. **Use EdgeTX subtrim** to achieve 1500μs on channels 1-4
3. **Target**: 1500μs ±5μs is acceptable
4. **Check**: All channels should read ~1500 with sticks centered

### 2. Endpoint Calibration  
1. **Move sticks to extremes**
2. **Adjust endpoints** in EdgeTX outputs to achieve:
   - **Minimum**: 1000μs (±5μs)
   - **Maximum**: 2000μs (±5μs)
3. **Verify**: Full stick deflection gives proper range

### 3. Switch Calibration
**Channel 5 (Throttle Cut) - Critical Safety Function:**
```
SA↑ (Up):    > 1500μs = THROTTLE CUT (motors disabled)
SA- (Mid):   ~ 1500μs = Normal operation  
SA↓ (Down):  < 1500μs = Normal operation
```

**Channel 6 (Flight Mode):**
```  
SB↑ (Up):    1700-2000μs = Hover mode
SB- (Mid):   1300-1700μs = Transition mode
SB↓ (Down):  1000-1300μs = Forward flight mode
```

## Pre-Flight Verification

### Control Surface Check
1. **Throttle**: Increases with stick forward
2. **Roll**: Right stick right = right roll command  
3. **Pitch**: Right stick back = pitch up command
4. **Yaw**: Left stick right = right yaw command

### Flight Mode Verification
Test each mode transition:
1. **Hover → Transition**: Smooth motor/servo transitions
2. **Transition → Forward**: Complete mode switch
3. **Emergency return to Hover**: Quick mode change capability

### Safety Checks
1. **Throttle Cut**: SA↑ immediately disables all motors
2. **Failsafe**: Radio loss triggers safe mode
3. **Range Test**: Verify control at maximum distance

## Troubleshooting

### Common Issues
**No Response from Receiver:**
- Check ExpressLRS binding process
- Verify power connections (5V/3.3V to receiver)
- Confirm PWM output mode on receiver

**Wrong Control Direction:**
- Use EdgeTX "Reverse" function in Outputs page
- Check physical stick calibration
- Verify control surface mechanical linkages

**Flight Mode Not Switching:**
- Check Channel 6 PWM ranges with multimeter
- Verify switch mechanical operation
- Confirm EdgeTX switch assignment

### Serial Monitor Values
**Expected PWM Ranges (Serial Output):**
```  
Channel 1: 1000-2000 (Throttle)
Channel 2: 1000-2000 (Aileron)
Channel 3: 1000-2000 (Elevator)  
Channel 4: 1000-2000 (Rudder)
Channel 5: 1000/2000 (Throttle Cut)
Channel 6: 1000/1500/2000 (Flight Mode)
```

## Advanced Configuration

### Expo and Rates
For smoother control feel:
```
Stick Expo: 20-30% on Aileron/Elevator  
Throttle Curve: Linear for VTOL
Dual Rates: Consider for different flight modes
```

### Telemetry Setup
If using ExpressLRS with telemetry:
- Battery voltage monitoring
- RSSI/LQ display
- Flight mode confirmation

## Safety Warnings

⚠️ **CRITICAL SAFETY POINTS:**
1. **Always test throttle cut** before first flight
2. **Verify flight mode switching** on the ground
3. **Test failsafe behavior** with radio off
4. **Never fly without proper receiver range testing**
5. **Ensure motor rotation directions** are correct

## Conclusion
This configuration provides full 6-channel control for the dRehmFlight F-35 VTOL with proper safety features and flight mode switching. Always perform thorough ground testing before attempting flight operations.

## References
- [dRehmFlight F-35 GitHub Repository](https://github.com/nickrehm/dRehmFlight-F-35)
- [EdgeTX User Manual](https://manual.edgetx.org/)  
- [ExpressLRS Documentation](https://www.expresslrs.org/)
- dRehmFlight VTOL Documentation.pdf (included with project)