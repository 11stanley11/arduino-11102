#include <Servo.h>

#define ldr A0 //光敏
#define button 2 //按鈕
#define LED_R 11 //LED R
#define LED_G 6 //LED G
#define LED_B 5 //LED B
#define SERVO_PIN 10 //伺服馬達腳位

Servo myservo;

bool LEDState = false;
bool servoState = false;
bool servoStart = false;
long servoStartTime;
int servoDuration = 600;
int priority[9] = {1,1,2,1,3,4,2,3,1};
int order=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button,INPUT);
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_B,OUTPUT);
  initServo();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(button)){
    LEDState = !LEDState;
    delay(500);
  }
  if(LEDState) LED(10,10,10);
  else LED(0,0,0);
  int ldrValue=analogRead(ldr);
  Serial.println(ldrValue);
  if(ldrValue>920) servoStart = true;
  if(servoStart){   
    if(!servoState) {
      servoState = true;
      servoStartTime = millis();
    }
    servoMove();
  } 
}

void LED(int R,int G,int B){
  analogWrite(LED_R,R);
  analogWrite(LED_G,G);
  analogWrite(LED_B,B);
}

void initServo() {
  myservo.attach(SERVO_PIN);
  myservo.write(90); //初使角度
  delay(500);
}

void setServo(int Position_angle) {
  myservo.attach(SERVO_PIN);
  myservo.write(Position_angle);
}

void servoMove(){
  switch(priority[order]){
    case 1:
      if(millis() - servoStartTime > servoDuration){
        setServo(90);
        if(millis() - servoStartTime > 2*servoDuration){
          servoState = false;
          servoStart = false;
          order++;
          myservo.detach();
        }
      }
      else{
        setServo(0); 
      }
      break;
  case 2:
    if(millis() - servoStartTime > 2000){
      if(millis() - servoStartTime > servoDuration+2000){
        setServo(90);
        if(millis() - servoStartTime > 2*servoDuration+2000){
          servoState = false;
          servoStart = false;
          order++;
          myservo.detach();
        }
      }
      else{
         setServo(0);
      }
    }  
    break;
  case 3:
    if(millis() - servoStartTime > servoDuration){
      if(millis() - servoStartTime > 2*servoDuration+2000){
        if(millis() - servoStartTime > 3*servoDuration+2000){
          setServo(90);
          if(millis() - servoStartTime > 4*servoDuration+2000){
            servoState = false;
            servoStart = false;
            order++;
            myservo.detach();
          }
        }
        else{
          setServo(0);
        }
      }
      else{
        setServo(90);
      }
    }
    else{
       setServo(20);
    } 
    break;
  case 4:
    if(millis() - servoStartTime > servoDuration+2000){
      if(millis() - servoStartTime > 2*servoDuration+4000){
        if(millis() - servoStartTime > 3*servoDuration+4000){
          setServo(90);
          if(millis() - servoStartTime > 4*servoDuration+4000){
            servoState = false;
            servoStart = false;
            order++;
            myservo.detach();
          }
        }
        else{
          setServo(0);
        }
      }
      else{
        setServo(90);
      }
    }
    else{
       setServo(20);
    } 
    break;
  }
}
