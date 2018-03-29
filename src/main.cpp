// Standard Libraries
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

// OTA Update Libraries
#include <ESPmDNS.h>          // This library isn't availible in PlatformIO's library tool, and has to be manually put into the lib directory. It's contained in the Arduino ESP32 framework.
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


// Blynk Libraries
char auth[] = "<BLYNK TOKEN>";
char ssid[] = "<SSID>";
char pass[] = "<PASSWORD>";
//#define BLYNK_DEBUG
#define BLYNK_PRINT Serial
#define BLYNK_MAX_READBYTES  4096
#include <BlynkSimpleEsp32.h>
#include <SimpleTimer.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <WidgetBridge.h>

WidgetRTC rtc;

BLYNK_CONNECTED() {
  rtc.begin();
  Blynk.syncAll();
}

// Used for foreground processes.
void loop1(void *pvParameters) {
  while (1) {
    delay(1);                       // Needed to reset watchdog timer, else it throws error in serial
  }
}


//  Used for background processes.   Also good for inturrupts (like button presses)
void loop2(void *pvParameters) {
  while (1) {
    if(Blynk.connected()) {
      Blynk.run();
    } else Blynk.connect();
    ArduinoOTA.handle();
    delay(1);                     // Needed to reset watchdog timer, else it throws error in serial
  }
}



void setup()
{
  Serial.begin(115200);

  // Blynk Setup
  Blynk.begin(auth, ssid, pass, "<SERVERNAME>", 8080);
  setSyncInterval(60);

  // OTA Setup
  ArduinoOTA.setHostname("ESP32-01");  // For OTA - Use your own device identifying name
  ArduinoOTA.begin();

  // Loop Setup
  xTaskCreatePinnedToCore(loop1, "loop1", 4096, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(loop2, "loop2", 4096, NULL, 1, NULL, 1);

}

void loop()
{
            // Leave empty
}
