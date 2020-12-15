#include "WiFi.h"
#include "WiFiClient.h"
#include "LXESP32DMX.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Secrets.h"


#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

#define SENDPIN 17 //DMX Setup

const char* Name = SECRET_SSID;
const char* Password = SECRET_PASSWORD;

WiFiClient client;
WiFiServer wifiServer(80);

void setup() {
  Serial.begin(115200);
 
  ConnectToWiFi();
  wifiServer.begin();

   //-----Start DMX control output
   ESP32DMX.startOutput(SENDPIN); //start the transmission
}

void loop() {
  WiFiClient client = wifiServer.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"242255000000000255255/F\">here</a> to turn ON the LED RED.<br>");
            client.print("Click <a href=\"242000255000000255000255/F\">here</a> to turn ON the LED GREEN.<br>");
            client.print("Click <a href=\"000000000000000000000000/F\">here</a> to turn OFF all the LED.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        
        // Check to see if the client request was "GET /F":
        if (currentLine.endsWith("/F")) {
          //Transmission is finished, parse it: ends with /F
          String temp;
          // pt = strtok(currentLine, "c");
          int count = 1;
          //Remove GET/
          currentLine = currentLine.substring(5);

          //While numbers in currentLine
          while(!currentLine.startsWith("/F")){
            temp = currentLine.substring(0,3);
            currentLine = currentLine.substring(3);
            // Serial.print(currentLine);
            // Serial.print(" ");
            int a = temp.toInt();
            ESP32DMX.setSlot(count++, a);
            // Serial.print("Setting to: ");
            // Serial.println(a);
          }
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
/*
  //set channels
  const float freq = 1.5; //Hz
  static const long int init_t = millis(); //initaial time stamp
  static const int init_r = 255;
  static const int inti_g = 255;
  static const int init_b = 0;
  
  
  int r            = sin((millis() - init_t)/1000.0*freq)*init_r/2.0 +init_r/2.0;
  int g            = inti_g;
  int b            = init_b;
  
  ESP32DMX.setSlot(1, 242);
  
  ESP32DMX.setSlot(2, r);
  ESP32DMX.setSlot(3, g);
  ESP32DMX.setSlot(4, b);

  //-----serial communication
  int serial_refresh_rate = 999; //ms
  
  if ((int(millis()- init_t) % serial_refresh_rate ) < 1){
    
    Serial.print("red channel: "); Serial.println(r);
    Serial.print("green channel: "); Serial.println(g);
    Serial.print("blue channel: "); Serial.println(b); Serial.print("\n");
  }
  */
  
}

void ConnectToWiFi()
{
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(Name, Password);
  Serial.print("Connecting to "); 
  Serial.println("The Promised LAN");
 
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
 
    if ((++i % 16) == 0)
    {
      Serial.println(F(" still trying to connect"));
    }
  }
 
  Serial.print(F("Connected. My IP address is: "));
  Serial.println(WiFi.localIP());
}
