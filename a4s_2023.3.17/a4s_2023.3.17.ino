#define B 9 //button
int LED[7] = {8,7,6,5,4,3,2};

int startTime;

bool buttonUp = true;
bool buttonPress(){
  bool buttonState = digitalRead(B);
  if(buttonState && buttonUp) buttonUp = false;
  else if (!buttonState && !buttonUp){
    buttonUp = true;
    return true;
  }else return false;
}

void Ledlevel(int number){
  for(int i=0;i<number;i++){
    digitalWrite(LED[i],HIGH);
  }
  for(int i=6;i>=number;i--){
    digitalWrite(LED[i],LOW);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(B,INPUT);
  for(int i=0;i<7;i++){
    pinMode(LED[i],OUTPUT);
  }
}

int buttonPressTime = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if(buttonPress()){
    startTime = millis();
    buttonPressTime++;
    while(1){
      if(buttonPress()) buttonPressTime++;
      int duration = (millis() - startTime+1000)/1000;
      int cps = buttonPressTime/2/duration;
      Serial.println(buttonPressTime/2);
      Ledlevel(cps);
    }
  }
  
}
