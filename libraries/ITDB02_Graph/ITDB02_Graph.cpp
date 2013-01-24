/*
  ITDB02_Graph.cpp - Arduino library support for 8bit QVGA LCD Boards
  Copyright (C)2010-2011 Henning Karlsen. All right reserved
  
  Basic functionality of this library are based on the demo-code provided by
  ITead studio. You can find the latest version of the library at
  http://www.henningkarlsen.com/electronics

  This library was originally especially for the 2.4" TFT LCD Screen Module: 
  ITDB02-2.4 by ITead studio, but has later been expanded to support multiple
  modules. This library has been designed to use 8bit mode, so it will not 
  work with 16bit modules.

  Supported controllers:
		-	ILI9325C
		-	ILI9325D

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



#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif
#include "ITDB02_Graph.h"
#include <avr/pgmspace.h>
#include <pins_arduino.h>

uint16_t gamma[10][2] =
{
	{0x0000, 0x0000},
	{0x0707, 0x0404},
	{0x0307, 0x0003},
	{0x0200, 0x0405},
	{0x0008, 0x0808},
	{0x0004, 0x0407},
	{0x0000, 0x0303},
	{0x0707, 0x0707},
	{0x0002, 0x0504},
	{0x1D04, 0x0808}
};

uint16_t ITDB02InitValues[6][2] =
{
	{0x0700, 0x0200},
	{0x1090, 0x1690},
	{0x001F, 0x000D},
	{0x1500, 0x1200},
	{0x0027, 0x000A},
	{0x0600, 0x0000}
};

ITDB02::ITDB02()
{
}

ITDB02::ITDB02(int RS, int WR,int CS, int RST, byte display)
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
}

void ITDB02::LCD_Writ_Bus(char VH,char VL)
{   
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	PORTA = VH;
	*P_WR &= ~B_WR;
	*P_WR |= B_WR;
	PORTA = VL;
	*P_WR &= ~B_WR;
	*P_WR |= B_WR;
#else
	PORTD = VH;
	*P_WR &= ~B_WR;
	*P_WR |= B_WR;
	PORTD = VL;
	*P_WR &= ~B_WR;
	*P_WR |= B_WR;
#endif
}

void ITDB02::LCD_Write_COM(char VL)  
{   
	*P_RS &= ~B_RS;
	LCD_Writ_Bus(0x00,VL);
}

void ITDB02::LCD_Write_DATA(char VH,char VL)
{
	*P_RS |= B_RS;
	LCD_Writ_Bus(VH,VL);
}

void ITDB02::main_W_com_data(char com1,int dat1)
{
	*P_RS &= ~B_RS;
	LCD_Writ_Bus(0x00,com1);
 	*P_RS |= B_RS;
	LCD_Writ_Bus(dat1>>8,dat1);
}

void ITDB02::InitLCD(byte orientation)
{
	orient=orientation;

	*P_RST |= B_RST;
	delay(5); 
	*P_RST &= ~B_RST;
	delay(5);
	*P_RST |= B_RST;
	delay(5);

	*P_CS &= ~B_CS;

	//************* ILI9325C/D **********//
	main_W_com_data(0xE5, 0x78F0);								// set SRAM internal timing
	main_W_com_data(0x01, 0x0100);								// set SS and SM bit
	main_W_com_data(0x02, ITDB02InitValues[0][displaymodel]);	// set 1 line inversion
	main_W_com_data(0x03, 0x1030);								// set GRAM write direction and BGR=1.
	main_W_com_data(0x04, 0x0000);								// Resize register
	main_W_com_data(0x08, 0x0207);								// set the back porch and front porch
	main_W_com_data(0x09, 0x0000);								// set non-display area refresh cycle ISC[3:0]
	main_W_com_data(0x0A, 0x0000);								// FMARK function
	main_W_com_data(0x0C, 0x0000);								// RGB interface setting
	main_W_com_data(0x0D, 0x0000);								// Frame marker Position
	main_W_com_data(0x0F, 0x0000);								// RGB interface polarity
	//*************Power On sequence ****************//
	main_W_com_data(0x10, 0x0000);								// SAP, BT[3:0], AP, DSTB, SLP, STB
	main_W_com_data(0x11, 0x0007);								// DC1[2:0], DC0[2:0], VC[2:0]
	main_W_com_data(0x12, 0x0000);								// VREG1OUT voltage
	main_W_com_data(0x13, 0x0000);								// VDV[4:0] for VCOM amplitude
	main_W_com_data(0x07, 0x0001);
	delay(50); // Dis-charge capacitor power voltage
	main_W_com_data(0x10, ITDB02InitValues[1][displaymodel]);	// SAP, BT[3:0], AP, DSTB, SLP, STB
	main_W_com_data(0x11, 0x0227);								// Set DC1[2:0], DC0[2:0], VC[2:0]
	delay(50); // Delay 50ms
	main_W_com_data(0x12, ITDB02InitValues[2][displaymodel]);	// 0012
	delay(50); // Delay 50ms
	main_W_com_data(0x13, ITDB02InitValues[3][displaymodel]);	// VDV[4:0] for VCOM amplitude
	main_W_com_data(0x29, ITDB02InitValues[4][displaymodel]);	// 04  VCM[5:0] for VCOMH
	main_W_com_data(0x2B, 0x000D);								// Set Frame Rate
	delay(50); // Delay 50ms
	main_W_com_data(0x20, 0x0000);								// GRAM horizontal Address
	main_W_com_data(0x21, 0x0000);								// GRAM Vertical Address
	// ----------- Adjust the Gamma Curve ----------//
	main_W_com_data(0x30, gamma[0][displaymodel]);
	main_W_com_data(0x31, gamma[1][displaymodel]);
	main_W_com_data(0x32, gamma[2][displaymodel]);
	main_W_com_data(0x35, gamma[3][displaymodel]);
	main_W_com_data(0x36, gamma[4][displaymodel]);
	main_W_com_data(0x37, gamma[5][displaymodel]);
	main_W_com_data(0x38, gamma[6][displaymodel]);
	main_W_com_data(0x39, gamma[7][displaymodel]);
	main_W_com_data(0x3C, gamma[8][displaymodel]);
	main_W_com_data(0x3D, gamma[9][displaymodel]);
	//------------------ Set GRAM area ---------------//
	main_W_com_data(0x50, 0x0000);								// Horizontal GRAM Start Address
	main_W_com_data(0x51, 0x00EF);								// Horizontal GRAM End Address
	main_W_com_data(0x52, 0x0000);								// Vertical GRAM Start Address
	main_W_com_data(0x53, 0x013F);								// Vertical GRAM Start Address
	main_W_com_data(0x60, 0xA700);								// Gate Scan Line
	main_W_com_data(0x61, 0x0001);								// NDL,VLE, REV
	main_W_com_data(0x6A, 0x0000);								// set scrolling line
	//-------------- Partial Display Control ---------//
	main_W_com_data(0x80, 0x0000);
	main_W_com_data(0x81, 0x0000);
	main_W_com_data(0x82, 0x0000);
	main_W_com_data(0x83, 0x0000);
	main_W_com_data(0x84, 0x0000);
	main_W_com_data(0x85, 0x0000);
	//-------------- Panel Control -------------------//
	main_W_com_data(0x90, 0x0010);
	main_W_com_data(0x92, ITDB02InitValues[5][displaymodel]);
	main_W_com_data(0x07, 0x0133);								// 262K color and display ON

	*P_CS |= B_CS;

	setColor(255, 255, 255);
	setBackColor(0, 0, 0);
	cfont.font=0;
}

