#define vr A5
#define mp 5 //motor positive
#define mn 6 //motor negative

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(vr,INPUT);
  pinMode(mp,OUTPUT);
  pinMode(mn,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   int value = map(analogRead(vr),0,1023,-250,250);
   Serial.println(value);
   if(value>=0){
    analogWrite(mp,abs(value));
    analogWrite(mn,0);
   }else{ 
    analogWrite(mp,0);
    analogWrite(mn,abs(value));
   }
}
