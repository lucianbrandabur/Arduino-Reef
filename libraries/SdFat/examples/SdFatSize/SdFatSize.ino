/*
 * Sketch to compare size of SdFat V2 with Arduino SD library.
 * See SD_Size.pde for Arduino SD sketch.
 *
 * Use MiniSerial to save RAM and flash.
 */
#include <SdFat.h>

SdFat sd;

SdFile file;
//------------------------------------------------------------------------------
void setup() {
  // will not work on Leonardo or Teensy - replace MiniSerial with Serial
  MiniSerial.begin(9600);

  if (!sd.begin()) {
    MiniSerial.println("init failed");
    return;
  }
  file.open("SIZE_TST.TXT", O_RDWR | O_CREAT | O_AT_END);

  file.println("Hello");

  file.close();
  MiniSerial.println("Done");
}
//------------------------------------------------------------------------------
void loop() {}
