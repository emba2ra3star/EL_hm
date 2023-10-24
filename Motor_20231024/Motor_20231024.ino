#include <Arduino.h>
#include <ESP32Servo.h> 
Servo myservo;
int servoPin = 15;
int pos = 0; // 定義舵機轉動位置

void setup()
{
  myservo.attach(servoPin, 500, 2500); // 設置舵機控制腳位，並設置最小與最大脈寬
  Serial.begin(921600);                // 設置序列埠鮑率
  int init_angle = myservo.read();     // 讀取舵機初始角度
  if (init_angle != pos)
  {
    myservo.write(pos);
    delay(2000);
  };
}

void loop()
{
  // 0到180旋轉舵機，每次延時15毫秒
  for(pos = 0; pos < 180; pos += 1) { 
    myservo.write(pos); 
    delay(15); 
    } 
  // 180到0旋轉舵機，每次延時15毫秒 
  for(pos = 180; pos>=1; pos-=1)    {                               
    myservo.write(pos);
    delay(15);
    }
}