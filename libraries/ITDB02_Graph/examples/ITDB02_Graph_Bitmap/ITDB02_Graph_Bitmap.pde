// ITDB02_Graph_Bitmap (C)2011 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of the drawBitmap()-function.
//
// This program requires the ITDB02_Graph library.
//

#include <ITDB02_Graph.h>
#include <avr/pgmspace.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];

// Uncomment the next line for Arduino 2009/Uno
//ITDB02 myGLCD(19,18,17,16);   // Remember to add the parameter for your display if you are not using an ITDB02-2.4!

// Uncomment the next line for Arduino Mega
ITDB02 myGLCD(38,39,40,41);   // Remember to add the parameter for your display if you are not using an ITDB02-2.4!

extern unsigned int info[0x400];
extern unsigned int icon[0x400];
extern unsigned int tux[0x400];

void setup()
{
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.setFont(SmallFont);
}

void loop()
{
  myGLCD.fillScr(255, 255, 255);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(" *** A 10 by 7 grid of a 32x32 icon *** ", CENTER, 228);
  for (int x=0; x<10; x++)
    for (int y=0; y<7; y++)
      myGLCD.drawBitmap (x*32, y*32, 32, 32, info);

  delay(5000);
  
  myGLCD.fillScr(255, 255, 255);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("   Two different icons in scale 1 to 4  ", CENTER, 228);
  int x=0;
  for (int s=0; s<4; s++)
  {
    x+=(s*32);
    myGLCD.drawBitmap (x, 0, 32, 32, tux, s+1);
  }
  x=0;
  for (int s=4; s>0; s--)
  {
    myGLCD.drawBitmap (x, 224-(s*32), 32, 32, icon, s);
    x+=(s*32);
  }

  delay(5000);
}

