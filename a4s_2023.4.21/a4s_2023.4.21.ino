#define trigPin 6
#define echoPin 7
#define buzzer 11
#define button 0

int frequency[7] = {524,588,660,698,784,880,988};
String Tone[7] = {"DO","RE","MI","FA","SO","LA","SI"};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(button,INPUT);
}

void loop() {
  int note = map (UltrasonicSensor(),300,700,0,6);
  Serial.println(Tone[note]);
  if(digitalRead(button)){
    tone(buzzer,frequency[note],150);
  }
  delay(125);
}

int UltrasonicSensor() //Ultrasonic Sensor Code Auto Generated Return CM max distance 200
{
  long duration;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration;
}
