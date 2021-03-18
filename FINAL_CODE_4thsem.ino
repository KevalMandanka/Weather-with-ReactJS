
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>


#include <LiquidCrystal_I2C.h>
#include <dht.h>
dht DHT;
#define DHT11_PIN 7

#define FIREBASE_HOST "arduino-weather-station-c087c.firebaseio.com"
#define FRIEBASE_AUTH "mPpOUEyy3qsNKADINaodYTGygFFOI27140x6RdPE"

#define WIFI_SSID "gliot"
#define WIFI_PASSWORD "GLIOT1212"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  //WIFI

  Serial.begin(9600);

  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("Connecting");

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(",");
    delay(500);
   
  }

   Serial.println();
   Serial.print("CONNECTED");
   Serial.print(WiFi.localIP());

   //FIREBASE

   Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
   delay(500);

  lcd.init();
  lcd.backlight();
  lcd.print("AURDINO WEATHER");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM PROJECT");
  Serial.begin(9600);

}

void loop() {

  int chk = DHT.read11(DHT11_PIN);

  float h = DHT.humidity;
  float t = DHT.temperature;

   Firebase.setString("hum/humVal",String(h));
   delay(300);
    Firebase.setString("temp/tempVal",String(t));
   delay(300);
  
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.print(t);
  lcd.print("C");

  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
  lcd.print(h);
  lcd.print("%");

  //lcd.noCursor();
  delay(1000);
  // lcd.blink();

}
