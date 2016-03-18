#include <Arduino.h>
#include <servo.h>
void setup();
void loop();
void doServo(char a);
#line 1 "src/sketch.ino"
//#include <servo.h>

Servo servo;

void setup()
{
  Serial.begin(9600);
  servo.attach(9);
  servo.write(20);
}

void loop()
{
  doServo(Serial.read());
}

void doServo(char a){
  switch(a){
    case 'a':
      servo.write(20);
      delay(50);
      break;
    case 's':
      servo.write(90);
      delay(50);
      break;
    case 'd':
      servo.write(160);
      delay(50);
      break;
    default:
      break;
  }
}

