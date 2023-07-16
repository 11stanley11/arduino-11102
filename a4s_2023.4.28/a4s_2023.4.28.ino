#include <Servo.h>
#define SERVO_PIN 10 //伺服馬達腳位
#define vr A5

Servo myservo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(vr,INPUT);
  myservo.attach(SERVO_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = map(analogRead(vr),0,1023,0,180);
  Serial.println(value);
  myservo.write(value);
}
