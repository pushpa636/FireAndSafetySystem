#define BLYNK_TEMPLATE_ID "your blynk teamplate id"
#define BLYNK_TEMPLATE_NAME "Fire and smart home"
#define BLYNK_AUTH_TOKEN "your auth token"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials
char ssid[] = "your wifi ssid";     // replace with your WiFi SSID
char pass[] = "your wfif password";      // replace with your WiFi Password

// Example sensor pins
#define FIRE_SENSOR D1
#define BUZZER D2

BlynkTimer timer;

// Function to read fire sensor
void checkFire()
{
  int fireValue = digitalRead(FIRE_SENSOR);

  if (fireValue == LOW) { // Assuming LOW = fire detected
    Serial.println("🔥 Fire Detected!");
    Blynk.logEvent("fire_alert", "🔥 Fire Detected in Your Home!"); // Make sure you created this Event in Blynk app
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode(FIRE_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Call checkFire every 2 seconds
  timer.setInterval(2000L, checkFire);
}

void loop()
{
  Blynk.run();
  timer.run();
}
