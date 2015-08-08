/*
 * Garage Door Sensor
 * 
 * Freetronics EtherTen Uno-compatible (presumed on 10,11,12,13 as per Ethernet Shield)
 * Error LED
 * OpenHAB IoT Gateway
 * MQTT PubSubClient from https://github.com/knolleary/pubsubclient
 * Freetronics DHT22 Humidity/Temp sensor library https://github.com/freetronics/DHT-sensor-library
 * Requires packages mosquitto mosquitto-clients python-mosquitto on server
 */

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h> // MQTT framework
#include <DHT.h> // Humidity/Temp Sensor

#define dhtPin 2 // Humidity/Temp Sensor
#define dhtType DHT22 // DHT 22 (AM2302)
#define erPin 7 // Error LED

byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x50}; // random mac address
byte server[] = {192, 168, 2, 215}; // OMVBOX3 with OpenHAB
IPAddress ip(192,168,2,150); //sensor01 Garageduino per HOSTS
EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient); // inits the MQQT host
DHT dht(dhtPin, dhtType);

unsigned long keepalivetime=0;
unsigned long MQTT_reconnect=0;
const boolean dbg = true; // serial debugging

void setup() {
 
  // init pins
  pinMode(dhtPin, INPUT);
  
  // general
  if (dbg) Serial.begin(9600);
 
  debug(0,"Loaded, doing DHCP...");
  
  // Ethernet
  while (Ethernet.begin(mac) == 0) {
    debug(0,"Failed to configure Ethernet using DHCP");
    delay(3000);
  }
  // print your local IP address:
  if(dbg) {
    Serial.print("My DHCP IP: ");
    for (byte thisByte = 0; thisByte < 4; thisByte++) {
      // print the value of each byte of the IP address:
      Serial.print(Ethernet.localIP()[thisByte], DEC);
      Serial.print("."); 
    }
    Serial.println();
  }
  
  // init MQTT connection
  while (client.connect("Garageduino") != 1) {
    Serial.println("Error connecting to MQTT");
    delay(3000);
  }

  // init Temp/Humidity Sensor
  dht.begin();
}

void loop() {
  dhtSensor();
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
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


