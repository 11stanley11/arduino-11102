#include <LiquidCrystal_I2C.h>
#define play 0
#define save 1
#define audio 11
#define VR A5 //variable resistance

LiquidCrystal_I2C   lcd(0x27, 16, 2);

const int AFmin = 0; //minimum audio frequency
const int AFmax = 1976; //maximum audio frequency
int frequency[22] = {50,262,294,330,349,392,440,494,
                     524,588,660,698,784,880,988,
                     1046,1175,1318,1397,1568,1760,1976};
String constNote[22] = {"X","0Do","0Re","0Mi","0Fa","0So","0La","0Si",
                        "1Do","1Re","1Mi","1Fa","1So","1La","1Si",
                        "2Do","2Re","2Mi","2Fa","2So","2La","2Si"};
int noteArr[100];
int noteArrSize = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(play,INPUT);
  pinMode(save,INPUT);
  pinMode(VR,INPUT);
  Serial.begin(9600);
  lcd.init();//初始化LCD
  lcd.backlight();//開啟背光
  lcd.setCursor(0,0);
}

int temp = -1;
void loop() {
  int value = analogRead(VR);
  int note = returnNoteNum(value);
  if(note != temp) {
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print(constNote[note]);
    temp = note;
  }
  if(digitalRead(save)){
    savePrintNoteArr(note);
    delay(1000);
  }
  if(digitalRead(play)){ 
    for(int i=0;i<noteArrSize;i++){
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print(constNote[noteArr[i]]); //print current note
      
      int currentNote = frequency[noteArr[i]];
      if(noteArr[i] != 0){
        tone(audio,currentNote,333);
      }
      delay(333); //play tone
    }
  }
}

int returnNoteNum(int VRvalue) {
  int order = -1;
  VRvalue = map(VRvalue,0,1025,AFmin,AFmax);
  for(int i=0;i<22;i++) {
    if(frequency[i]>=VRvalue) {
      int middle = frequency[i] + frequency[i+1];
      if(VRvalue<middle) order = i;
      else order = i+1;
      if(order>-1) return order;
    }
  }
}

void savePrintNoteArr (int note) {
  noteArr[noteArrSize] = note;
  noteArrSize++;
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  int printRange = 0;
  if(noteArrSize > 4) printRange = noteArrSize - 4;
  for(int i=printRange;i<noteArrSize;i++){
    lcd.print(constNote[noteArr[i]]);
    lcd.print(" ");
  }
}
