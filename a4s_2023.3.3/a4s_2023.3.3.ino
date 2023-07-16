#include "a4s_2023.3.3.h"
#define R 12
#define G 11
#define B 10

void RGB(bool Red,bool Green,bool Blue){
  digitalWrite(R,Red);
  digitalWrite(G,Green);
  digitalWrite(B,Blue);
}

int ranColor(){
  String colors = "RGBYCPW";
  return int(colors[int(random(7))]);
}

void colorSwitch(int c){
  switch(c){
    case int('R'):
      RGB(1,0,0);
      break;
    case int('G'):
      RGB(0,1,0);
      break;
    case int('B'):
      RGB(0,0,1);
      break;
    case int('Y'):
      RGB(1,1,0);
      break;
    case int('C'):
      RGB(0,1,1);
      break;
    case int('P'):
      RGB(1,0,1);
      break;
    case int('W'):
      RGB(1,1,1);
      break;
    default:
      RGB(0,0,0);
      break;
  }
}

int temp=0;
int readChar() {
  while (Serial.available()) { //如果有輸入 則進行紀錄
    return Serial.read();
    /*if(temp!=c){
      colorSwitch(c);
      temp = c;
    }*/
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);
  randomSeed(analogRead(0));
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  delay(3000);
  Serial.println("------------Guess the right color------------");
  Serial.println("R = Red , G = Green , B = Blue , Y = Yellow ,");
  Serial.println("C = Cyan , P = Pink , W = White");
  Serial.println("---------------------------------------------");
}                 

int correct=0,times=0;

void loop() {
  // put your main code here, to run repeatedly:
  int c;
  c = ranColor();
  colorSwitch(c);
  Serial.print("Q");
  Serial.print(times+1);
  Serial.println(":");
  while (1) {
    if (Serial.available()) {
      if (readChar() == c){
        Serial.print("Correct!");
        correct++;
      }
      else Serial.print("Wrong!");
      times++;
      break;
    }
  }
  Serial.print("  The answer is ");
  Serial.println(char(c));
  Serial.print("Score: ");
  Serial.print(correct);
  Serial.print(" / ");
  Serial.println(times);
  Serial.println("---------------------------------------------");
}
