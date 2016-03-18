#include <Arduino.h>
#include <Servo.h>
void setup();
void loop();
int smoothFilter(int *buf, int raw, int _index);
#line 1 "src/sketch.ino"
//#include <Servo.h>

#define CDS 0
#define BUF_LENGTH 10 
#define THRESHOLD 70

Servo myservo;

void setup() {
  myservo.attach(9);
  myservo.write(0);
  Serial.begin(9600);
}

void loop() {
  static int buffer[BUF_LENGTH];
  static int index = 0;
  static boolean state = false;
  
  int raw = analogRead(CDS);
  int smoothedValue = smoothFilter(buffer, raw, index);

  if(smoothedValue<THRESHOLD){
    myservo.write(180);
  } else {
    myservo.write(0);
  }

  if(state) {
    myservo.write(180);
  }

  Serial.print("raw value is : ");
  Serial.print(raw);
  Serial.print('\t');
  Serial.print("smoothed value is : ");
  Serial.println(smoothedValue);
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



