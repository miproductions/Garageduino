
#include "DHT.h"; // library for using the humidity and temperature sensor

int lightSensorVal = 0;
float temp = 0.0f; // stores the temperature
float humi = 0.0f; // stores the humidity
#define DHTTYPE DHT22 // needed for the humi/temp sensor
DHT dht(3, DHTTYPE); // initialises the humi/temp sensor
#define lightSensorAPinI 0 // reading light on 

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(13, OUTPUT); // onboard LED
  pinMode(4, OUTPUT); // red led
  pinMode(5, OUTPUT); // green led
  Serial.begin(9600); // lets the arduino talk to the computer
  dht.begin(); // starts the humi/temp sensor
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH); // turn on the onboard led
  digitalWrite(4, LOW); // turn off the red led
  digitalWrite(5, HIGH); // turn on the green led
  delay(500); // wait half a second
  digitalWrite(13, LOW); // turn off the onboard led
  digitalWrite(4, HIGH); // turn on the red led
  digitalWrite(5, LOW); // turn off the greed led
  delay(500); // wait half a second
  temp = dht.readTemperature(); // read the actual temperature from the sensor
  Serial.print("Temperature:");
  Serial.println(temp); // write the temp to the console
  humi = dht.readHumidity(); // read the actual humidity from the sensor
  Serial.print("Humidity:"); 
  Serial.println(humi); // write the humidity to the console
  lightSensorVal = analogRead(lightSensorAPinI);
  Serial.print("Light Value:");
  Serial.println(lightSensorVal);
}
