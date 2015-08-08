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

#define erPin 13
#define trPin 10
#define ecPin 11
#define ping 100
#define ok 20
#define tmg 58.2
#define omsg " open"
#define cmsg " closed"
#define emsg "error"
void setup() {
  Serial.begin (9600);
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
    Serial.println(emsg);
  } else if (dist < ok) {
    // door is open
    digitalWrite(erPin,HIGH);
    delay(100);
    digitalWrite(erPin,LOW);
    Serial.print(dist);
    Serial.println(omsg);
  } else {
    // door is closed
    digitalWrite(erPin,LOW);
    Serial.print(dist);
    Serial.println(cmsg);
  }
  delay(ping);
}
