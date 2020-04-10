#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include "parse_merge.h" // <-- important library

#define SS_PIN 10
#define RST_PIN 9
#define Status_Kunci() digitalRead(8)

MFRC522 mfrc522(SS_PIN, RST_PIN);

int MQ2_Get_Value(){
  int mq = 0;
  for(int x = 0; x<5;x++)
    mq += analogRead(A0);
  return mq/5;
}

String RFID_Get_Data(){
  String data_rfid = "";
  
  for (byte i = 0; i < mfrc522.uid.size; i++)
     data_rfid = data_rfid + String(mfrc522.uid.uidByte[i]);
  return data_rfid;
}

void setup(){
  Serial.begin(115200); // <-- enlarge the data transmission size
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop(){
  if(Serial.available() > 0){
    data = Serial.readStringUntil('\n');
    parse_string();
    
    if(DATA_STR(0) == "REQ")
      Serial.println(RFID_Get_Data() + ";" + String(MQ2_Get_Value()) + ";" + String(Status_Kunci()) + ";");
  }
  
  if (mfrc522.PICC_IsNewCardPresent()){
    if (!mfrc522.PICC_ReadCardSerial()) return;
    
    if(RFID_Get_Data()=="18589242176"){
      Serial.println("kartu dikenali..");
      digitalWrite(8, HIGH);
    }else{
      Serial.println("kartu tdk dikenal..");
      digitalWrite(8, LOW);
      }
      Serial.println(RFID_Get_Data() + ";" + String(MQ2_Get_Value()) + ";" + String(Status_Kunci()) + ";");
    }
  }
