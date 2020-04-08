#include <Arduino.h>
#include "parse_merge.h" // <-- important library

void setup(){
  Serial.begin(115200); // <-- enlarge the data transmission size

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
