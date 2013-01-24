// ITDB02_Graph_Textrotation_Demo (C)2011 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of the textrotation-functions.
//
// This program requires the ITDB02_Graph library.
//

#include <ITDB02_Graph.h>

// Declare which fonts we will be using
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

// Uncomment the next line for Arduino 2009/Uno
//ITDB02 myGLCD(19,18,17,16);   // Remember to add the parameter for your display if you are not using an ITDB02-2.4!

// Uncomment the next line for Arduino Mega
ITDB02 myGLCD(38,39,40,41);   // Remember to add the parameter for your display if you are not using an ITDB02-2.4!

void setup()
{
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);
}

void loop()
{
    myGLCD.print("Text rotation", 0, 0);
    myGLCD.setColor(0, 0, 255);
    myGLCD.print("0 degrees", 0, 16, 0);
    myGLCD.print("90 degrees", 319, 0, 90);
    myGLCD.print("180 degrees", 319, 239, 180);
    myGLCD.print("270 degrees", 0, 239, 270);

    myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.print("45", 90, 100, 45);
    myGLCD.print("90", 200, 50, 90);
    myGLCD.print("180", 300, 200, 180);

  while (true) {};
}

