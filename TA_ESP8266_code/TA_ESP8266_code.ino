#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

ESP8266WebServer server(80);

void web_root_handle(){
  String web = "";
  web += "<a <head><style>body {background-color: grey;}</style></head> </a>\n";
  web += "<nav class=navbar navbar-dark bg-primary><a class=navbar-brand> <style>body {background : red;}</style>My Home</a></nav>";
  web += "<a href=\"/cekkunci\"> <button>Kondisi Kunci</button></a>\n";
  web += "<a href=\"/buka\"> <button>Buka Kunci</button></a>\n";
  web += "<a href=\"/tutup\"><button>Tutup Kunci</button></a>\n"; 
  web += "<a href=\"/bacaLPG\"><button>Sensor LPG</button></a>\n"; 
  web += "<a href=\"/hidup1\"><button>Lampu1ON</button></a>\n"; 
  web += "<a href=\"/mati1\"><button>Lampu1OFF</button></a>\n"; 
  web += "<a href=\"/hidup2\"><button>Lampu2ON</button></a>\n"; 
  web += "<a href=\"/mati2\"><button>Lampu2OFF</button></a>\n"; 
  web += "<a href=\"/hidup3\"><button>Lampu3ON</button></a>\n"; 
  web += "<a href=\"/mati3\"><button>Lampu3OFF</button></a>\n"; 
  web += "<a href=\"/semuaON\"><button>Nyalakan Semua Lampu</button></a>\n"; 
  web += "<a href=\"/semuaOFF\"><button>Matikan Semua Lampu</button></a>\n"; 

  server.send(200, "text/html", web);
  }  

void setup() {
  Serial.begin(115200);
  WiFi.begin("Rumah", "Khususrahmabayar2000");
  Serial.println("\n\nPlease wait Device is Traying to Connecting.. \n[");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print("*");
    delay(100);
    }
    Serial.println("\t[OK]");
    Serial.println("\nConnected");
    Serial.println(WiFi.localIP());

    server.on("/", web_root_handle);
//    server.on("/cekkunci", kondisi_kunci);
//    server.on("/buka", buka_kunci);
//    server.on("/bacaLPG", gas);
//    server.on("/hidup1", lampu_1_ON);
//    server.on("/mati1", lampu_1_OFF);
//    server.on("/hidup2", lampu_2_ON);
//    server.on("/mati2", lampu_2_OFF);
//    server.on("/hidup3", lampu_3_ON);
//    server.on("/mati3", lampu_3_OFF);
//    server.on("/semuaON", nyala_semua);
//    server.on("/semuaOFF", mati_semua);
//    server.on("/tutup", tutup_kunci);
    server.begin();
}

void loop() {
server.handleClient();
}
