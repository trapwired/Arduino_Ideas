#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "Secrets.h"

// Secrets
const char* ssid = SECRET_SSID; //your WiFi Name
const char* password = SECRET_PASSWORD;  //Your Wifi Password
const char* http_request = SECRET_TELEGRAM_LINK;

// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "f2 ad 29 9c 34 48 dd 8d f4 cf 52 32 f6 57 33 68 2e 81 c1 90";

const char* host = "api.telegram.org";
const int httpsPort = 443;

// Pinout
int ledPin = D3; 
const int voltageSensor = A0;

// vars
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;


void setup() {
  Serial.begin(115200);
  delay(10); 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 
  Serial.println();
  
  setupWiFi();
}

void loop() {
  value = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 1024.0;
  vIN = vOUT / (R2/(R1+R2));
  if (vIN > 1.9){
    sendDingDong("DingDong");
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
  }
}

void setupWiFi(){
  Serial.print("Connecting to ");
  Serial.println(ssid); 
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}

void sendDingDong(char *msg){
  if(WiFi.status()== WL_CONNECTED){
    // Use WiFiClientSecure class to create TLS connection
    WiFiClientSecure client;
    client.setInsecure();
    client.setFingerprint(fingerprint);

    if (!client.connect("api.telegram.org", 443)) {
      Serial.println("connection failed");
      return;
    }

    String url = SECRET_TELEGRAM_LINK_PARTIAL + String(msg);
  
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

    Serial.println("request sent");
    client.stop();
  } else {
    // reconnect
    setupWiFi();
    sendDingDong("DingDong");
  }

}
