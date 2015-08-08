/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at: http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#define trigPin 13
#define echoPin 12
#define ledRed 11
#define ledGrn 10

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGrn, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  if (distance < 10) {
    // digitalWrite(ledRed,HIGH);
    digitalWrite(ledGrn,LOW);
  } else {
    // digitalWrite(ledRed,LOW);
    digitalWrite(ledGrn,HIGH);
  }
  
  if (distance >= 200 || distance <= 0){
    Serial.println("OUT OF RANGE");
    Serial.println("duration:" + duration);
    Serial.println("distance:" + distance);
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  
  delay(1000);
}
