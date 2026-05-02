#ifndef CONFIG_H
#define CONFIG_H

// ── WiFi Configuration ────────────────────────────────────────────
#define WIFI_SSID        "YOUR_WIFI_SSID"        // Change to your WiFi name
#define WIFI_PASSWORD    "YOUR_WIFI_PASSWORD"    // Change to your WiFi password
#define UDP_PORT         5005                    // UDP port for communication
#define PACKET_TIMEOUT_MS 1000                   // Stop motors if no packet for 1 second

// ── Motor Pins (Adjust based on your wiring) ──────────────────────
// LEFT MOTOR
#define IN1   19   // Motor A direction pin 1
#define IN2   21   // Motor A direction pin 2
#define ENA   22   // Motor A PWM speed pin

// RIGHT MOTOR
#define IN3   23   // Motor B direction pin 1
#define IN4   25   // Motor B direction pin 2
#define ENB   26   // Motor B PWM speed pin

// ── PWM Configuration ─────────────────────────────────────────────
#define PWM_FREQ  5000   // PWM frequency in Hz
#define PWM_RES   8      // PWM resolution (8-bit = 0-255)
#define PWM_CH_L  0      // PWM channel for left motor
#define PWM_CH_R  1      // PWM channel for right motor

#endif
