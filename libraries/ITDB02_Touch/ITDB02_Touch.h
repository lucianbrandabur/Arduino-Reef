/*
  ITDB02_Touch.h - Arduino library support for ITDB02 Touch function
  Copyright (C)2010 Henning Karlsen. All right reserved
  
  Basic functionality of this library are based on the demo-code provided by
  ITead studio. You can find the latest version of the library at
  http://www.henningkarlsen.com/electronics

  This library has been made for the 2.4" TFT LCD Screen Module: “ITDB02-2.4”, 
  the 3.2" TFT LCD Screen Module: “ITDB02-3.2” and the 3.2" Wide-screen module 
  “ITDB02-3.2WC” by ITead studio.

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

  Version:   1.0  - Sep  13 2010  - initial release
			 1.01 - Sep  18 2010  - Added example: ITDB02_Touch_ButtonTest
			 1.1  - Oct   7 2010  - Fixed incompatibility with ITDB02-3.2
			 1.2  - Oct  12 2010  - Added support for ITDB02-3.2WC
			 1.21 - Mar  27 2011  - Updated some of the examples to be 
									compatible with ITDB02_Graph(16) v4.0

*/


#ifndef ITDB02_Touch_h
#define ITDB02_Touch_h

#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif

#define PORTRAIT	0
#define LANDSCAPE	1

#define PREC_LOW		1
#define PREC_MEDIUM		2
#define PREC_HI			3
#define PREC_EXTREME	4

class ITDB02_Touch
{
	public:
		word	TP_X ,TP_Y;

				ITDB02_Touch(byte tclk, byte tcs, byte tdin, byte dout, byte irq);

		void	InitTouch(byte orientation = PORTRAIT);
		void	read();
		bool	dataAvailable();
		int		getX();
		int		getY();
		void	setPrecision(byte precision);
    
    private:
		byte	T_CLK, T_CS, T_DIN, T_DOUT, T_IRQ;
		byte	orient;
		byte	prec;

		void	touch_WriteData(byte data);
		word	touch_ReadData();
};

#endif
