// ITDB02_Graph_Rotate_Bitmap (C)2011 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of the drawBitmap()-function.
//
// This program requires the ITDB02_Graph library.
//

#include <ITDB02_Graph.h>
#include <avr/pgmspace.h>

// Uncomment the next line for Arduino 2009/Uno
//ITDB02 myGLCD(19,18,17,16);   // Remember to add the parameter for your display if you are not using an ITDB02-2.4!

// Uncomment the next line for Arduino Mega
ITDB02 myGLCD(38,39,40,41);   // Remember to add the parameter for your display if you are not using an ITDB02-2.4!

extern unsigned int tux[0x400];

void setup()
{
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.fillScr(255, 255, 255);
  myGLCD.setColor(0, 0, 0);
}

void loop()
{
    for (int i=0; i<360; i+=5)
    {
      myGLCD.drawBitmap (100, 100, 32, 32, tux, i, 16, 16);
    }
}

