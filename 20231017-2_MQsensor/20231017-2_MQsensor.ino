int buzzpin=16;

void setup() {
  Serial.begin(9600);
  pinMode(13,INPUT);
  pinMode(buzzpin,OUTPUT);
}

void loop() {
  int gasValue;
  gasValue=analogRead(13);
  Serial.println(gasValue);
  
  if(gasValue>3000){
    digitalWrite(buzzpin,HIGH);
  }else{
    digitalWrite(buzzpin,LOW);
  }
  delay(100);
}