void ITDB02::setXY(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (orient==LANDSCAPE)
	{
		tmp=x1;
		x1=y1;
		y1=319-tmp;
		tmp=x2;
		x2=y2;
		y2=319-tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	main_W_com_data(0x20,x1);    
	main_W_com_data(0x21,y1);   
	main_W_com_data(0x50,x1);   
	main_W_com_data(0x52,y1);   
	main_W_com_data(0x51,x2);  
	main_W_com_data(0x53,y2);   
	LCD_Write_COM(0x22);           				 
}

void ITDB02::drawRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	drawHLine(x1, y1, x2-x1);
	drawHLine(x1, y2, x2-x1);
	drawVLine(x1, y1, y2-y1);
	drawVLine(x2, y1, y2-y1);
}

void ITDB02::drawRoundRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		drawPixel(x1+1,y1+1);
		drawPixel(x2-1,y1+1);
		drawPixel(x1+1,y2-1);
		drawPixel(x2-1,y2-1);
		drawHLine(x1+2, y1, x2-x1-4);
		drawHLine(x1+2, y2, x2-x1-4);
		drawVLine(x1, y1+2, y2-y1-4);
		drawVLine(x2, y1+2, y2-y1-4);
	}
}

void ITDB02::fillRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	if (orient==PORTRAIT)
	{
		for (int i=0; i<((y2-y1)/2)+1; i++)
		{
			drawHLine(x1, y1+i, x2-x1);
			drawHLine(x1, y2-i, x2-x1);
		}
	}
	else
	{
		for (int i=0; i<((x2-x1)/2)+1; i++)
		{
			drawVLine(x1+i, y1, y2-y1);
			drawVLine(x2-i, y1, y2-y1);
		}
	}
}

