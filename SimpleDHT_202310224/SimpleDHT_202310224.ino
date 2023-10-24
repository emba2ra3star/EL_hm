#include <SimpleDHT.h> 

int pinDHT11 = 15; //ESP32 GPIO15
SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600);
}

void loop() {
    // start working...
    Serial.println("=============");   
    Serial.println("Sample DHT11 ……");   
    // read without samples
    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
       Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
       return;
    }
    Serial.print("Sample OK: ");   
    Serial.print("Temperature = ");   
    Serial.print((int)temperature);   
    Serial.println("*C, ");
    Serial.print("Humidity = ");   
    Serial.print((int)humidity);   
    Serial.print("%.");   

    delay(3000);  //每3秒顯示一次
}