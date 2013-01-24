// ITDB02_Graph_Demo (C)2011 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of how to use most of the functions
// of the library with a supported 8bit display module.
//
// This program requires the ITDB02_Graph library.
//

#include <ITDB02_Graph.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];

// Uncomment the next line for Arduino 2009/Uno
//ITDB02 myGLCD(19,18,17,16);   // Remember to add the parameter for your display if you are not using an ITDB02-2.4!

// Uncomment the next line for Arduino Mega
ITDB02 myGLCD(38,39,40,41);   // Remember to add the parameter for your display if you are not using an ITDB02-2.4!

void setup()
{
  randomSeed(analogRead(0));
  
// Setup the LCD
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
}

void loop()
{
  int buf[238];
  int x, x2;
  int y, y2;
  int r;

// Clear the screen and draw the frame
  myGLCD.clrScr();

  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, 239, 13);
  myGLCD.setColor(64, 64, 64);
  myGLCD.fillRect(0, 306, 239, 319);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("QVGA TFT 240x320 Color Display", CENTER, 1);
  myGLCD.setColor(255, 128, 128);
  myGLCD.setBackColor(64, 64, 64);
  myGLCD.print("H.Karlsen", LEFT, 307);
  myGLCD.print("(C)2011", RIGHT, 307);
  myGLCD.setColor(255,255,0);
  myGLCD.print("Portrait", CENTER, 307);

  myGLCD.setColor(0, 0, 255);
  myGLCD.drawLine(0, 14, 239, 14);
  myGLCD.drawLine(0, 14, 0, 305);
  myGLCD.drawLine(239, 14, 239, 305);
  myGLCD.drawLine(0, 305, 239, 305);

// Draw crosshairs
  myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(119, 15, 119, 304);
  myGLCD.drawLine(1, 159, 238, 159);
  for (int i=9; i<240; i+=10)
    myGLCD.drawLine(i, 157, i, 161);
  for (int i=19; i<300; i+=10)
    myGLCD.drawLine(117, i, 121, i);
  
// Draw sin-, cos- and tan-lines  
  myGLCD.setColor(0,255,255);
  myGLCD.print("Sin", 5, 15);
  for (int i=1; i<238; i++)
  {
    myGLCD.drawPixel(i,159+(sin(((i*1.51)*3.14)/180)*100));
  }
  
  myGLCD.setColor(255,0,0);
  myGLCD.print("Cos", 5, 27);
  for (int i=1; i<238; i++)
  {
    myGLCD.drawPixel(i,159+(cos(((i*1.51)*3.14)/180)*100));
  }

  myGLCD.setColor(255,255,0);
  myGLCD.print("Tan", 5, 39);
  for (int i=1; i<238; i++)
  {
    myGLCD.drawPixel(i,159+(tan(((i*1.51)*3.14)/180)));
  }

  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,238,304);
  myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(119, 15, 119, 304);
  myGLCD.drawLine(1, 159, 238, 159);

// Draw a moving sinewave
  x=1;
  for (int i=1; i<6902; i++)
  {
    x++;
    if (x==239)
      x=1;
    if (i>239)
    {
      if ((x==119)||(buf[x-1]==159))
        myGLCD.setColor(0,0,255);
      else
        myGLCD.setColor(0,0,0);
      myGLCD.drawPixel(x,buf[x-1]);
    }
    myGLCD.setColor(0,255,255);
    y=159+(sin(((i*1.4)*3.14)/180)*(100-(i / 100)));
    myGLCD.drawPixel(x,y);
    buf[x-1]=y;
  }

  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,238,304);

// Draw some filled rectangles
  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        myGLCD.setColor(255,0,255);
        break;
      case 2:
        myGLCD.setColor(255,0,0);
        break;
      case 3:
        myGLCD.setColor(0,255,0);
        break;
      case 4:
        myGLCD.setColor(0,0,255);
        break;
      case 5:
        myGLCD.setColor(255,255,0);
        break;
    }
    myGLCD.fillRect(30+(i*20), 70+(i*20), 90+(i*20), 130+(i*20));
  }

  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,238,304);

// Draw some filled, rounded rectangles
  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        myGLCD.setColor(255,0,255);
        break;
      case 2:
        myGLCD.setColor(255,0,0);
        break;
      case 3:
        myGLCD.setColor(0,255,0);
        break;
      case 4:
        myGLCD.setColor(0,0,255);
        break;
      case 5:
        myGLCD.setColor(255,255,0);
        break;
    }
    myGLCD.fillRoundRect(150-(i*20),70+(i*20), 210-(i*20), 130+(i*20));
  }
  
  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,238,304);

// Draw some filled circles
  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        myGLCD.setColor(255,0,255);
        break;
      case 2:
        myGLCD.setColor(255,0,0);
        break;
      case 3:
        myGLCD.setColor(0,255,0);
        break;
      case 4:
        myGLCD.setColor(0,0,255);
        break;
      case 5:
        myGLCD.setColor(255,255,0);
        break;
    }
    myGLCD.fillCircle(60+(i*20),100+(i*20), 30);
  }
  
  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,238,304);

// Draw some lines in a pattern
  myGLCD.setColor (255,0,0);
  for (int i=15; i<304; i+=5)
  {
    myGLCD.drawLine(1, i, (i/1.22)-10, 304);
  }
  myGLCD.setColor (255,0,0);
  for (int i=304; i>15; i-=5)
  {
    myGLCD.drawLine(238, i, (i/1.22)-11, 15);
  }
  myGLCD.setColor (0,255,255);
  for (int i=304; i>15; i-=5)
  {
    myGLCD.drawLine(1, i, 251-(i/1.22), 15);
  }
  myGLCD.setColor (0,255,255);
  for (int i=15; i<304; i+=5)
  {
    myGLCD.drawLine(238, i, 250-(i/1.22), 304);
  }
  
  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,238,304);

// Draw some random circles
  for (int i=0; i<100; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x=32+random(175);
    y=45+random(212);
    r=random(30);
    myGLCD.drawCircle(x, y, r);
  }

  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,238,304);

// Draw some random rectangles
  for (int i=0; i<100; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x=2+random(236);
    y=16+random(287);
    x2=2+random(236);
    y2=16+random(287);
    myGLCD.drawRect(x, y, x2, y2);
  }

  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,238,304);

// Draw some random rounded rectangles
  for (int i=0; i<100; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x=2+random(236);
    y=16+random(287);
    x2=2+random(236);
    y2=16+random(287);
    myGLCD.drawRoundRect(x, y, x2, y2);
  }

  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(2,16,238,304);

  for (int i=0; i<100; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x=2+random(236);
    y=16+random(289);
    x2=2+random(236);
    y2=16+random(289);
    myGLCD.drawLine(x, y, x2, y2);
  }

  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,238,304);

  for (int i=0; i<10000; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    myGLCD.drawPixel(2+random(236), 16+random(289));
  }

  delay(2000);

  myGLCD.fillScr(0, 0, 255);
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRoundRect(30, 100, 209, 219);
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("That's it!", CENTER, 133);
  myGLCD.print("Restarting in a", CENTER, 159);
  myGLCD.print("few seconds...", CENTER, 172);
  
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.print("Runtime: (msecs)", CENTER, 290);
  myGLCD.printNumI(millis(), CENTER, 305);
  
  delay (10000);
}

