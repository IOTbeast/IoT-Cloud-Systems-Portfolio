/*
 * Project: Smart Guest Attendance System
 * Author: Vishal Kumar
 * Hardware: ESP32, HC-SR04 x2, DS1307 RTC, LDR, LED
 * Services: Blynk IoT, ThingSpeak
 * * Description: 
 * This system monitors guest entry/exit using ultrasonic sensors,
 * controls room lighting based on time-of-day and ambient light,
 * and syncs all data to Blynk and ThingSpeak dashboards.
 */

#include "WiFi.h"
#include <Wire.h>
#include <RTClib.h>
#include "ThingSpeak.h"
#include <BlynkSimpleEsp32.h>
#include "config.h"  // <--- This pulls in your private data

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Guest Attendance System"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#define WIFI_NETWORK "Wokwi-GUEST"
#define pass ""
#define CHANNEL_ID 0000000 // Your ThingSpeak Channel ID
#define CHANNEL_API_KEY "YOUR_API_KEY"

char auth[] = BLYNK_AUTH_TOKEN;

RTC_DS1307 rtc;  //RTC instance

//setting pin values for the sensors
#define trig1 12
#define echo1 14
#define trig2 5
#define echo2 17

float cm1, cm2;

const int sensorpin = 34;
const int ledpin = 23;
int bpin = 0;

int pirState = LOW;  // we start, assuming no motion detected
int ledstate = LOW;           
int val = 0; 
int totalEntry = 0;
int current = 0;
int brightness = 0;
int per = 0;

// Defining the maximum and minimum brightness levels
const int maxBrightness = 255; // Maximum brightness 
const int minBrightness = 0;   // Minimum brightness 
const int morningBrightness = 75;  // Dimmer brightness in the morning
const int noonBrightness = 50;     // Full brightness at noon
const int eveningBrightness = 100;   // Dimmer brightness in the evening
const int nightBrightness = 255;     // Lowest brightness at night

WiFiClient client;  //WiFi instance

//Function to connect to the WiFi
void connectToWifi()
{
  Serial.print("Connecting To Wifi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  if(WiFi.status() !=WL_CONNECTED)
  {
    Serial.print("Failed");
  }
  else
  {
    Serial.print("Connected");
    Serial.print(WiFi.localIP());
  }
}

//Function to obtain value from the ultrasonic sensor
long readUltrasonicDistance(int triggerPin, int echoPin)
{
	pinMode(triggerPin, OUTPUT);  // Clear the trigger
	digitalWrite(triggerPin, LOW);
	delayMicroseconds(2);
	// Sets the trigger pin to HIGH state for 10 microseconds
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);
	pinMode(echoPin, INPUT);
	// Reads the echo pin, and returns
	// the sound wave travel time in microseconds
	return pulseIn(echoPin, HIGH);
}

//Function to determine the guest count
void entryExit()
{
  cm1 = 0.0344/2 * readUltrasonicDistance(trig1, echo1);
  cm2 = 0.0344/2 * readUltrasonicDistance(trig2, echo2);

  if(2 < cm1 && cm1 < 100) //Setting the threshold value to determine guest entry
  {
    Serial.print("\nExternal Motion Detected!!\nWaiting for Permission");
    delay(1000);
    if(per == 1)
      {
        Serial.print("\nPermission Granted\nGuest Entered!!");
        totalEntry++;
        current++;
      }
      else if(per == 0)
      {
        Serial.print("\nGuest Entry Denied!!");  
      }
    delay(1000);
  }
  if(2 < cm2 && cm2 < 100) //Setting the threshold value to determine guest exit
  {
    if(current>0)
    {
      current--;
      Serial.print("\nInternal Motion Detected!!\nGuest Left!!");
      delay(1000);
    }
  }
   Serial.print("\nGuests Entered: ");
  Serial.println(totalEntry);
  Serial.print("Guests Present: ");
  Serial.println(current);
  if(current >0 && ledstate == LOW)
  {
    Serial.print("LED Turned On!!");
    light();
  }
  else if(current > 0 && ledstate == HIGH)
  {
    light();
  }
  else if(current == 0 && ledstate == HIGH)
  {
    Serial.print("LED Turned Off!!");
    analogWrite(ledpin, 0);
  }
  delay(1000); 
}

//Function to turn on the light based on guest count and time of the day
void light()
{
  // Read the value from the ldr sensor
  int sensorvalue = analogRead(sensorpin);

  // Mapping the ldr value to the LED brightness
  int b = map(sensorvalue, 0, 1023, minBrightness, maxBrightness);

   // Read the current time
  DateTime now = rtc.now();
  brightness = 0;
  // Adjust brightness based on time of day
  if (now.hour() >= 6 && now.hour() < 12) {
    brightness = morningBrightness;
  } else if (now.hour() >= 12 && now.hour() < 18) {
    brightness = noonBrightness;
  } else if (now.hour() >= 18 && now.hour() < 22) {
    brightness = eveningBrightness;
  } else {
    brightness = nightBrightness;
  }

  // Adjust brightness based on both time of day and surrounding brightness
  brightness = min(brightness, b);

  // Set the brightness of the LED
  analogWrite(ledpin, brightness);
  ledstate = HIGH;

  // Print the brightness value...for user's knowledge
  Serial.print("\nBrightness: ");
  Serial.println(brightness);
  Serial.print("\n");
  delay(1000); 
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(ledpin, OUTPUT);

  connectToWifi();
  ThingSpeak.begin(client);

  if (!rtc.begin())
 {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  Blynk.begin(auth, WIFI_NETWORK, pass);  
   while(!Blynk.connected())
  {
    Serial.print(".");
    delay(100);
  }
  Serial.print("\nConnected to Blynk");  
  pinMode(bpin,OUTPUT);
  
}

void loop()
 {
  // put your main code here, to run repeatedly:
      Blynk.run();
      entryExit();
      ThingSpeak.setField(1, totalEntry);
      ThingSpeak.setField(2, current);
      ThingSpeak.setField(3, brightness);
      ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);   
      delay(5000);   
 }
 BLYNK_CONNECTED()
{ 
      Blynk.syncVirtual(V0);  // will cause BLYNK_WRITE(V0) to be executed
}

BLYNK_WRITE(V0) // Executes when the value of virtual pin 0 changes
{
    per = param.asInt();
}
