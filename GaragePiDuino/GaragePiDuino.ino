/*
  Test circuit for GaragePi using 5V logic off an Arduino
  Note Pi uses 3V3 logic
 */

#include "DHT.h"; // https://github.com/freetronics/DHT-sensor-library

// Pins - no duplicates
#define lightSensorAPinI 0
#define printerLightsDPinO 0
#define garageDoorDPinI 2
#define humitempDPinI 3
#define garageWindowDPinI 4
#define onboardLedDPinO 13

// Constants
#define DHTTYPE DHT22
#define DEBUG true
#define DELAY 1000
#define YES true
#define NO false

// Variables
int lightSensorVal = 0;
float temp = 0.0f;
float humi = 0.0f;
DHT dht(humitempDPinI, DHTTYPE);

void setup() {
  pinMode(onboardLedDPinO, OUTPUT); // Activity LED
  pinMode(printerLightsDPinO, OUTPUT); // Relay 1 for printer lights
  pinMode(garageWindowDPinI, INPUT); // Window Hall Effect Sensor input
  pinMode(garageDoorDPinI, INPUT); // Garage Door Hall Effect Sensor input
  
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  digitalWrite(onboardLedDPinO, HIGH); // LED on while we're processing loop
  digitalWrite(printerLightsDPinO, HIGH);
  
  debugit("-----------------------", YES);
  
  lightSensorVal = analogRead(lightSensorAPinI);
  debugit("Light Value:", NO);
  debugit(lightSensorVal, YES);
  
  debugit("Garage Window:", NO);
  debugit(digitalRead(garageWindowDPinI), YES);
  
  debugit("Garage Door:", NO);
  debugit(digitalRead(garageDoorDPinI), YES);
  
  humi = dht.readHumidity();
  debugit("Humidity: ", NO);
  debugit(humi, YES);
  
  temp = dht.readTemperature();
  debugit("Temperature: ", NO);
  debugit(temp, YES);
  
  digitalWrite(onboardLedDPinO, LOW); // LED off while we delay
  delay(DELAY);
}

void debugit (int foo, boolean enter) {
  if (DEBUG && !isnan(foo)) {
    if (enter) {
      Serial.println(foo);
    } else {
      Serial.print(foo);
    }
  }
}

void debugit (String foo, boolean enter) {
  if (DEBUG) {
    if (enter) {
      Serial.println(foo);
    } else {
      Serial.print(foo);
    }
  }
}

void debugit (float foo, boolean enter) {
  if (DEBUG && !isnan(foo)) {
    if (enter) {
      Serial.println(foo);
    } else {
      Serial.print(foo);
    }
  }
}

