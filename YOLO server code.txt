from ultralytics import YOLO                 # Import YOLO model
from flask import Flask, request             # Flask server and request handler
import numpy as np                           # For handling byte data
import cv2                                   # For decoding image
import requests                              # To send alert to ESP32
app = Flask(__name__)                        # Create Flask app
model = YOLO("yolov8n.pt")                   # Load YOLOv8 model
ESP32_URL = "http://192.168.225.60/alert"    # ESP32 alert URL
ANIMAL_CLASSES = [15, 16, 18, 19]            # cat, dog, sheep, cow IDs
@app.route("/upload", methods=["POST"])      # Endpoint to receive image
def upload():                              # Called when image comes from ESP32
  print("\n📸 Image received from ESP32")   # Show message
    img_bytes = request.get_data()           # Read raw image bytes
    img_arr = np.frombuffer(img_bytes, np.uint8)  # Convert to array
    img = cv2.imdecode(img_arr, cv2.IMREAD_COLOR) # Decode image
     if img is None:                              # If decode failed
         print("❌ Failed to decode image")
         return {"status": "error"}, 400
     results = model(img)[0]                      # Run YOLO detection
     detected = False                             # Detection flag
     for cls in results.boxes.cls:                # Check each detected class
         cls_id = int(cls)                        # Convert class to number
         if cls_id in ANIMAL_CLASSES:             # If animal found
             detected = True
           print(f"🐾 Animal detected! Class = {cls_id}")
     if detected:                                 # If any animal detected
         print("➡️ Sending alert to ESP32")
         try:
             requests.get(ESP32_URL, timeout=2)    # Send alert
             print("🚨 Alert sent!")
         except Exception as e:
             print("❌ Failed to send alert:", e)
     return {"status": "ok"}                      # Reply to ESP32
 app.run(host="0.0.0.0", port=5000)               # Start server