void ITDB02::fillRoundRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	if ((x2-x1)>4 && (y2-y1)>4)
	{
		for (int i=0; i<((y2-y1)/2)+1; i++)
		{
			switch(i)
			{
			case 0:
				drawHLine(x1+2, y1+i, x2-x1-4);
				drawHLine(x1+2, y2-i, x2-x1-4);
				break;
			case 1:
				drawHLine(x1+1, y1+i, x2-x1-2);
				drawHLine(x1+1, y2-i, x2-x1-2);
				break;
			default:
				drawHLine(x1, y1+i, x2-x1);
				drawHLine(x1, y2-i, x2-x1);
			}
		}
	}
}

void ITDB02::drawCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
	char ch, cl;
	
	ch=((fcolorr&248)|fcolorg>>5);
	cl=((fcolorg&28)<<3|fcolorb>>3);
 
	*P_CS &= ~B_CS;
	setXY(x, y + radius, x, y + radius);
	LCD_Write_DATA(ch,cl);
	setXY(x, y - radius, x, y - radius);
	LCD_Write_DATA(ch,cl);
	setXY(x + radius, y, x + radius, y);
	LCD_Write_DATA(ch,cl);
	setXY(x - radius, y, x - radius, y);
	LCD_Write_DATA(ch,cl);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		setXY(x + x1, y + y1, x + x1, y + y1);
		LCD_Write_DATA(ch,cl);
		setXY(x - x1, y + y1, x - x1, y + y1);
		LCD_Write_DATA(ch,cl);
		setXY(x + x1, y - y1, x + x1, y - y1);
		LCD_Write_DATA(ch,cl);
		setXY(x - x1, y - y1, x - x1, y - y1);
		LCD_Write_DATA(ch,cl);
		setXY(x + y1, y + x1, x + y1, y + x1);
		LCD_Write_DATA(ch,cl);
		setXY(x - y1, y + x1, x - y1, y + x1);
		LCD_Write_DATA(ch,cl);
		setXY(x + y1, y - x1, x + y1, y - x1);
		LCD_Write_DATA(ch,cl);
		setXY(x - y1, y - x1, x - y1, y - x1);
		LCD_Write_DATA(ch,cl);
	}
	*P_CS |= B_CS;
	if (orient==PORTRAIT)
		setXY(0,0,239,319);
	else
		setXY(0,0,319,239);
}

void ITDB02::fillCircle(int x, int y, int radius)
{
	*P_CS &= ~B_CS;
	for(int y1=-radius; y1<=radius; y1++) 
		for(int x1=-radius; x1<=radius; x1++) 
			if(x1*x1+y1*y1 <= radius*radius) 
			{
				setXY(x+x1, y+y1, x+x1, y+y1);
				LCD_Write_DATA(((fcolorr&248)|fcolorg>>5),((fcolorg&28)<<3|fcolorb>>3));
			}
	*P_CS |= B_CS;
	if (orient==PORTRAIT)
		setXY(0,0,239,319);
	else
		setXY(0,0,319,239);
}

void ITDB02::clrScr()
{
	long i;
	
	*P_CS &= ~B_CS;
	if (orient==PORTRAIT)
		setXY(0,0,239,319);
	else
		setXY(0,0,319,239);
	*P_RS |= B_RS;
	for (i=0; i<76800; i++)
	{
		LCD_Writ_Bus(0,0);
	}
	*P_CS |= B_CS;
}

void ITDB02::fillScr(byte r, byte g, byte b)
{
	long i;
	char ch, cl;
	
	ch=((r&248)|g>>5);
	cl=((g&28)<<3|b>>3);

	*P_CS &= ~B_CS;
	if (orient==PORTRAIT)
		setXY(0,0,239,319);
	else
		setXY(0,0,319,239);
	*P_RS |= B_RS;
	for (i=0; i<76800; i++)
	{
		LCD_Writ_Bus(ch,cl);
	}
	*P_CS |= B_CS;
}

