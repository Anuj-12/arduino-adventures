#include <Servo.h>

int servoPin = 9;
int lightPin = A5;

int lightVal;
int servoPos;

Servo servo;

void setup() {

  servo.attach(servoPin);

  pinMode(lightPin, INPUT);

  Serial.begin(9600);
}

void loop() {

  lightVal = analogRead(lightPin);
//  Serial.println(lightVal);
  
  servoPos = (180./870.) * (lightVal -120); 
  Serial.println(servoPos);
  servo.write(servoPos);
} 
