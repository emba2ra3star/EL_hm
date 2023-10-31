#include <BluetoothSerial.h> 
BluetoothSerial SerialBT; 

int led_1 =16; // LED 
int led_2=15;
void setup() {
  Serial.begin(9600);
  pinMode(led_1, OUTPUT);
    pinMode(led_2, OUTPUT);

  SerialBT.begin("1212");//更改為設定的藍牙顯示名稱
}

void loop() {
  String value;
  if (SerialBT.available()) {
    value = SerialBT.readString();
    if(value == "1"){
      //收到1，開啟LED
      digitalWrite(led_1,HIGH);
      digitalWrite(led_2,LOW);

      Serial.println("收到1，開啟LED");
    }
    if(value == "2"){
      //收到2，關閉LED
      digitalWrite(led_1,LOW);
      digitalWrite(led_2,HIGH);

      Serial.println("收到2，關閉LED");
    }
  }
  delay(500);
}
