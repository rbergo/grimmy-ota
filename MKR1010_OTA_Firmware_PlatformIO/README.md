# Arduino MKR WiFi 1010 OTA Firmware (PlatformIO)

This firmware enables Over-the-Air (OTA) updates for the Arduino MKR WiFi 1010 board using the WiFiNINA library and PlatformIO.

## Features

*   Connects to a specified WiFi network.
*   Initializes the ArduinoOTA service.
*   Allows firmware updates over the WiFi network without needing a USB connection after the initial flash.
*   Uses PlatformIO for project building and management.

## Prerequisites

*   [PlatformIO CLI](https://platformio.org/install/cli) or [PlatformIO IDE for VSCode](https://platformio.org/platformio-ide) installed.
*   Arduino MKR WiFi 1010 board.
*   A WiFi network.

## Setup and Usage

### 1. Configure WiFi Credentials

Open the `src/main.cpp` file and modify the following lines with your WiFi network's SSID and password:

```cpp
// IMPORTANT: Replace with your actual WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* pass = "YOUR_WIFI_PASSWORD";
```

(Optional) For enhanced security, you can set an OTA password by uncommenting and setting a value for `ota_password` in `src/main.cpp`:
```cpp
// const char* ota_password = "ota_password"; // Uncomment and set a password for OTA security
```
If you set a password here, you will need to provide it when performing an OTA update.

### 2. Initial Firmware Upload (USB)

1.  Connect your Arduino MKR WiFi 1010 to your computer via USB.
2.  Open this project folder in VSCode with the PlatformIO extension installed, or navigate to this project folder in your terminal.
3.  Build and upload the firmware using PlatformIO:
    ```bash
    pio run -t upload
    ```
    PlatformIO should automatically detect the port. If not, you might need to specify it.

### 3. Open Serial Monitor

After uploading, open the Serial Monitor to observe the connection process and see the IP address assigned to the board. You can do this in PlatformIO using:
```bash
pio device monitor
```
Or by clicking the "Serial Monitor" icon in the PlatformIO toolbar in VSCode. The default speed is 115200 baud.

You should see output similar to this:
```
Booting...
Attempting to connect to SSID: YOUR_WIFI_SSID
.........
Connected to WiFi
IP Address: 192.168.1.XXX  <-- Note this IP address
OTA Initialized
Ready to receive OTA updates for hostname: mkr1010-ota-pio
```

### 4. Performing an OTA Update

Once the initial firmware is running and the device is connected to WiFi, you can perform subsequent updates wirelessly:

1.  Make your desired changes to the firmware code (e.g., in `src/main.cpp`).
2.  Build and upload using PlatformIO, specifying the device's IP address (obtained from the Serial Monitor) as the upload port:
    ```bash
    pio run -t upload --upload-port <IP_ADDRESS_OF_DEVICE>
    ```
    For example:
    ```bash
    pio run -t upload --upload-port 192.168.1.123
    ```
    Alternatively, if you are using VSCode with the PlatformIO extension, network ports (like your MKR1010's OTA endpoint) should automatically appear in the "Upload Port" list when you try to upload. The hostname `mkr1010-ota-pio.local` (if mDNS is working on your network) might also be available.

3.  During the OTA update, you should see progress messages in the Serial Monitor (if it's still open) and in the PlatformIO upload output.

## Project Structure

*   `src/main.cpp`: The main firmware code.
*   `platformio.ini`: PlatformIO project configuration file.
*   `.gitignore`: Specifies intentionally untracked files that Git should ignore.
*   `README.md`: This file.

## Troubleshooting

*   **No WiFi Module:** If you see "Communication with WiFi module failed!", ensure your MKR1010 board is functioning correctly and the WiFiNINA firmware is up to date if prompted.
*   **OTA Not Appearing:**
    *   Ensure your computer and the MKR1010 are on the **same WiFi network**.
    *   Check your firewall settings to ensure it's not blocking network discovery (mDNS on port 5353) or the OTA communication (typically TCP port 3232 on ESP32, check ArduinoOTA specifics for SAMD if different, though often handled by hostname).
    *   If using the hostname (e.g., `mkr1010-ota-pio.local`), ensure your system has mDNS/Bonjour support. Using the IP address directly is more reliable.
*   **OTA Password:** If you set an OTA password in the firmware, you'll be prompted for it during the upload process.
```
