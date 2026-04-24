#include <WiFi.h>                           // WiFi functions
#include <WiFiClientSecure.h>               // Secure WiFi client
#include "esp_camera.h"                     // ESP32-CAM library
#include "esp_timer.h"                      // Timer functions
#include "img_converters.h"                 // Image conversion tools
#include "Arduino.h"                        // Arduino core functions
const char* ssid = "  ";                    // WiFi name
const char* password = "  ";                // WiFi password
String serverUrl = "http://  :5000/upload"; // Server URL
void startCamera() {                        // Start camera setup
  camera_config_t config;                   // Camera config object
  config.ledc_channel = LEDC_CHANNEL_0;     // LEDC channel
  config.ledc_timer = LEDC_TIMER_0;         // LEDC timer
  config.pin_d0 = Y2_GPIO_NUM;              // Data pin D0
  config.pin_d1 = Y3_GPIO_NUM;              // Data pin D1
  config.pin_d2 = Y4_GPIO_NUM;              // Data pin D2
  config.pin_d3 = Y5_GPIO_NUM;              // Data pin D3
  config.pin_d4 = Y6_GPIO_NUM;              // Data pin D4
  config.pin_d5 = Y7_GPIO_NUM;              // Data pin D5
  config.pin_d6 = Y8_GPIO_NUM;              // Data pin D6
  config.pin_d7 = Y9_GPIO_NUM;              // Data pin D7
  config.pin_xclk = XCLK_GPIO_NUM;          // Clock pin
  config.pin_pclk = PCLK_GPIO_NUM;          // Pixel clock
  config.pin_vsync = VSYNC_GPIO_NUM;        // VSYNC pin
  config.pin_href = HREF_GPIO_NUM;          // HREF pin
  config.pin_sscb_sda = SIOD_GPIO_NUM;      // I2C SDA
  config.pin_sscb_scl = SIOC_GPIO_NUM;      // I2C SCL
  config.pin_pwdn = PWDN_GPIO_NUM;          // Power down
  config.pin_reset = RESET_GPIO_NUM;        // Reset pin
  config.xclk_freq_hz = 20000000;           // Clock speed
  config.pixel_format = PIXFORMAT_JPEG      // JPEG format
  config.frame_size = FRAMESIZE_SVGA;       // Resolution
  config.jpeg_quality = 10;                 // JPEG quality
  config.fb_count = 2;                      // Frame buffers
  if (esp_camera_init(&config) != ESP_OK) { // If init fails
    Serial.println("Camera init failed");   // Show error
    delay(2000);                            // Pause
    ESP.restart();                          // Restart
  }
}
void sendImage() {                          // Capture and send image
  camera_fb_t * fb = esp_camera_fb_get();   // Get frame
  if (!fb) {                                // If failed
    Serial.println("Failed camera capture");// Print error
    return;                                 // Stop
  }
  WiFiClient client;                        // WiFi client
  if (!client.connect("192.168.225.160", 5000)) { // Connect to server
    Serial.println("Connection Failed");    // Error
    esp_camera_fb_return(fb);               // Free memory
    return;                                 // Stop
  }
  client.println("POST /upload HTTP/1.1");  // POST request
  client.println("Host: 192.168.225.160");  // Host header
  client.println("Content-Type: image/jpeg"); // JPEG type
  client.print("Content-Length: ");         // Size label
  client.println(fb->len);                  // Size value
  client.println();                         // End headers
  client.write(fb->buf, fb->len);           // Send bytes
  esp_camera_fb_return(fb);                 // Free buffer
  Serial.println("Image sent!");            // Success msg
}
void setup() {                               // Runs once
  Serial.begin(115200);                      // Start serial
  Serial.println("Booting...");              // Boot msg
  WiFi.begin(ssid, password);                // Connect WiFi
  while (WiFi.status() != WL_CONNECTED) {    // Wait for WiFi
    Serial.print(".");                       // Dots for loading
    delay(300);                              // Delay
  }
  Serial.println("\nWiFi connected!");       // Connected
  startCamera();                              // Start camera
}
void loop() {                                 // Repeat
  sendImage();                                // Send image
  delay(1500);                                // 1.5 sec wait
}
