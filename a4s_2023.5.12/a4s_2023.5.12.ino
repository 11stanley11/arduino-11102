#include <Keyboard.h>
#include <LiquidCrystal_I2C.h>
#define VR A5 //variable resistance
#define button 7

LiquidCrystal_I2C   lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button,INPUT);
  Keyboard.begin();
  lcd.init();//初始化LCD
  lcd.backlight();//開啟背光
  lcd.setCursor(3,0);
  lcd.print("0123456789");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(button));
  int index = map (analogRead(VR),0,1024,0,10);
  lcd.setCursor(3+index,0);
  lcd.blink();
  if(digitalRead(button)){
    Keyboard.print(String(index));
    delay(500);
  }
}
//
