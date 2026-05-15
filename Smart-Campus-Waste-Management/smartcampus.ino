#define BLYNK_TEMPLATE_ID "TMPL38fNCO9P6"
#define BLYNK_TEMPLATE_NAME "IOt Project"
#define BLYNK_AUTH_TOKEN "zTZNRUNnHoOWvyAHxrORKRUmexFPhEVx"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#define TRIG_PIN1 4
#define ECHO_PIN1 13
#define TRIG_PIN2 18
#define ECHO_PIN2 17
#define DHT_PIN 15
#define BUZZER_PIN 16
#define LED_PIN 2
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;

float getDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  long duration = pulseIn(echo, HIGH, 20000); 
  if (duration == 0) return 400.0;
  
  return (duration / 2.0) / 29.1;
}

void sendSensorData() {
  float d1 = getDistance(TRIG_PIN1, ECHO_PIN1);
  float d2 = getDistance(TRIG_PIN2, ECHO_PIN2);
  float distance = min(d1, d2);

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    temp = 25.0; 
    hum = 50.0;
  }

  Blynk.virtualWrite(V2, distance);    
  Blynk.virtualWrite(V0, temp);        
  Blynk.virtualWrite(V3, hum);         

  if (distance > 0 && distance < 10) {
    Blynk.virtualWrite(V1, "CRITICAL: Bin is Full!");
    tone(BUZZER_PIN, 1000, 200); 
    digitalWrite(LED_PIN, HIGH);
  } else {
    Blynk.virtualWrite(V1, "Status: Space Available");
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  if (temp > 60) {
    Blynk.virtualWrite(V1, "ALARM: Fire Hazard Temp!");
    tone(BUZZER_PIN, 2000, 500); 
  }

  Serial.printf("D1: %.1fcm | D2: %.1fcm | Temp: %.1fC\n", d1, d2, temp);
}

void setup() {
  Serial.begin(115200);
  delay(500); 
  Serial.println("\n--- Initializing Smart Bin System ---");
  
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  dht.begin();
  Blynk.config(BLYNK_AUTH_TOKEN);
  WiFi.begin(ssid, pass);
  
  timer.setInterval(4000L, sendSensorData);
  Serial.println("System Setup Complete!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Blynk.run();
  }
  timer.run();
}