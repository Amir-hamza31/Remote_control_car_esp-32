#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include "config.h"

WiFiUDP udp;
char packetBuffer[256];
unsigned long lastPacketTime = 0;

// ── Motor control ────────────────────────────────────────────────
void setMotor(uint8_t pinA, uint8_t pinB, uint8_t pwmCh, float speed) {
    int pwm = (int)(abs(speed) * 255);
    pwm = constrain(pwm, 0, 255);

    if (speed > 0.02f) {
        digitalWrite(pinA, HIGH);
        digitalWrite(pinB, LOW);
    } else if (speed < -0.02f) {
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, HIGH);
    } else {
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        pwm = 0;
    }
    ledcWrite(pwmCh, pwm);
}

void stopMotors() {
    setMotor(IN1, IN2, PWM_CH_L, 0);
    setMotor(IN3, IN4, PWM_CH_R, 0);
}

// ── Setup ─────────────────────────────────────────────────────────
void setup() {
    Serial.begin(115200);

    // Motor pin modes
    pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

    // PWM channels
    ledcSetup(PWM_CH_L, PWM_FREQ, PWM_RES);
    ledcSetup(PWM_CH_R, PWM_FREQ, PWM_RES);
    ledcAttachPin(ENA, PWM_CH_L);
    ledcAttachPin(ENB, PWM_CH_R);

    stopMotors();

    // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected! IP: ");
    Serial.println(WiFi.localIP());

    udp.begin(UDP_PORT);
    Serial.printf("UDP server listening on port %d\n", UDP_PORT);
}

// ── Loop ──────────────────────────────────────────────────────────
void loop() {
    // Safety timeout — stop if Python script disconnects
    if (millis() - lastPacketTime > PACKET_TIMEOUT_MS) {
        stopMotors();
    }

    int packetSize = udp.parsePacket();
    if (packetSize <= 0) return;

    int len = udp.read(packetBuffer, sizeof(packetBuffer) - 1);
    packetBuffer[len] = '\0';
    lastPacketTime = millis();

    StaticJsonDocument<64> doc;
    if (deserializeJson(doc, packetBuffer) != DeserializationError::Ok) return;

    float left  = doc["l"] | 0.0f;
    float right = doc["r"] | 0.0f;

    left  = constrain(left,  -1.0f, 1.0f);
    right = constrain(right, -1.0f, 1.0f);

    setMotor(IN1, IN2, PWM_CH_L, left);
    setMotor(IN3, IN4, PWM_CH_R, right);
}