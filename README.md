# Unified Road Safety: AI Animal Collision Prevention

This project aims to prevent animal-vehicle collisions on highways using an ESP32 Cam module and AI-driven detection. When an animal is detected, the system triggers a roadside alert to warn drivers in real-time.

## 🚀 How It Works
1.  **Capture**: The **ESP32 Cam** module captures images of the roadside environment.
2.  **Processing**: Images are sent to a **YOLO (You Only Look Once)** server.
3.  **Detection**: The AI processes the images using predefined datasets to identify animals.
4.  **Alert**: If an animal is detected, a signal is sent back to trigger an **LED** and **Buzzer** alert for the driver.

## 🛠️ Hardware Requirements
*   ESP32 Cam Module
*   ESP32 Devkit (for testing/interfacing)
*   LED (Visual Alert)
*   Buzzer (Audio Alert)

## 📂 Repository Structure
*   `ESP 32 cam code.txt`: Source code for the camera module's firmware.
*   `YOLO server code.txt`: Python/AI server scripts for processing image data.
*   `ESP 32 Devkit.txt`: Configuration or pinout details for the development board.
*   `live testing.jpg`: Current snapshot of the system in action.

## 📸 Live Testing
![Live Testing](./live%20testing.jpg)

## 🔧 Setup & Installation
1.  **Flash ESP32**: Use the code in `ESP 32 cam code.txt` to program your module.
2.  **Start Server**: Run the `YOLO server code.txt` on your local machine or server to begin processing incoming frames.
3.  **Hardware Wiring**: Ensure the LED and Buzzer are connected to the specified GPIO pins defined in the source code.
