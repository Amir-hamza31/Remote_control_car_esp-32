#pragma once

// WiFi
#define WIFI_SSID     "high ping"
#define WIFI_PASSWORD "netnaibal"

// UDP
#define UDP_PORT 1234

// Motor pins
#define IN1 25
#define IN2 26
#define IN3 27
#define IN4 14
#define ENA 32
#define ENB 33

// PWM
#define PWM_FREQ   1000
#define PWM_RES    8      // 8-bit = 0–255
#define PWM_CH_L   0
#define PWM_CH_R   1

// Safety timeout (ms) — stop motors if no packet received
#define PACKET_TIMEOUT_MS 500