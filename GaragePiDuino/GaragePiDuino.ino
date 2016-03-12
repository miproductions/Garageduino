/*
  Test circuit for GaragePi using 5V logic off an Arduino
  Note Pi uses 3V3 logic
 */

#include "DHT.h"; // https://github.com/freetronics/DHT-sensor-library
#define DHTTYPE DHT22

int lightSensorAPinI = 0;
int lightSensorVal = 0;
int printerLightsDPinO = 0;
int garageDoorDPinI = 2;
int humitempDPinI = 3;
int garageWindowDPinI = 4;
int onboardLedDPinO = 13;

DHT dht(humitempDPinI, DHTTYPE);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(onboardLedDPinO, OUTPUT); // LED
  pinMode(printerLightsDPinO, OUTPUT); // Relay 1
  pinMode(garageWindowDPinI, INPUT); // Window HES input
  pinMode(garageDoorDPinI, INPUT); // Garage Door HES input
  Serial.begin(9600);
  dht.begin();
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(onboardLedDPinO, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(printerLightsDPinO, HIGH);    // Relay 1 NO
  lightSensorVal = analogRead(lightSensorAPinI);
  Serial.print("Light Value:");
  Serial.println(lightSensorVal);
  Serial.print("Garage Window:");
  Serial.println(digitalRead(garageWindowDPinI));
  Serial.print("Garage Door:");
  Serial.println(digitalRead(garageDoorDPinI));
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: ");
    Serial.println(h);
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C");
  }
  delay(500);              // wait for a second
  digitalWrite(onboardLedDPinO, LOW);    // turn the LED off by making the voltage LOW
  // digitalWrite(printerLightsDPinO, LOW);    // Relay 1 NC
  delay(500);              // wait for a second
}
