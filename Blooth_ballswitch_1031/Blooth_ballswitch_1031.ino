#include <BluetoothSerial.h> 
BluetoothSerial SerialBT; 

int  tiltPin = 2; //定義變數tiltPin為2，傾斜感測器使用D2接腳
int  ledPin = 16; //定義變數ledPin為16，LED使用D16接腳
int  value; //宣告value變數。


void setup() {
  Serial.begin(9600);
  SerialBT.begin("1212"); 
  pinMode(ledPin,OUTPUT); //設定ledPin的接腳為輸出模式
  pinMode(tiltPin,INPUT); //設定tiltPin的接腳為輸入模式
}

void loop() {
  value = digitalRead(tiltPin);
  Serial.println(value);
  //若value等於1，則點亮ledPin上的LED；否則熄滅ledPin上的LED
  
    if (value == 1){
    digitalWrite(ledPin,HIGH);
    SerialBT.println("1");
        
  }else{
    digitalWrite(ledPin,LOW);
    SerialBT.println('c');
  }
  delay(500);
  
  
}