/*
 * Garage Door Sensor
 * HC-SR04 Ultrasonic Sensor 
 * Freetronics EtherTen Uno-compatible (presumed on 10,11,12,13 as per Ethernet Shield)
 * Error LED
 * OpenHAB IoT Gateway
 */

#define erPin 7 // Error LED
#define trPin 8 // HC-SR04 Trigger Pin
#define ecPin 9 // HC-SR04 Echo Pin
#define ping 1000 // no less than ~60ms to allow one ping to complete before the next is sent
#define ok 20 // distance in cm under which the door is open
#define tmg 58.2 // converts the ping duration to cm
#define omsg " open"
#define cmsg " closed"
#define emsg "error"
#define dbg true // serial debugging

#include <SPI.h>
#include <Ethernet.h>

void setup() {
  if (dbg) Serial.begin (9600);
  pinMode(trPin, OUTPUT);
  pinMode(ecPin, INPUT);
  pinMode(erPin, OUTPUT);
  digitalWrite(erPin, HIGH);
}

void loop() {
  long dur, dist;
  digitalWrite(trPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trPin, LOW);
  dur = pulseIn(ecPin, HIGH);
  dist = dur / tmg;
  if (dist >= 200 || dist <= 0) {
    // Sensor isn't reading a valid value
    digitalWrite(erPin,HIGH);
    debug(dist, emsg);
  } else if (dist < ok) {
    // door is open
    digitalWrite(erPin,HIGH);
    delay(100);
    digitalWrite(erPin,LOW);
    debug(dist, omsg);
  } else {
    // door is closed
    digitalWrite(erPin,LOW);
    debug(dist, cmsg);
  }
  delay(ping);
}

void debug(long dist, String msg) {
  if (dbg) {
    Serial.print(dist);
    Serial.println(msg);
  }
}


