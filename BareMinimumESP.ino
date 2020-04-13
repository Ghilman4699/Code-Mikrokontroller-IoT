#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "parse_merge.h"

// Global variable
ESP8266WebServer server(80);

// Web Handle Here
void web_handle_root(){
  Serial.println("REQ");
  
  String web = "";
  web += "<strong> Contoh Monitoring </strong>";
  web += "<ul>";
  web += "\t<li>RFID\t: " +DATA_STR(0)+ "</li>";
  web += "\t<li>MQ2\t: " +DATA_STR(1)+ "</li>";
  web += "\t<li>Pintu\t: " +DATA_STR(2)+ "</li>";
  web += "</ul>";
  
  server.send(200, "text/html", web);
}

// Function declaration
void WiFi_Connect(String data_ssid, String data_pwd){
  bool stat = false;
  int elapsed_time = 0;
  
  Serial.println("[*] Connecting..");
  elapsed_time = millis();
  WiFi.begin("Rumah", "Khususrahmabayar2000");
  Serial.print('[');
  while(WiFi.status() != WL_CONNECTED){
    if( (((millis() - elapsed_time)/1000)) > 20 ){
      stat = false;
      break;
    }
    
    Serial.print('*');
    stat = true;
    delay(50);
  }
  Serial.println(']');
  
  if(stat){
    Serial.println("[+] Connected!");
    Serial.println("[*] " + WiFi.localIP().toString());
  }else
    Serial.println("[-] Error while connecting to WiFi!");
}

void setup(){
  Serial.begin(115200);
  WiFi_Connect("Rumah", "Khususrahmabayar2000");
  
  server.on("/", web_handle_root);
  server.begin();
}

void loop(){
  if(Serial.available() > 0){
    data = Serial.readStringUntil('\n');
    parse_string();
  }
  
  server.handleClient();
}