void ITDB02::setColor(byte r, byte g, byte b)
{
	fcolorr=r;
	fcolorg=g;
	fcolorb=b;
}

void ITDB02::setBackColor(byte r, byte g, byte b)
{
	bcolorr=r;
	bcolorg=g;
	bcolorb=b;
}

void ITDB02::setPixel(byte r,byte g,byte b)
{
	LCD_Write_DATA(((r&248)|g>>5),((g&28)<<3|b>>3));
}

void ITDB02::drawPixel(int x, int y)
{
	*P_CS &= ~B_CS;
	setXY(x, y, x, y);
	setPixel(fcolorr, fcolorg, fcolorb);
	*P_CS |= B_CS;
	if (orient==PORTRAIT)
		setXY(0,0,239,319);
	else
		setXY(0,0,319,239);
}

void ITDB02::drawLine(int x1, int y1, int x2, int y2)
{
	int tmp;
	double delta, tx, ty;
	double m, b, dx, dy;
	char ch, cl;
	
	ch=((fcolorr&248)|fcolorg>>5);
	cl=((fcolorg&28)<<3|fcolorb>>3);

	if (((x2-x1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
    if (((y2-y1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	if (y1==y2)
	{
		if (x1>x2)
		{
			tmp=x1;
			x1=x2;
			x2=tmp;
		}
		drawHLine(x1, y1, x2-x1);
	}
	else if (x1==x2)
	{
		if (y1>y2)
		{
			tmp=y1;
			y1=y2;
			y2=tmp;
		}
		drawVLine(x1, y1, y2-y1);
	}
	else if (abs(x2-x1)>abs(y2-y1))
	{
		*P_CS &= ~B_CS;
		delta=(double(y2-y1)/double(x2-x1));
		ty=double(y1);
		if (x1>x2)
		{
			for (int i=x1; i>=x2; i--)
			{
				setXY(i, int(ty+0.5), i, int(ty+0.5));
				LCD_Write_DATA(ch, cl);
        		ty=ty-delta;
			}
		}
		else
		{
			for (int i=x1; i<=x2; i++)
			{
				setXY(i, int(ty+0.5), i, int(ty+0.5));
				LCD_Write_DATA(ch, cl);
        		ty=ty+delta;
			}
		}
		*P_CS |= B_CS;
	}
	else
	{
		*P_CS &= ~B_CS;
		delta=(float(x2-x1)/float(y2-y1));
		tx=float(x1);
        if (y1>y2)
        {
			for (int i=y2+1; i>y1; i--)
			{
		 		setXY(int(tx+0.5), i, int(tx+0.5), i);
				LCD_Write_DATA(ch, cl);
        		tx=tx+delta;
			}
        }
        else
        {
			for (int i=y1; i<y2+1; i++)
			{
		 		setXY(int(tx+0.5), i, int(tx+0.5), i);
				LCD_Write_DATA(ch, cl);
        		tx=tx+delta;
			}
        }
		*P_CS |= B_CS;
	}

	if (orient==PORTRAIT)
		setXY(0,0,239,319);
	else
		setXY(0,0,319,239);
}

void ITDB02::drawHLine(int x, int y, int l)
{
	char ch, cl;
	
	ch=((fcolorr&248)|fcolorg>>5);
	cl=((fcolorg&28)<<3|fcolorb>>3);

	*P_CS &= ~B_CS;
	setXY(x, y, x+l, y);
	for (int i=0; i<l+1; i++)
	{
		LCD_Write_DATA(ch, cl);
	}
	*P_CS |= B_CS;
}

void ITDB02::drawVLine(int x, int y, int l)
{
	char ch, cl;
	
	ch=((fcolorr&248)|fcolorg>>5);
	cl=((fcolorg&28)<<3|fcolorb>>3);

	*P_CS &= ~B_CS;
	setXY(x, y, x, y+l);
	for (int i=0; i<l; i++)
	{
		LCD_Write_DATA(ch, cl);
	}
	*P_CS |= B_CS;
}

void ITDB02::printChar(byte c, int x, int y)
{
	byte i,j,ch;
	word temp; 

	*P_CS &= ~B_CS;
  
	if (orient==PORTRAIT)
	{
		setXY(x,y,x+cfont.x_size-1,y+cfont.y_size-1);
	  
		temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
		for(j=0;j<((cfont.x_size/8)*cfont.y_size);j++)
		{
			ch=pgm_read_byte(&cfont.font[temp]);
			for(i=0;i<8;i++)
			{   
				if((ch&(1<<(7-i)))!=0)   
				{
					setPixel(fcolorr, fcolorg, fcolorb);
				} 
				else
				{
					setPixel(bcolorr, bcolorg, bcolorb);
				}   
			}
			temp++;
		}
	}
	else
	{
		temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;

		for(j=0;j<((cfont.x_size/8)*cfont.y_size);j+=(cfont.x_size/8))
		{
			setXY(x,y+(j/(cfont.x_size/8)),x+cfont.x_size-1,y+(j/(cfont.x_size/8)));
			for (int zz=(cfont.x_size/8)-1; zz>=0; zz--)
			{
				ch=pgm_read_byte(&cfont.font[temp+zz]);
				for(i=0;i<8;i++)
				{   
					if((ch&(1<<i))!=0)   
					{
						setPixel(fcolorr, fcolorg, fcolorb);
					} 
					else
					{
						setPixel(bcolorr, bcolorg, bcolorb);
					}   
				}
			}
			temp+=(cfont.x_size/8);
		}
	}
	*P_CS |= B_CS;
}

void ITDB02::rotateChar(byte c, int x, int y, int pos, int deg)
{
	byte i,j,ch;
	word temp; 
	int newx,newy;
	double radian;
	radian=deg*0.0175;  

	*P_CS &= ~B_CS;

	temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
	for(j=0;j<cfont.y_size;j++) 
	{
		for (int zz=0; zz<(cfont.x_size/8); zz++)
		{
			ch=pgm_read_byte(&cfont.font[temp+zz]); 
			for(i=0;i<8;i++)
			{   
				newx=x+(((i+(zz*8)+(pos*cfont.x_size))*cos(radian))-((j)*sin(radian)));
				newy=y+(((j)*cos(radian))+((i+(zz*8)+(pos*cfont.x_size))*sin(radian)));

				setXY(newx,newy,newx+1,newy+1);
				
				if((ch&(1<<(7-i)))!=0)   
				{
					setPixel(fcolorr, fcolorg, fcolorb);
				} 
				else  
				{
					setPixel(bcolorr, bcolorg, bcolorb);
				}   
			}
		}
		temp+=(cfont.x_size/8);
	}
	*P_CS |= B_CS;
}

void ITDB02::print(char *st, int x, int y, int deg)
{
	int stl, i;

	stl = strlen(st);

	if (orient==PORTRAIT)
	{
	if (x==RIGHT)
		x=240-(stl*cfont.x_size);
	if (x==CENTER)
		x=(240-(stl*cfont.x_size))/2;
	}
	else
	{
	if (x==RIGHT)
		x=320-(stl*cfont.x_size);
	if (x==CENTER)
		x=(320-(stl*cfont.x_size))/2;
	}

	for (i=0; i<stl; i++)
		if (deg==0)
			printChar(*st++, x + (i*(cfont.x_size)), y);
		else
			rotateChar(*st++, x, y, i, deg);
}

void ITDB02::printNumI(long num, int x, int y)
{
  char buf[25];
  char st[27];
  boolean neg=false;
  int c=0;
  
  if (num==0)
  {
	  st[0]=48;
	  st[1]=0;
  }
  else
  {
	  if (num<0)
	  {
		neg=true;
		num=-num;
	  }
	  
	  while (num>0)
	  {
		buf[c]=48+(num % 10);
		c++;
		num=(num-(num % 10))/10;
	  }
	  buf[c]=0;
	  
	  if (neg)
	  {
		st[0]=45;
	  }
	  
	  for (int i=0; i<c; i++)
	  {
		st[i+neg]=buf[c-i-1];
	  }
	  st[c+neg]=0;
  }

  print(st,x,y);
}

void ITDB02::printNumF(double num, byte dec, int x, int y)
{
  char buf[25];
  char st[27];
  boolean neg=false;
  int c=0;
  int c2;
  unsigned long inum;
  
  if (num==0)
  {
	  st[0]=48;
	  st[1]=46;
	  for (int i=0; i<dec; i++)
		  st[2+i]=48;
	  st[2+dec]=0;
  }
  else
  {
	  if (num<0)
	  {
		neg=true;
		num=-num;
	  }
	  
	  if (dec<1)
		dec=1;
	  if (dec>5)
		dec=5;
	  
	  inum=long(num*pow(10,dec));
	  
	  while (inum>0)
	  {
		buf[c]=48+(inum % 10);
		c++;
		inum=(inum-(inum % 10))/10;
	  }
	  if ((num<1) and (num>0))
	  {
		  buf[c]=48;
		  c++;
	  }
	  buf[c]=0;
	  
	  if (neg)
	  {
		st[0]=45;
	  }
	  
	  c2=neg;
	  for (int i=0; i<c; i++)
	  {
		st[c2]=buf[c-i-1];
		c2++;
		if ((c-(c2-neg))==dec)
		{
		  st[c2]=46;
		  c2++;
		}
	  }
	  st[c2]=0;
  }

  print(st,x,y);
}

void ITDB02::setFont(uint8_t* font)
{
	cfont.font=font;
	cfont.x_size=pgm_read_byte(&cfont.font[0]);
	cfont.y_size=pgm_read_byte(&cfont.font[1]);
	cfont.offset=pgm_read_byte(&cfont.font[2]);
	cfont.numchars=pgm_read_byte(&cfont.font[3]);
}

void ITDB02::drawBitmap(int x, int y, int sx, int sy, unsigned int* data, int scale)
{
	unsigned int col;
	int tx, ty, tc, tsx, tsy;

	if (scale==1)
	{
		if (orient==PORTRAIT)
		{
			*P_CS &= ~B_CS;
			setXY(x, y, x+sx-1, y+sy-1);
			for (tc=0; tc<(sx*sy); tc++)
			{
				col=pgm_read_word(&data[tc]);
				LCD_Write_DATA(col>>8,col & 0xff);
			}
			*P_CS |= B_CS;
		}
		else
		{
			*P_CS &= ~B_CS;
			for (ty=0; ty<sy; ty++)
			{
				setXY(x, y+ty, x+sx-1, y+ty);
				for (tx=sx; tx>=0; tx--)
				{
					col=pgm_read_word(&data[(ty*sx)+tx]);
					LCD_Write_DATA(col>>8,col & 0xff);
				}
			}
			*P_CS |= B_CS;
		}
	}
	else
	{
		if (orient==PORTRAIT)
		{
			*P_CS &= ~B_CS;
			for (ty=0; ty<sy; ty++)
			{
				setXY(x, y+(ty*scale), x+((sx*scale)-1), y+(ty*scale)+scale);
				for (tsy=0; tsy<scale; tsy++)
					for (tx=0; tx<sx; tx++)
					{
						col=pgm_read_word(&data[(ty*sx)+tx]);
						for (tsx=0; tsx<scale; tsx++)
							LCD_Write_DATA(col>>8,col & 0xff);
					}
			}
			*P_CS |= B_CS;
		}
		else
		{
			*P_CS &= ~B_CS;
			for (ty=0; ty<sy; ty++)
			{
				for (tsy=0; tsy<scale; tsy++)
				{
					setXY(x, y+(ty*scale)+tsy, x+((sx*scale)-1), y+(ty*scale)+tsy);
					for (tx=sx; tx>=0; tx--)
					{
						col=pgm_read_word(&data[(ty*sx)+tx]);
						for (tsx=0; tsx<scale; tsx++)
							LCD_Write_DATA(col>>8,col & 0xff);
					}
				}
			}
			*P_CS |= B_CS;
		}
	}
}

void ITDB02::drawBitmap(int x, int y, int sx, int sy, unsigned int* data, int deg, int rox, int roy)
{
	unsigned int col;
	int tx, ty, newx, newy;
	byte r, g, b;
	double radian;
	radian=deg*0.0175;  

	if (deg==0)
		drawBitmap(x, y, sx, sy, data);
	else
	{
		*P_CS &= ~B_CS;
		for (ty=0; ty<sy; ty++)
			for (tx=0; tx<sx; tx++)
			{
				col=pgm_read_word(&data[(ty*sx)+tx]);

				newx=x+rox+(((tx-rox)*cos(radian))-((ty-roy)*sin(radian)));
				newy=y+roy+(((ty-roy)*cos(radian))+((tx-rox)*sin(radian)));

				setXY(newx, newy, newx, newy);
				LCD_Write_DATA(col>>8,col & 0xff);
			}
		*P_CS |= B_CS;
	}
}
