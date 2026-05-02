#include <WiFi.h>

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();  
  delay(1000);

  Serial.println("WiFi scan started...");
}

void loop() {
  Serial.println("Scanning nearby WiFi networks...");

  int n = WiFi.scanNetworks(); // returns number of networks found

  if (n == 0) {
    Serial.println("No networks found");
  } else {
    Serial.println("Networks found:");
    for (int i = 0; i < n; i++) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));        // Network name
      Serial.print(" (Signal: ");
      Serial.print(WiFi.RSSI(i));        // Signal strength
      Serial.print(" dBm)");
      
      // Check encryption type
      Serial.print("  Security: ");
      switch (WiFi.encryptionType(i)) {
        case WIFI_AUTH_OPEN:
          Serial.println("Open");
          break;
        case WIFI_AUTH_WEP:
          Serial.println("WEP");
          break;
        case WIFI_AUTH_WPA_PSK:
          Serial.println("WPA PSK");
          break;
        case WIFI_AUTH_WPA2_PSK:
          Serial.println("WPA2 PSK");
          break;
        case WIFI_AUTH_WPA_WPA2_PSK:
          Serial.println("WPA/WPA2");
          break;
        default:
          Serial.println("Unknown");
          break;
      }
    }
  }

  Serial.println("-------------------------");

  WiFi.scanDelete(); // free memory
  delay(5000);       // scan every 5 sec
}