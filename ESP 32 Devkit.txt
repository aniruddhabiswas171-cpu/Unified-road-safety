#include <WiFi.h>                 // WiFi library for ESP32 network connection
#include <WebServer.h>           // WebServer library to handle HTTP requests
WebServer server(80);                   // Create a web server on port 80
#define BUZZER_PIN 5                    // GPIO pin for buzzer
#define LED_PIN 4                       // GPIO pin for LED
void alert() {                // Function called when YOLO server sends alert
  Serial.println("🚨 ALERT RECEIVED — Animal detected!");  
  digitalWrite(BUZZER_PIN, HIGH);       // Turn ON buzzer
  digitalWrite(LED_PIN, HIGH);          // Turn ON LED
  delay(1500);                          // Keep ON for 1.5 seconds
  digitalWrite(BUZZER_PIN, LOW);        // Turn OFF buzzer
  digitalWrite(LED_PIN, LOW);           // Turn OFF LED
  server.send(200, "text/plain", "OK"); // Send response back to YOLO server
}
const char* ssid = "JioFi3_6A6C7D";     // WiFi SSID
const char* password = "y0kzn8mjww";    // WiFi password
void setup() {
  Serial.begin(115200);                 // Start Serial Monitor
  pinMode(BUZZER_PIN, OUTPUT);          // Set buzzer pin as output
  pinMode(LED_PIN, OUTPUT);             // Set LED pin as output
  digitalWrite(BUZZER_PIN, LOW);        // Ensure buzzer is OFF initially
  digitalWrite(LED_PIN, LOW);           // Ensure LED is OFF initially
  Serial.println("Connecting…");        // Show connection progress
  WiFi.begin(ssid, password);           // Begin WiFi connection
  while (WiFi.status() != WL_CONNECTED) { // Wait until connected
    delay(400);
    Serial.print(".");                  // Print dots while connecting
  }
  Serial.println("\nConnected!");  // Successfully connected
  Serial.print("ESP32 URL: ");     // Display ESP32 IP for Flask server usage
  Serial.println(WiFi.localIP());       

  server.on("/alert", alert);     // Create endpoint /alert → triggers alert()
  server.begin();               // Start the HTTP server
}
void loop() {
  server.handleClient();                // Handle all incoming HTTP requests
}
