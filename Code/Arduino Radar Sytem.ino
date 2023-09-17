#include <Servo.h>
#include <LiquidCrystal.h>

const int triggerPin=11;
const int ecoPin=12;
const int buzzer = 13;
int count = 0;
int prev = 100;
const int rs = 9, en = 10, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

long duration;
int distance;

Servo myServo;

void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(ecoPin, INPUT);
  pinMode(buzzer,OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Arduino Radar");

  myServo.attach(8);
}

void loop() {
  count = 0;
  for(int i = 15; i <= 165; i++){  
    myServo.write(i);
    delay(50);

    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print("\n");

    if(distance <= 40){
      digitalWrite(buzzer,HIGH);
    }else{
      digitalWrite(buzzer,LOW);
    }

    if(distance <= 40 && i == 15){
      count++;
    }
    else if(distance <= 40 && prev >= 40){
      count++;
    }
    else {
      count = count;
    }
    prev = distance;
  }

  lcd.clear();
  lcd.print(count);
  lcd.print(" OBJECTS FOUND");
  delay(2000);

  count = 0;
  for(int i = 165; i >= 15; i--){  
    myServo.write(i);
    delay(50);

    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print("\n");

    if(distance <= 40){
      digitalWrite(buzzer,HIGH);
    }else{
      digitalWrite(buzzer,LOW);
    }

    if(distance <= 40 && i == 165){
      count++;
    }
    else if(distance <= 40 && prev >= 40){
      count++;
    }
    else {
      count = count;
    }
    prev = distance;
  }

  lcd.clear();
  lcd.print(count);
  lcd.print(" OBJECTS FOUND");
  delay(2000);
}

int calculateDistance(){
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(triggerPin, LOW);

  duration = pulseIn(ecoPin, HIGH);
  distance = (duration*0.034)/2;

  return distance;
}