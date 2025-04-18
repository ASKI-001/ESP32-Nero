# ESP32-Nero: Simple Router MITM Attack Tool

**⚠️  WARNING: This tool is intended for educational and ethical testing purposes only.Unauthorized use to access or disrupt networks is illegal and unethical. Use responsibly! ⚠️**

## Description

ESP32-Nero is a simple tool designed for demonstrating a "Man-in-the-Middle" (MITM) attack scenario, specifically targeting a |)14log 4G router user's web interface. It leverages an ESP32 to create a fake access point that mimics the router, capturing credentials entered by unsuspecting users.

**Key Features:**

* **Fake Access Point:** Creates a Wi-Fi access point with the SSID "Dialog 4G 670" (can be modified).
* **Captive Portal:** Presents a web page that strongly resembles the fake router's update page.
* **Credential Capture:** Intercepts and displays the username (prefilled) and password submitted through the fake web page.
* **Simple Setup:** Designed to be relatively easy to deploy on an ESP32.
* **Notifications:** (Optional) Provides serial monitor notifications when devices connect or disconnect from the fake access point, including MAC addresses.

## How It Works

1.  The ESP32 creates a Wi-Fi access point, impersonating the target router.
2.  A DNS server running on the ESP32 redirects all web requests to the ESP32's web server.
3.  The web server serves a fake HTML page that looks like the router's update page.
4.  When a user connects to the fake access point and tries to access a web page, they are presented with the fake update page.
5.  If the user enters their password and submits the form, the ESP32 captures the credentials.

## Setup

**Hardware:**

* ESP32 WROOM 32U development board

**Software:**

* Arduino IDE
* ESP32 Arduino core installed

**Installation:**

1.  Clone or download this repository.
2.  Open the `ESP32-Nero.ino` file in the Arduino IDE.
3.  In the Arduino IDE:
    * Go to `Tools` \> `Board` and select your ESP32 board (e.g., "ESP32 Dev Module").
    * Ensure the correct COM port is selected under `Tools` \> `Port`.
4.  Compile and upload the code to your ESP32.

## Image


## Usage

1.  After uploading the code, the ESP32 will start the fake access point.
2.  Connect to the Wi-Fi network named "Dialog 4G 670" (or the SSID you configured).
3.  Open a web browser. You should be redirected to the fake update page.
4.  Enter the password.
5.  The captured password will be displayed in the Arduino IDE's serial monitor.

## Important Considerations

* **Ethical Use:** This tool should ONLY be used for authorized penetration testing or educational purposes.  Using it against networks or devices without explicit permission is illegal and unethical.
* **Disclaimer:** The developers of this tool are not responsible for any misuse.
* **Detection:** Advanced users or network security systems may be able to detect this type of attack.
* **Customization:** You can modify the SSID, HTML content, and other parameters in the code to suit your specific testing needs.

## License
Copyright (c) 2025 ASKI-001

Permission is hereby granted, free of charge, to any person obtaining a copyof this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

- Please give credits
- Only use for educational purposse 

## Disclaimer

This tool is provided as-is for educational and ethical testing purposes only.  The authors are not responsible for any misuse or damage caused by this software.  It is the user's responsibility to ensure they have proper authorization before using this tool.
