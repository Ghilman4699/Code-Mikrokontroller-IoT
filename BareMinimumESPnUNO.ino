#include <Arduino.h>
#include "parse_merge.h" // <-- important library

// Global variable
static String data_array[5] = {};

// Function declaration
void send_command(String cmd, unsigned char index){
  data_array[index] = cmd;
  String new_data = "";
  
  for(int x=0;x<5;x++)
    new_data += (data_array[x] + ";");
  Serial.println(new_data);
}

void setup(){
  Serial.begin(115200); // <-- enlarge the data transmission size

  // Fill empty array
  for(int x=0;x<5;x++)
    data_array[x] = "000";
  
  // Once run code put here
}

void loop(){
  // <-- Data gateway begin
  // Access received data using DATA_STR(x) <-- x is data position
  if(Serial.available() > 0){
    data = Serial.readStringUntil('\n');
    parse_string();
  }
  // <-- Data gateway end
  
  // Loop program put here
}
