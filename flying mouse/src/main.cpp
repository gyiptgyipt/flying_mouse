#include <Wire.h>
#include <MPU9250.h>
#include <WiFi.h>

MPU9250 IMU(Wire, 0x68); // Create an MPU9250 object

// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Server details
WiFiServer server(80); // Create a TCP server on port 80

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize MPU9250
  if (IMU.begin() < 0) {
    Serial.println("IMU initialization failed");
    while (1);
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // Check for client connections

  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      IMU.readSensor(); // Read sensor data

      // Get accelerometer data
      float ax = IMU.getAccelX_mss();
      float ay = IMU.getAccelY_mss();

      // Send data to the client
      client.print(ax);
      client.print(",");
      client.println(ay);

      delay(20); // Adjust delay for smoother data transmission
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}