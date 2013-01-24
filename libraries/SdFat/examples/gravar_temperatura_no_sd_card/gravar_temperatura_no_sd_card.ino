// Ported to SdFat from the native Arduino SD library example by Bill Greiman
// On the Ethernet Shield, CS is pin 4. SdFat handles setting SS
const int chipSelect = 4;
/*
 SD card read/write
  
 This example shows how to read and write data to and from an SD card file 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 created   Nov 2010
 by David A. Mellis
 updated 2 Dec 2010
 by Tom Igoe
 modified by Bill Greiman 11 Apr 2011
 This example code is in the public domain.
 	 
 */
#include <SdFat.h>
#include <SdFatUtil.h>
#include <Sd2PinMap.h>

Sd2Card card;
SdFile file;
SdFile root;
SdVolume volume;

float temp;
float tempe;

void setup() 
{
  int16_t n;
  char buf[8];
  
  Serial.begin(9600);

  // Initialize SdFat or print a detailed error message and halt
  // Use half speed like the native library.
  // change to SPI_FULL_SPEED for more performance.
  card.init(SPI_QUARTER_SPEED,chipSelect);
  volume.init(&card);
  root.openRoot(&volume);
  
  // open the file for write at end like the Native SD library
 if(file.open(&root, "LOGTDIA.TXT", O_CREAT | O_APPEND | O_WRITE))
  {
  // if the file opened okay, write to it:
  Serial.println("Gravando...");
  }
  
  for(temp=27.5; temp>22.0; temp-=0.15)
  {
   file.print(temp);
   file.write((uint8_t*)"\0", 1);
   file.write((uint8_t*)"\r\n", 2);
  }
  
   for(tempe=22.5; tempe<28.0; tempe+=0.15)
  {
   file.print(tempe);
   file.write((uint8_t*)"\0", 1);
   file.write((uint8_t*)"\r\n", 2);
  }

  // close the file:
  file.close();
  Serial.println("Gravado.");
  
  file.open(&root, "LOGTDIA.TXT", O_READ);
  while ((n = file.read(buf, sizeof(buf))) > 0)
  {
    Serial.println(buf);
  }
  file.close();
  Serial.print("concluido");
}

void loop() {
  // nothing happens after setup
}


