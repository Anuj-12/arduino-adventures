#include <LiquidCrystal.h>

const int rs = 3, en = 2, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int hourPin = 7;
const int minPin = 8;
const int resetPin = 6;
const int buzzPin = 4;
const int contrastPin = A5;

int hourCount = 0;
int minCount = 0;

// Debounce variables
const int debounceDelay = 50;
unsigned long lastDebounceTime = 0;
boolean hourButtonPressed = false;
boolean minButtonPressed = false;
boolean resetButtonPressed = false;
boolean isTimer = false;

unsigned long startTime;

void setup() {
  pinMode(hourPin, INPUT_PULLUP);
  pinMode(minPin, INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);
  pinMode(buzzPin, OUTPUT);
  pinMode(contrastPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(6, 1);

  Serial.begin(9600);
}

void loop() {
  analogWrite(contrastPin, 0);

  // Debounce buttons
  unsigned long currentMillis = millis();
  if (currentMillis - lastDebounceTime >= debounceDelay) {
    lastDebounceTime = currentMillis;

    int reading = digitalRead(hourPin);
    hourButtonPressed = (reading == LOW);

    reading = digitalRead(minPin);
    minButtonPressed = (reading == LOW);

    reading = digitalRead(resetPin);
    resetButtonPressed = (reading == LOW);
  }

  if (resetButtonPressed) {
    isTimer = false;
    hourCount = 0;
    minCount = 0;
    lcd.clear();
    lcd.setCursor(6, 1);
    lcd.print("00:00");
    digitalWrite(buzzPin, LOW);
  } else {
    if (hourButtonPressed) {
      isTimer = true;
      startTime = millis();
      hourCount++;
      if (hourCount >= 24) {
        hourCount = 0;
      }
      delay(250); // Add a small delay to prevent rapid button presses
    }

    if (minButtonPressed) {
      isTimer = true;
      startTime = millis();
      minCount += 5;
      if (minCount >= 60) {
        minCount = 0;
        hourCount++;
        if (hourCount >= 24) {
          hourCount = 0;
        }
      }
      delay(250); // Add a small delay to prevent rapid button presses
    }

    // Format time and display
    lcd.setCursor(6, 1);
    lcd.print(hourCount < 10 ? "0" : "");
    lcd.print(hourCount);
    lcd.print(":");
    lcd.print(minCount < 10 ? "0" : "");
    lcd.print(minCount);
  }


  if(isTimer && countdown(minCount, hourCount)){
    digitalWrite(buzzPin, HIGH);
  }

  // Serial.println(startTime);
}

boolean countdown(int minutes, int hours){

  unsigned long seconds = (millis() - startTime) /1000;
  int minutesTarget = minutes + (hours * 60); //Total number of minutes to reach
  minutes = seconds / 60; //minutes after starting the timer
  
  if(isTimer = true){

    minutesTarget -= minutes;

    lcd.setCursor(0,0);
    lcd.print("Minutes Left:");
    lcd.print(minutesTarget);

    Serial.println(minutesTarget);
    
    return minutesTarget == 0 ? true : false;
  }

  return false;
}
