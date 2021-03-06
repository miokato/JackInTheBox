#include <Arduino.h>
#include <Servo.h>
void runMode(int state);
void setup();
void loop();
int smoothFilter(int *buf, int raw, int _index);
#line 1 "src/sketch.ino"
//#include <Servo.h>

#define CDS 0
#define BUF_LENGTH 10 
#define THRESHOLD 50
#define HYSTERESIS 20

// state
#define FAR 0
#define NEAR 1

Servo myservo;


void runMode(int state){
  switch(state){
    case FAR:
      myservo.write(30);
      break;
    case NEAR:
      myservo.write(120);
      break;
    default:
      break;
  }
}

void setup() {
  myservo.attach(9);
  myservo.write(30);
  Serial.begin(9600);
}

void loop() {
  // sensor value buffer
  static int buffer[BUF_LENGTH];
  static int index = 0;

  // state
  static int state = FAR;
  static boolean wasNear = false;
  boolean isNear = wasNear;
  
  int raw = analogRead(CDS);
  int smoothedValue = smoothFilter(buffer, raw, index);

  // state change if smooth value is less than THRESHOLD
  if(smoothedValue > (THRESHOLD + HYSTERESIS)){
    isNear = true;
  } else if(smoothedValue < (THRESHOLD - HYSTERESIS)){
    isNear = false;
  } else {
  }  

  if(!wasNear && isNear){
    myservo.write(90);
    Serial.println("state = near");
  } else if(wasNear && !isNear){
    myservo.write(30);
    Serial.println("state = far");
  }
  wasNear = isNear;

  //Serial.print("raw value is : ");
  //Serial.print(raw);
  //Serial.print('\t');
  //Serial.print("smoothed value is : ");
  //Serial.println(smoothedValue);
  delay(6);
}

// smooth filter
int smoothFilter(int *buf, int raw, int _index){
  int static index = _index;
  buf[index] = raw;
  index = (index + 1)%BUF_LENGTH;
  long sum = 0;
  for (int i=0; i<BUF_LENGTH; i++){
    sum += buf[i];
  }
  return (int)(sum / BUF_LENGTH);
}



