#include <Arduino.h>
#include "parse_merge.h" // <-- important library
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define Status_Kunci() digitalRead(8)

MFRC522 mfrc522(SS_PIN, RST_PIN);
String RFID;

static String data_array[6] = {};

void send_command(String cmd, unsigned char index){
  data_array[index] = cmd;
  String new_data = "";

  for(int x=0;x<6;x++)
    new_data += (data_array[x] + ";");
  Serial.println(new_data);
}

int MQ2_Get_Value(){
  int data = 0;
  for(int x = 0; x<5;x++)
    data += analogRead(A0);
  return data/5;
}

String RFID_Get_Data(){
  String data_rfid = "";
  
   if (! mfrc522.PICC_IsNewCardPresent())
    return;
  if (! mfrc522.PICC_ReadCardSerial()) 
    return;
  
  for (byte i = 0; i < mfrc522.uid.size; i++)
     data_rfid = data_rfid + String(mfrc522.uid.uidByte[i]);
  return data_rfid;
}


void setup(){
  Serial.begin(115200); // <-- enlarge the data transmission size
  pinMode(A0, INPUT);
  SPI.begin();
  mfrc522.PCD_Init();

  for(int x=0;x<6;x++)
    data_array[x] = "000";
}

void loop(){
  // <-- Data gateway begin
  // Access received data using DATA_STR(x) <-- x is data position
  if(Serial.available() > 0){
    data = Serial.readStringUntil('\n');
    parse_string();
  }
  // <-- Data gateway end
  
}