#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "parse_merge.h"

// Global variable
ESP8266WebServer server(80);

// Web Handle Here
void web_handle_root(){
  String web = "";
  
  server.send(200, "text/html", web);
}

// Function declaration
void WiFi_Connect(String data_ssid, String data_pwd){
  bool stat = false;
  int elapsed_time = 0;
  
  Serial.println("[*] Connecting..");
  elapsed_time = millis();
  WiFi.begin(data_ssid.c_str(), data_pwd.c_str());
  Serial.print('[');
  while(WiFi.status() != WL_CONNECTED){
    if( ((elapsed_time/1000) - (millis()/1000)) > 10 ){
      stat = false;
      break;
    }
    
    Serial.print('*');
    stat = true;
    delay(150);
  }
  Serial.print(']');
  
  if(stat)
    Serial.println("[+] Connected!");
  else
    Serial.println("[-] Error while connecting to WiFi!");
}

void setup(){
  Serial.begin(115200);
  WiFi_Connect("myWiFiName", "myWiFiPwd");
  
  // Fill empty array
  for(int x=0;x<6;x++)
    data_array[x] = "000";
  
  server.on("/", web_handle_root);
}

void loop(){
  if(Serial.available() > 0){
    data = Serial.readStringUntil('\n');
    parse_string();
  }
  
  //server.handleClient();
  Serial.println("\nTotal data : " + String(get_data_total()));
  Serial.println("Data RFID\t: " + DATA_STR(0));
  Serial.println("Data MQ2\t: " + DATA_STR(1));
  Serial.println("Data Kunci\t: " + DATA_STR(2));
  delay(250); // <-- jeda agar data terlihat (tidak dibutuhkan pada program asli)
}
