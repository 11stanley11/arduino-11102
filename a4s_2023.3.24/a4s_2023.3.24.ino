#include "Mouse.h"
#define xAxis A0
#define yAxis A1
#define button 2
#define R 9
#define G 6
#define B 5

int xyInit[2] = {332,195};    // 滑鼠XY在中心的初始位置
int range = 36;               // XY方向上的移動範圍
int threshold = 1;      // 偵測是否移動的門檻值
int center = range/2;         // 範圍的中間值
int axis[] = {xAxis, yAxis};  // 在 x, y 軸上所使用的腳位
int mouseReading[2];          // 滑鼠的 x, y 座標
int responseDelay[3] = {30,10,2};        // 滑鼠的響應時間（單位：毫秒）
int cursorSpeed = 0;
 
void setup() {
  Serial.begin(9600);
  Mouse.begin();
  Mouse.move(xyInit[0],xyInit[1],0); //將滑鼠定位到初始位置
  pinMode(button,INPUT);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
}
 
void loop() {
  //讀取xy需移動的距離
  if(digitalRead(button)){
    cursorSpeed++;
    delay(500);
  }
  switch(cursorSpeed%3){
    case 0:
      LED(0,100,0);
      break;
    case 1:
      LED(100,100,0);
      break;
    case 2:
      LED(100,0,0);
      break;
  }
  int xReading = readAxis(0);
  int yReading = readAxis(1);
 
  Serial.print(xReading);
  Serial.print(" ");
  Serial.println(yReading);
  Mouse.move(xReading,yReading,0);
  delay(responseDelay[cursorSpeed%3]);
}

int readAxis(int axisNumber) {
  int distance = 0; // 滑鼠的移動距離
  int reading = analogRead(axis[axisNumber]); // 讀取類比輸入
  reading = map(reading,0, 1024, 0, range); // 將讀值重新映射
  if (abs(reading - center) > threshold) {  // 假如輸出讀值已經超過移動的門檻值
    distance = (reading - center);          // 則計算距離中心點的長度:
  } 
  if (axisNumber == 1) {  // 為了能正確的映射出移動距離，Y 軸的值需要乘上 -1
    distance = -distance;
  }
  return distance;  // 回傳該軸的移動距離
}

void LED(int Red,int Green,int Blue){
  analogWrite(R,Red);
  analogWrite(G,Green);
  analogWrite(B,Blue);
}
