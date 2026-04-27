#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define PIR_PIN 4

// 🔐 Replace with your WiFi
const char* ssid = "your wifi name ";
const char* password = "your wifi password";

// 🌐 Replace with your server (ngrok or local IP)
const char* serverUrl = "http://local IP :5001/add";

// Track last state (important for efficiency)
int lastState = -1;

void setup() {
    Serial.begin(115200);
    pinMode(PIR_PIN, INPUT);

    // Connect WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi!");
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {

        int motion = digitalRead(PIR_PIN);

        // 🔥 Send only when state changes
        if (motion != lastState) {

            HTTPClient http;
            http.begin(serverUrl);
            http.addHeader("Content-Type", "application/json");

            String jsonData = "{\"motion\":" + String(motion) + "}";

            int response = http.POST(jsonData);

            Serial.print("Sent: ");
            Serial.print(motion);
            Serial.print(" | Response: ");
            Serial.println(response);

            http.end();

            lastState = motion;
        }
    } else {
        Serial.println("WiFi Disconnected");
    }

    delay(500); // small delay for stability
}
