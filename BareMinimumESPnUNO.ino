#include <Arduino.h>
#include "parse_merge.h" // <-- important library
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
String RFID;

static String data_array[6] = {};

void send_command(String cmd, unsigned char index){
  data_array[index] = cmd;
  String new_data = "";

  for(int x=0;x<6;x++)
    new_data += (data_array[x] + ";");
  Serial.println(new_data);;
  }

int MQ2_Get_Value(){
  int data = 0;
  for(int x = 0; x<5;x++)
  data += analogRead(A0);
  return data/5;
  }

String RFID_Get_Data(){
   if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  Serial.print("UID tag :");
  RFID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     RFID = RFID + String(mfrc522.uid.uidByte[i]);
     Serial.println(RFID);
     Serial.print(mfrc522.uid.uidByte[i], DEC);
  }
  return RFID;
  }

int Kondisi_Kunci(){
  int kondisi = digitalRead(8);
  return kondisi;
  }


void setup(){
  Serial.begin(115200); // <-- enlarge the data transmission size
  pinMode(A0, INPUT);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Approximate your card to the reader...");
  Serial.println();

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
