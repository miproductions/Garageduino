/*
 * When activated, blinks red and green LEDs
 * By Thomas
 */

void setup() {
  // put your setup code here, to run once:
  // initialise digital pin 10 and 11 as output
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(13, LOW);
  delay(1000);

  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(13, LOW);
  delay(1000);

  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(13, HIGH);
  delay(1000);
  
  
  

}
