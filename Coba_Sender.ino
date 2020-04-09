#include <Arduino.h>
#include "parse_merge.h" // <-- important library

// Global variable
static String data_array[6] = {};

// Function declaration
void send_command(String cmd, unsigned char index){
  data_array[index] = cmd;
  String new_data = "";
  
  for(int x=0;x<6;x++)
    new_data += (data_array[x] + ";");
  Serial.println(new_data);
}

void setup(){
  Serial.begin(115200);

  // Fill empty array
  for(int x=0;x<6;x++)
    data_array[x] = "000";
}

void loop(){
  if(Serial.available() > 0){
    data = Serial.readStringUntil('\n');
    parse_string();
  }
  
  /*send_command("200", 0);
  send_command("tes", 1);
  send_command("oke", 2);
  send_command("done", 3);
  send_command("50.5", 4);
  send_command("34f", 5);*/
  Serial.println("200;tes;oke;done;50.5;34f;");
  
  delay(100);
}
