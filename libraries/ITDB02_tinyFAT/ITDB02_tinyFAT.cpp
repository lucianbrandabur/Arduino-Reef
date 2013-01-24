/*
  ITDB02_tinyFAT.cpp - Add-on library to integrate ITDB02_Graph and tinyFAT
  Copyright (C)2010-2011 Henning Karlsen. All right reserved
  
  Basic functionality of this library are based on the demo-code provided by
  ITead studio. You can find the latest version of the library at
  http://www.henningkarlsen.com/electronics

  This library has been made especially for the 2.4" TFT LCD Screen Module: 
  ITDB02-2.4(D) by ITead studio. This library has been designed to use 8bit mode, 
  so it will not work with the 3.2" Module.

  If you make any modifications or improvements to the code, I would appreciate
  that you share the code with me so that I might include it in the next release.
  I can be contacted through http://www.henningkarlsen.com/electronics/contact.php

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Version:   1.0  - Apr  19 2011  - initial release

*/

#if defined(__AVR__)
	#if defined(ARDUINO) && ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
#include "ITDB02_tinyFAT.h"
#include "tinyFAT.h"
#include <pins_arduino.h>

ITDB02tf::ITDB02tf(int RS, int WR,int CS, int RST, byte display)
{ 
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
   DDRA = 0xFF;
#else
   DDRD = 0xFF;
#endif
	P_RS	= portOutputRegister(digitalPinToPort(RS));
	B_RS	= digitalPinToBitMask(RS);
	P_WR	= portOutputRegister(digitalPinToPort(WR));
	B_WR	= digitalPinToBitMask(WR);
	P_CS	= portOutputRegister(digitalPinToPort(CS));
	B_CS	= digitalPinToBitMask(CS);
	P_RST	= portOutputRegister(digitalPinToPort(RST));
	B_RST	= digitalPinToBitMask(RST);
	pinMode(RS,OUTPUT);
	pinMode(WR,OUTPUT);
	pinMode(CS,OUTPUT);
	pinMode(RST,OUTPUT);
	displaymodel = display;
};

word ITDB02tf::loadBitmap(int x, int y, int sx, int sy, char *filename)
{
	int res;
	int cx, cy, cp;
	word temp, result;
	byte r,g,b;

	res=file.openFile(filename, FILEMODE_BINARY);
	if (res==NO_ERROR)
	{
		*P_CS &= ~B_CS;
		cx=0;
		cy=0;
		result=512;
		if (orient==PORTRAIT)
		{
			setXY(x, y, x+sx-1, y+sy-1);
		}
		while (result==512)
		{
			result=file.readBinary();
			switch(result)
			{
				case ERROR_WRONG_FILEMODE:
					return ERROR_WRONG_FILEMODE;
					break;
				case ERROR_NO_FILE_OPEN:
					return ERROR_NO_FILE_OPEN;
					break;
				default:
					if (orient==PORTRAIT)
					{
						for (int i=0; i<result; i+=2)
							LCD_Write_DATA(file.buffer[i],file.buffer[i+1]);
					}
					else
					{
						cp=0;
						while (cp<result)
						{
							if (((result-cp)/2)<(sx-cx))
							{
								setXY(x+cx, y+cy, x+cx+((result-cp)/2)-1, y+cy);
								for (int i=(result-cp)-2; i>=0; i-=2)
									LCD_Write_DATA(file.buffer[cp+i],file.buffer[cp+i+1]);
								cx+=((result-cp)/2);
								cp=result;
							}
							else
							{
								setXY(x+cx, y+cy, x+sx-1, y+cy);
								for (int i=sx-cx-1; i>=0; i--)
									LCD_Write_DATA(file.buffer[cp+(i*2)],file.buffer[cp+(i*2)+1]);
								cp+=(sx-cx)*2;
								cx=0;
								cy++;
							}
						}
					}
					break;
			}              
		}
		file.closeFile();
		if (orient==PORTRAIT)
			setXY(0,0,239,319);
		else
			setXY(0,0,319,239);
		*P_CS |= B_CS;
		return 0;
	}
	else
	{
		return res;
	}
};
