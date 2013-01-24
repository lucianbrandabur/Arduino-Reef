// ITDB02_Touch_QuickDraw (C)2010 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a quick demo of how to use the library.
//
// This program requires the ITDB02_Graph library (8bit mode)
// or ITDB02_Graph16 (16bit mode).
//
// It is assumed that the ITDB02 module is connected to a
// ITDB02 Shield, a ITDB02 Mega Shield or that you know how 
// to change the pin numbers in the setup.
//

// Remember to change the next line if you are using as 16bit module!
#include <ITDB02_Graph.h>
#include <ITDB02_Touch.h>

// Uncomment the next two lines for the ITDB02 Shield
ITDB02        myGLCD(19,18,17,16);
ITDB02_Touch  myTouch(15,10,14,9,8);

// Uncomment the next two lines for the ITDB02 Mega Shield
//ITDB02        myGLCD(38,39,40,41);   // Remember to add ASPECT_16x9 if you are using an ITDB02-3.2WC!
//ITDB02_Touch  myTouch(6,5,4,3,2);

void setup()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
}

void loop()
{
    while (myTouch.dataAvailable() == true)
    {
      myTouch.read();
      myGLCD.drawPixel (myTouch.getX(), myTouch.getY());
    }
}

