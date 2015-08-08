/*
 * Garage Door Sensor
 * HC-SR04 Ultrasonic Sensor DEPRECATED due to 40kHz being in dog hearing range. TODO switch to IR/reed?
 * Freetronics EtherTen Uno-compatible (presumed on 10,11,12,13 as per Ethernet Shield)
 * Error LED
 * OpenHAB IoT Gateway
 * MQTT PubSubClient from https://github.com/knolleary/pubsubclient
 * Requires packages mosquitto mosquitto-clients python-mosquitto on server
 */

#define erPin 7 // Error LED
#define trPin 8 // HC-SR04 Trigger Pin
#define ecPin 9 // HC-SR04 Echo Pin
#define ping 1000 // no less than ~60ms to allow one ping to complete before the next is sent
#define ok 20 // distance in cm under which the door is open
#define tmg 58.2 // converts the ping duration to cm

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h> // MQTT framework

byte mac[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x50}; // my mac address
byte server[] = {192, 168, 2, 215}; // OMVBOX3 with OpenHAB
IPAddress ip(192,168,2,150); //sensor01 Garageduino per HOSTS
EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient); // inits the MQQT host

unsigned long keepalivetime=0;
unsigned long MQTT_reconnect=0;
const String omsg = " open";
const String cmsg = " closed";
const String emsg = "error";
const boolean dbg = true; // serial debugging

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

void setup() {
  // general
  if (dbg) Serial.begin(9600);
  
  // init pins
  pinMode(trPin, OUTPUT);
  pinMode(ecPin, INPUT);
  pinMode(erPin, OUTPUT);
  digitalWrite(erPin, HIGH);

  // init Ethernet
  Ethernet.begin(mac,ip);

  // init MQTT connection
  /*
  while (client.connect("Garageduino") != 1) {
    Serial.println("Error connecting to MQTT");
    delay(3000);
  }
  */
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


