int pin[7] = {13,11,10,9,6,5,3};
int order = 0;
void initLED(){
  for(int i=0;i<7;i++){
    pinMode(pin[i],OUTPUT);
  }
}
  
void wave(int cycle,int max,int min,int delayms){ //normal state - cycle=7 max=255 min=125 delayms = 100
  for(int i=0;i<7;i++){
    int brightness=(max-min)/2*(sin(2*PI/cycle*(i+order)))+(max+min)/2;
    analogWrite(pin[i],brightness);
    //Serial.print(brightness);
    //Serial.print(" ");
  }
  order++;
  delay(delayms);
  //Serial.println("");
}

int readValue() {
  String num = "";
  int i = 0 ;
  int n;
  while (Serial.available()) { //如果有輸入 則進行紀錄
    if (i == 0) {
      num = "";
    }
    num += Serial.read() - 48; // -48是要將ASC II 碼轉換為數字
    i++;
  }
  n = num.toInt();
  return n;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(10);
  initLED();
  delay(3000);
}

int c=0,temp_c;
int mx=0,temp_mx;
int mn=0,temp_mn;
int d=0,temp_d;
void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("輸入週期  (以幾顆LED作為一次波動週期)  ");
  while(1){
    if(Serial.available()){
      temp_c = readValue();
      Serial.println(temp_c);
      break;
    }
    wave(c,mx,mn,d);
  }
  Serial.print("輸入最大亮度  (0~255 LED的最大亮度)  ");
  while(1){
    if(Serial.available()){
      temp_mx = readValue();
      Serial.println(temp_mx);
      break;
    }
    wave(c,mx,mn,d);
  }
  Serial.print("輸入最小亮度  (0~255 LED的最小亮度)  ");
  while(1){
    if(Serial.available()){
      temp_mn = readValue();
      Serial.println(temp_mn);
      break;
    }
    wave(c,mx,mn,d);
  }
  Serial.print("輸入延遲ms  (LED顏色改變的延遲時間)  ");
  while(1){
    if(Serial.available()){
      temp_d = readValue();
      Serial.println(temp_d);
      break;
    }
    wave(c,mx,mn,d);
  }
  c=temp_c;
  mx=temp_mx;
  mn=temp_mn;
  d=temp_d;
  Serial.print("\n");
}
