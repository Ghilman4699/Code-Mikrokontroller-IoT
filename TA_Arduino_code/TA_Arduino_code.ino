#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define led1 7
#define led2 6
#define led3 5
#define LPG A0
#define solenoid 8
int sensorValue = 0;
int outputValue = 0;
const byte interrupt1 = 2;
const byte interrupt2 = 3;
MFRC522 mfrc522(SS_PIN, RST_PIN); 
String data = "";

void kondisi_kunci(){
  String web = "";
  int lock;
  String kondisi = "kunci ditutup";
  lock = digitalRead(8);
  if(lock==HIGH){
    kondisi = "kunci dibuka";
    }
    else{
      kondisi = "kunci ditutup";
      }
   web += "<strong> "+ kondisi +" </strong>"; 

//   server.send(200, "text/html", web);   
  }  
  
void buka_kunci(){
  
  String web = "";
  
  web += "<strong>Berhasil dibuka</strong>";
  
  Serial.println("ON");
  Serial.println("Tombol dihidupkan..");
  digitalWrite(8, HIGH);
  
//  server.send(200, "text/html", web);
  } 

void gas(){
  String web = "";
  String nilai;

  sensorValue = analogRead(A0); 
  Serial.print("pembacaan sensor = ");
  Serial.println(sensorValue);
  outputValue = map(sensorValue, 0, 1023, 0, 5);
  
  switch(outputValue){
    case 0:
      Serial.println("tidak ada kebocoran");
      nilai = "tidak ada kebocoran";
      break;
    case 1:
      Serial.println("ada kebocoran");
      nilai = "ada kebocoran";
      break;
    case 2:
      Serial.println("bahaya");
      nilai = "bahaya";
      break;
    case 3:
      Serial.println("sangat bahaya");
      nilai = "sangat bahaya";
      break;
    case 4:
      Serial.println("warning!!");
      nilai = "warning!";
      break;
    case 5:
      Serial.println("sangat warning!!");
      nilai = "sangat warning!!";
      break;
    }
  delay(10);

  nilai = sensorValue + nilai;
  web += "<strong>"+ nilai +"</strong>";

//  server.send(200, "text/html", web);
}

void lampu_1_ON(){
  String web = "";

  web += "<strong>lampu satu dihidupkan/strong>";
  
  digitalWrite(7, HIGH);
  Serial.println("Lampu 1 ON");

//  server.send(200, "text/html", web);
  }  

void lampu_1_OFF(){
  String web = "";

  web += "<p>lampu satu dimatikan</p>";
  
  digitalWrite(7, LOW);
  Serial.println("Lampu 1 OFF");

//  server.send(200, "text/html", web);
  }  

void lampu_2_ON(){
  String web = "";

  web += "<strong>lampu dua dihidupkan</strong>";
  
  digitalWrite(6, HIGH);
  Serial.println("Lampu 2 ON");

//  server.send(200, "text/html", web);
  }  

void lampu_2_OFF(){
  String web = "";

  web += "<strong>lampu dua dimatikan/strong>";

  digitalWrite(6, LOW);
  Serial.println("Lampu 2 OFF");

//  server.send(200, "text/html", web);
  }  

void lampu_3_ON(){
  String web = "";

  web += "<strong>lampu tiga dihidupkan/strong>";

  digitalWrite(5, HIGH);
  Serial.println("Lampu 3 ON");

//  server.send(200, "text/html", web);
  }  

void lampu_3_OFF(){
  String web = "";

  web += "<strong>lampu tiga dimatikan/strong>";

  digitalWrite(5, LOW);
  Serial.println("Lampu 3 OFF");

//  server.send(200, "text/html", web);
  }  

void nyala_semua(){
  String web = "";

  web += "<strong>semua lampu menyala/strong>";

  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  Serial.println("Semua lampu ON");

//  server.send(200, "text/html", web);
  }  

void mati_semua(){
  String web = "";

  web += "<strong>semua lampu dimatikan/strong>";

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  Serial.println("Semua lampu OFF");

//  server.send(200, "text/html", web);
  }  

void baca_rfid(){
   //   Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  data = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     data = data + String(mfrc522.uid.uidByte[i]);
     Serial.print(mfrc522.uid.uidByte[i], DEC);
  }
  Serial.println("\nreaded : " + data);
  if(data == "18589242176"){
      Serial.println("kartu dikenali..");
      digitalWrite(8, HIGH);
      delay(2000);
    }else{
      Serial.println("kartu tdk dikenal..");
      digitalWrite(8, LOW);
      delay(2000);
      }
  }

void tutup_kunci(){
  String web = "";
  web += "<strong>Berhasil dikunci</strong>";
  
  Serial.println("OFF");
  Serial.println("Tombol Dimatikan Ditekan!");
  digitalWrite(8, LOW);

//  server.send(200, "text/html", web);
  }   

void buka_kunci2(){
  String web = "";
  web += "<strong>kunci dibuka</strong>";

  digitalWrite(D8, HIGH);
  Serial.println("Kunci rumah dibuka");

//  server.send(200, "text/html", web);
  }

void setup() {
  pinMode(interrupt1, INPUT);   //interrupt pin1
  pinMode(interrupt2, INPUT);   //interrupt pin2
  pinMode(7, OUTPUT);          //lampu1
  pinMode(6, OUTPUT);          //lampu2
  pinMode(5, OUTPUT);          //lampu3
  pinMode(8, OUTPUT);          //solenoid
  pinMode(A0,OUTPUT);           //sensor gas LPG
  Serial.begin(115200);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

  attachInterrupt(digitalPinToInterrupt(interrupt1), baca_rfid, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupt2), buka_kunci2, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:

}
