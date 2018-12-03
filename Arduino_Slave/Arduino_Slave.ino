#include <Wire.h>

void setup() {
  Wire.begin(0x72);
  Wire.onRequest(requestEvent);
}

void loop() {
  delay(100);
}

void requestEvent() {
  int16_t raw1 = analogRead(A0);
  int16_t raw2 = analogRead(A1);
  byte myArray[4];
  myArray[0] = (raw1 >> 8) & 0xFF;
  myArray[1] = raw1 & 0xFF;
  myArray[2] = (raw2 >> 8) & 0xFF;
  myArray[3] = raw2 & 0xFF;
  Wire.write(myArray, 4);
  
}
