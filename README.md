A template for ESP32 with a basic Blynk configuration and OTA enabled.  Two tasks are setup, with the main processing occuring in loop1, and the background (e.g. Blynk.run) occuring in loop2.  Each loop runs on a different core.

The next revision will contain a working WifiManager setup for easier wireless network configuration and provisioning.
