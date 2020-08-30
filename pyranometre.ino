/*
  Station Meteo Pro - module pyranomètre
  avec : 
     - NodeMCU
     - DS18B20

 Cablage DS18B20 :
 VCC - 3V
 GND - GND 
 DATA - D4

  
  Source :     https://www.sla99.fr
  Site météo : https://www.meteo-four38.fr
  Date : 2019-09-05

  Changelog : 
  26/04/2020  v1    xx initiale

*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DallasTemperature.h>

#define LED 14 //D5
  
const char* ssid = "xxxxx";
const char* password = "xxxxx";
char server[] = "192.168.1.2";  
WiFiClient client;
String KEY_WS="134567654345670012";
const int DS18B20 = 2; //D4
 
  
void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(LED, OUTPUT); 
   
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());   
  Serial.println(WiFi.macAddress());

  OneWire oneWire(DS18B20);
  DallasTemperature sensors(&oneWire);
  sensors.begin();
  sensors.requestTemperatures(); // Send the command to get temperatures
  double temp = sensors.getTempCByIndex(0);


  String url = "/stationmeteo/pyrano.php?key="+KEY_WS+"&temp="+String(temp);
 
  HTTPClient http;  
  String Link = "http://192.168.1.2:81"+url;
   
  http.begin(Link); 
   
  int httpCode = http.GET();          
  String payload = http.getString();  
  
  Serial.println(httpCode);   
  Serial.println(payload);  
  
  http.end(); 

  digitalWrite(LED, HIGH);
  delay(250);
  digitalWrite(LED, LOW);
  delay(250);
  digitalWrite(LED, HIGH);
   
  Serial.println("Going into deep sleep for 60 seconds");
  ESP.deepSleep(60e6); 
  
}
  
void loop() {


}
