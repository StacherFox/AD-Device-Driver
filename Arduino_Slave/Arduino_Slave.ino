#include <Wire.h>

int16_t raw1 = 55;
int16_t raw2 = 1000;

void setup() {
  Wire.begin(0x72);
  Wire.onRequest(requestEvent);
}

void loop() {
  delay(100);
}

void requestEvent() {
  byte myArray[4];
  myArray[0] = (raw1 >> 8) & 0xFF;
  myArray[1] = raw1 & 0xFF;
  myArray[2] = (raw2 >> 8) & 0xFF;
  myArray[3] = raw2 & 0xFF;
  Wire.write(myArray, 4);
  
}
