#include "PCF8575.h"
#include "PCint.h"

PCF8575::PCF8575(){
	resetRegister();
}

PCF8575::~PCF8575(){
	/* DO NOTHING */
}

void PCF8575::begin(int SADR){
	PCFaddress=SADR;
	Wire.begin();
}

void PCF8575::pinMode(int pin, int mode){
	bitWrite(PCFTRISA,pin,mode);
}

void PCF8575::digitalWrite(int pin,int value){
	if((pin >= 0) && (pin < 16)){
		bitWrite(PCFPORTA,pin,value);
		i2cSend();
	}
}

int PCF8575::digitalRead(int pin){
	if((pin >= 0) && (pin < 16)){
		i2cRead();
		return bitRead(PCFPORTA,pin);
	}
}

void PCF8575::write(int value){
	PCFPORTA = value;
	i2cSend();
}

void PCF8575::pullUp(int pin){
	if((pin >= 0) && (pin < 16)){
		PCFPULL[pin] == 1;
		i2cRead();
		bitWrite(PCFPORTA,pin,1);
		i2cSend(PCFPORTA);
	}
}

void PCF8575::pullDown(int pin){
	if((pin >= 0) && (pin < 16)){
		PCFPULL[pin] == 2;
		i2cRead();
		bitWrite(PCFPORTA,pin,0);
		i2cSend(PCFPORTA);
	}
}

int PCF8575::read(){
	i2cRead();
	return PCFPORTA;
}

void PCF8575::clear(){
		PCFPORTA = 0x00;
		i2cSend();
}

void PCF8575::set(){
		PCFPORTA = 0xFFFF;
		i2cSend();
}

void PCF8575::toggle(int pin){
	if((pin >= 0) && (pin < 16)){
		i2cRead();
		bitWrite(PCFPORTA,pin,!bitRead(PCFPORTA,pin));
		i2cSend();
	}
}

void PCF8575::blink(int pin,int time,int wait){
	if((pin >= 0) && (pin < 16)){
		i2cRead();
		for(int i=0;i<time;i++){
			bitWrite(PCFPORTA,pin,0);
			i2cSend();
			delay(wait);
			bitWrite(PCFPORTA,pin,1);
			i2cSend();
			delay(wait);
		}
	}
}

void PCF8575::enableInterrupt(int pin,void(* selfCheckFunction)(void)){
	PCFIntPin = pin;
	pinMode(PCFIntPin,INPUT);
	PCattachInterrupt(PCFIntPin,selfCheckFunction,FALLING);
}

void PCF8575::disableInterrupt(){
	PCdetachInterrupt(PCFIntPin);
}

#ifdef INT_INPUT_ONLY
#define INT_CHECK (PCFTRISA[i] == INPUT)
#else
#define INT_CHECK true
#endif

void PCF8575::checkForInterrupt(){
	sei();
	PCFBUFFER = i2cRead(0x00);
	for(int i=0;i<16;i++){
		switch(PCFINT[i]){
			case CHANGE:
				if(INT_CHECK && (bitRead(PCFPORTA,i) != bitRead(PCFBUFFER,i)))
					PCFJMP[i]();
				break;
			case LOW:
				if(INT_CHECK && (bitRead(PCFBUFFER,i) == 0))
					PCFJMP[i]();
				break;
			case FALLING:
				if(INT_CHECK && (bitRead(PCFPORTA,i) == 1) && (bitRead(PCFBUFFER,i) == 0))
					PCFJMP[i]();
				break;
			case RISING:
				if(INT_CHECK && (bitRead(PCFPORTA,i) == 0) && (bitRead(PCFBUFFER,i) == 1))
					PCFJMP[i]();
				break;
			case 255:
				break;
		}
	}
}

void PCF8575::attachInterrupt(int pin,void (*userFunc)(void),int mode){
	if((pin >= 0) && (pin < 16)){
		PCFINT[pin] = mode;
		PCFJMP[pin] = userFunc;
	}
}

void PCF8575::detachInterrupt(int pin){
	if((pin >= 0) && (pin < 16)){
		PCFINT[pin] = 255;
	}
}

void PCF8575::resetRegister(){
	PCFPORTA =0;
	PCFTRISA =0;
	PCFBUFFER =0;
	for(int i=0;i<8;i++)
			PCFINT[i] = 255;
}

void PCF8575::i2cSend(){
	PCFBUFFER = i2cRead(0x00);
	for(int i=0;i<16;i++){
		if(bitRead(PCFTRISA,i) == INPUT)
			bitWrite(PCFPORTA,i,bitRead(PCFBUFFER,i));
		if(PCFPULL[i] == 1) bitWrite(PCFPORTA,i,1); // Required for unblock pull level
		if(PCFPULL[i] == 2) bitWrite(PCFPORTA,i,0); // Required for unblock pull level
	}
	Wire.beginTransmission(PCFaddress);
	Wire.write((uint8_t)(PCFPORTA & 0xFF));
	Wire.write((uint8_t)((PCFPORTA & 0xFF00) >> 8));
	Wire.endTransmission();
}

void PCF8575::i2cSend(unsigned int mask){
	Wire.beginTransmission(PCFaddress);
	Wire.write((uint8_t)(PCFPORTA & 0xFF));
	Wire.write((uint8_t)((PCFPORTA & 0xFF00) >> 8));
	Wire.endTransmission();
}

void PCF8575::i2cRead(){
  unsigned int value = 0x00;
  Wire.requestFrom(PCFaddress, 1);
  if(Wire.available() >= 2) {
    value = Wire.read();
	value += Wire.read() << 8;
  }
  PCFPORTA = value;
}

unsigned int PCF8575::i2cRead(unsigned int value){
  Wire.requestFrom(PCFaddress, 1);
  if(Wire.available()) {
    value = Wire.read();
	value += Wire.read() << 8;
  }
  return value;
}
