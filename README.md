# Bluetooth-Enabled PID Line Follower & Autonomous Maze Navigation 

A high-speed line following robot with autonomous maze-solving capability, built on a custom PCB using Arduino, 2000 RPM DC motors, and an 8-sensor array with a tuned PID control loop.

## How It Works

The robot reads an 8-sensor IR array, maps the sensor pattern to a positional error (-7 to +7), and feeds that into a PD control loop that adjusts left and right motor speeds in real time. At intersections, it detects the pattern and executes turns autonomously.

## Features
- **Tuned PD control loop** — Kp and Kd values tuned iteratively for stable high-speed tracking
- **Bluetooth telemetry** — wireless parameter tuning and live debugging without reflashing
- **Autonomous intersection detection** — detects left, right, and straight intersections in real time
- **Stop detection** — recognizes end-of-maze markers and halts
- **I2C OLED diagnostics** — live sensor values and PID parameters displayed on board
- **Auto background detection** — handles both black-on-white and white-on-black tracks

## Files
- `pidfinalcodes.ino` — final competition-ready version, tuned for black line on white background
- `ashit.ino` — experimental version with auto background detection and Bluetooth telemetry

## Key Parameters
```cpp
#define diff_const  17   // Proportional constant (Kp)
#define kd          65   // Derivative constant (Kd)
#define baseMotorSpeed  90  // Base speed (0-255)
#define turnspeed   90   // Speed during turns
```

## Hardware
- Arduino Uno
- 8-channel IR sensor array
- L298N motor driver
- 2000 RPM DC motors
- Custom PCB (designed in Altium)
- I2C OLED display
- Bluetooth module (HC-05)

## Built By
Shrey Pathak — EE Student at San José State University
