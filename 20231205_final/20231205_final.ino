#include <WiFi.h>
#include <HTTPClient.h>
#include <SimpleDHT.h>
#include <BluetoothSerial.h>

//請修改以下參數--------------------------------------------
const char ssid[] = "Hosialpha";              //ssid:網路名稱
const char password[] = "19910820";  //password:網路密碼
//請修改為你自己的API Key，並將https改為http
String url = "http://api.thingspeak.com/update?api_key=87GC77FS09TSWON9";
//----------wifi--------
BluetoothSerial SerialBT;
//-------------------------------setPin-------------------------------
//----------DHT11----------
int pinDHT11 = 15;  //假設DHT11接在腳位GPIO15
//---------wifi------------
int led_1 = 16;  // LED
//----------FLAME----------
int buzzPin = 13;     // 有源蜂鳴器正極 連接到ESP32 GPIO13
int isFlamePin = 36;  // 火焰感測器長端 連接到ESP32 GPIO36
int isFlame = 0;      // 暫存來自傳感器的變量數值
int button = 22;

//---------------------------------------------------------
SimpleDHT11 dht11(pinDHT11);  //宣告SimpleDHT11物件

//-----------------------公用變數區----------------------------------
byte temperature = 0;
byte humidity = 0;
bool SendFlag = false;
byte previousState=1, presentState=1,patternNumber=0;

void setup() {
  Serial.begin(115200);
  Serial.print("開始連線到無線網路SSID:");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("連線完成");

  //-----wifi-------
  pinMode(led_1, OUTPUT);
  SerialBT.begin("ESP32_BT");  //更改為設定的藍牙顯示名稱
  //-----FLAME------
  pinMode(buzzPin, OUTPUT);
  pinMode(isFlamePin, INPUT);
  pinMode(button,INPUT);
}

void loop() {
  Serial.println("==========");

  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("溫度計讀取失敗，錯誤碼="); Serial.println(err); 
    delay(1000);
    return;
  }
  //讀取成功，將溫濕度顯示在序列視窗
  Serial.print("溫度計讀取成功: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println("%H");
  //開始傳送到thingspeak
  Serial.println("啟動網頁連線");
  HTTPClient http;
  //將溫度及濕度以http get參數方式補入網址後方
  String url1 = url + "&field1=" + (int)temperature + "&field2=" + (int)humidity;
  //http client取得網頁內容
  http.begin(url1);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)      {
    //讀取網頁內容到payload
    String payload = http.getString();
    //將內容顯示出來
    Serial.print("網頁內容=");
    Serial.println(payload);
  } else {
    //讀取失敗
    Serial.println("網路傳送失敗");
  }
  http.end();

  isFlame = analogRead(isFlamePin);  
  Serial.println(isFlame);
  presentState=digitalRead(button);
  Serial.println(presentState);
  if(presentState == 0 && previousState == 1){patternNumber=!patternNumber;}//set buzz
  if (isFlame >= 50 && temperature>=30) {
    SerialBT.print("有火災");
    if(patternNumber)digitalWrite(buzzPin,LOW);
    else digitalWrite(buzzPin, HIGH);    
    digitalWrite(led_1, HIGH);    
  }    
  else if(isFlame >= 50 && temperature<30 ){
    SerialBT.print("有人在玩火");
    digitalWrite(buzzPin, LOW);
    digitalWrite(led_1, LOW);  
    patternNumber=0;
  }
  else {
    SerialBT.print("沒事");
    digitalWrite(buzzPin, LOW);
    digitalWrite(led_1, LOW);  
    patternNumber=0;
  }
  Serial.println(patternNumber);


  delay(3000);  //休息3秒
  previousState=presentState;  
}
