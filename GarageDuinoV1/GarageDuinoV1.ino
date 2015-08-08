/*
 * Garage Door Sensor
 * 
 * Freetronics EtherTen Uno-compatible (presumed on 10,11,12,13 as per Ethernet Shield)
 * Error LED
 * OpenHAB IoT Gateway
 * MQTT PubSubClient from https://github.com/knolleary/pubsubclient
 * Requires packages mosquitto mosquitto-clients python-mosquitto on server
 */

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h> // MQTT framework
#include <DHT.h> // Humidity/Temp Sensor

#define dhtPin 2 // Humidity/Temp Sensor
#define dhtType DHT22 // DHT 22 (AM2302)
#define erPin 7 // Error LED
#define trPin 8 // HC-SR04 Trigger Pin
#define ecPin 9 // HC-SR04 Echo Pin
#define ping 1000 // no less than ~60ms to allow one ping to complete before the next is sent
#define ok 20 // distance in cm under which the door is open
#define tmg 58.2 // converts the ping duration to cm

byte mac[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x50}; // my mac address
byte server[] = {192, 168, 2, 215}; // OMVBOX3 with OpenHAB
IPAddress ip(192,168,2,150); //sensor01 Garageduino per HOSTS
EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient); // inits the MQQT host
DHT dht(dhtPin, dhtType);

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

  // init Temp/Humidity Sensor
  dht.begin();
}

void loop() {
  dhtSensor();
}

void debug(long num, String msg) {
  if (dbg) {
    Serial.print(num);
    Serial.println(msg);
  }
}

void dhtSensor() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
   debug(0,"Failed to read from DHT");
  } else {
    debug(h, "% Humidity");
    debug (t, "*C Temperature");
  }
}


