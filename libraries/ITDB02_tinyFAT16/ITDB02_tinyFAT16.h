/*
  ITDB02_tinyFAT16.h - Add-on library to integrate ITDB02_Graph16 and tinyFAT
  Copyright (C)2010-2011 Henning Karlsen. All right reserved
  
  Basic functionality of this library are based on the demo-code provided by
  ITead studio. You can find the latest version of the library at
  http://www.henningkarlsen.com/electronics

  This library has been made especially for the 3.2" TFT LCD Screen Module: 
  ITDB02-3.2 by ITead studio. This library has been designed to use 16bit mode, 
  and it should work with the 2.4" Module in 16bit mode as well, although I do
  not have one, so this is untested.

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
*/

#ifndef ITDB02_tinyFAT16_h
#define ITDB02_tinyFAT16_h

#include "WProgram.h"
#include "ITDB02_Graph16.h"
#include "tinyFAT.h"

class ITDB02tf: public ITDB02
{
	public:

		ITDB02tf(int RS, int WR,int CS, int RST, byte model=ITDB32);

		word loadBitmap(int x, int y, int sx, int sy, char *filename);
};

#endif