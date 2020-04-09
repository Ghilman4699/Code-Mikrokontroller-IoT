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
  
  Serial.println("\nTotal data ada : " + String(get_total_data()));
  Serial.println("data ke 0 : " + DATA_STR(0));
  Serial.println("data ke 1 : " + DATA_STR(1));
  Serial.println("data ke 2 : " + DATA_STR(2));
  Serial.println("data ke 3 : " + DATA_STR(3));
  Serial.println("data ke 4 : " + DATA_STR(4));
  Serial.println("data ke 5 : " + DATA_STR(5));
  delay(100);
}
