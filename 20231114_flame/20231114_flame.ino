int buzzPin = 13; // 有源蜂鳴器正極 連接到ESP32 GPIO13
int isFlamePin = 36; // 火焰感測器長端 連接到ESP32 GPIO36
int isFlame = 0; // 暫存來自傳感器的變量數值

void setup() {
 pinMode(buzzPin, OUTPUT);
 pinMode(isFlamePin, INPUT);
 Serial.begin(9600);
}

void loop() {
  isFlame = analogRead(isFlamePin);//類比讀
  Serial.println(isFlame);
  if (isFlame >= 50 )
  {
    Serial.println("FLAME, FLAME, FLAME");
    digitalWrite(buzzPin, HIGH);
  }
  else
  {
    Serial.println("no flame");
    digitalWrite(buzzPin, LOW);
  }
  delay(500);
}
