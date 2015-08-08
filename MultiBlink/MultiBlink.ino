/*
 * When activated, blinks red and green LEDs
 * By Thomas
 */

#define _pause 200
#define _shortPause 50

void setup() {
  // put your setup code here, to run once:
  // initialise digital pin 10,11 and 13 as output
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(13, HIGH);
  delay(_pause);

  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(13, LOW);
  delay(_pause);

  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(13, LOW);
  delay(_pause);

  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(13, LOW);
  delay(_shortPause);

  
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(13, LOW);
  delay(_pause);
  

  
  
  
  

}
