#include <SoftwareSerial.h>

void setup() {
  Serial.begin(115200);     // optional debug (USB)
  Serial1.begin(115200);    // TX only to VESC
}

void loop() {
  Serial1.println("Hello VESC");
  delay(1000);
}