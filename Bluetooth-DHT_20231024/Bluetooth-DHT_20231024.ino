#include <SimpleDHT.h> 
#include <BluetoothSerial.h> 
BluetoothSerial SerialBT;
int pinDHT11 = 15; //ESP32 GPIO15
SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("Changhach"); //藍牙顯示名稱，可自行更改，需避免與他人重複命名
}

void loop() {
    // start working...
    Serial.println("=============");   
    Serial.println("Sample DHT11 ____");   
    // read without samples
    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
       Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
       return;
    }
    //texting
    if (Serial.available()) {
      SerialBT.write(Serial.read());
      
    }
    if (SerialBT.available()) {
      Serial.println(SerialBT.readString());
      
    }
    // 將溫溼度傳輸到藍芽裝置
    SerialBT.print((int)temperature);
    SerialBT.print("*C, ");
    SerialBT.print((int)humidity);
    SerialBT.println("%.");

    delay(1000);  //休息1秒
}