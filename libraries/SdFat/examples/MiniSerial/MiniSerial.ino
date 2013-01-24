// This example illustrates use of SdFat's
// minimal unbuffered Serial support.
//
// This is useful for debug and saves RAM
// Will not work on Leonardo or Teensy
#include <SdFat.h>
#include <SdFatUtil.h>
void setup() {
  MiniSerial.begin(9600);
  MiniSerial.println(FreeRam());
  MiniSerial.println(F("Type any Character"));
  while(MiniSerial.read() < 0) {}
  MiniSerial.println(F("Done"));
}
void loop() {}
