#include <Adafruit_NeoPixel.h>

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define LED_PIN    4
#define LED_COUNT 54

const char *ssid     = "pigpen";
const char *password = "Jamie1149664344";
const long utcOffsetInSeconds = -14400;
bool state = false;
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup(){
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
      strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  if (!state && timeClient.getHours()>= 9 && timeClient.getMinutes()>= 0){
    Serial.println("Turning on");
    state = true;
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      for (int j = 0; j<20; j++){
        strip.setPixelColor(i, strip.Color(j*12,j*12,j*11));         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
        delay(50);                           //  Pause for a moment
      }
    }
  }
  delay(1000);
}
