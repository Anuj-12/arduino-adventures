#include <Servo.h>

Servo servo;

int servoPin = 3;
int rightLight = A0;
int leftLight = A5;
int no = 5;

int leftVal;
int rightVal;
float difference;
float normalisedDiff;
float servoPos;

void setup() {

  servo.attach(servoPin);
  pinMode(leftLight, INPUT);
  pinMode(rightLight, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  
//  servo.write(90);

  leftVal = analogRead(leftLight);
  rightVal = analogRead(rightLight);
  difference = leftVal - rightVal;
//  normalisedDiff = difference / 725.;

  Serial.print("Left = ");
  Serial.println(leftVal);
  Serial.print("Right = ");
  Serial.println(rightVal);

  if(difference < -5 || difference > 5){
    servoPos = ((90./725.) * (difference - 5)) + 90;
  } else{
         
  }

//  Serial.println(difference);
//  Serial.println(normalisedDiff);
  Serial.println(servoPos);
//  servoPos = 90;
  servo.write(servoPos);

//  delay(250);
}
