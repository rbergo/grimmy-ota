#include <Arduino.h>
#include <WiFiNINA.h>
#include <ArduinoOTA.h>
#include <InternalStorage.h> // For InternalStorage

// IMPORTANT: Replace with your actual WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* pass = "YOUR_WIFI_PASSWORD";

// OTA Settings
const char* ota_name = "mkr1010-ota";
// You can set an OTA password here if desired. If not, leave it empty.
const char* ota_password = ""; // Empty string for no password

InternalStorageClass ota_storage; // Concrete implementation for on-chip flash

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Booting...");

  // Check for WiFi module
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // Attempt to connect to WiFi network
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    Serial.print(".");
    delay(3000); // wait 3 seconds for connection
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Configure OTA
  // The ArduinoOTA.begin() for this library version requires IP, name, password, and storage.
  ArduinoOTA.begin(WiFi.localIP(), ota_name, ota_password, ota_storage);

  Serial.print("OTA Initialized. Device Name: ");
  Serial.print(ota_name);
  Serial.print(" (IP: ");
  Serial.print(WiFi.localIP());
  Serial.println(")");
  if (strlen(ota_password) > 0) {
    Serial.println("OTA Password is set.");
  } else {
    Serial.println("OTA Password is NOT set.");
  }
}

void loop() {
  ArduinoOTA.poll();
}