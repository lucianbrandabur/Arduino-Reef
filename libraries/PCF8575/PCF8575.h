#ifndef PCF8575_H
#define PCF8575_H

#include <Arduino.h>
#include <Wire.h>

typedef void (*FunctionPointer)(void);

class PCF8575 {
public:
        PCF8575();
        ~PCF8575();
		void begin(int SADR);
		void pinMode(int pin, int mode);
		void digitalWrite(int pin,int value);
		int digitalRead(int pin);
		void write(int value);
		int read();
		void clear();
		void set();
		void pullUp(int pin);
		void pullDown(int pin);
		void toggle(int pin);
		void blink(int pin,int time,int wait);
		void enableInterrupt(int pin,void(* selfCheckFunction)(void)); // Require pointer to an user create gateway function because checkForInterrupt() is in PCF8575 namespace.
		void disableInterrupt();
		void attachInterrupt(int pin,void (*userFunc)(void),int mode);
		void detachInterrupt(int pin);
		void checkForInterrupt();
private:
		volatile unsigned int PCFPORTA;
		volatile unsigned int PCFPULL[16];
		volatile unsigned int PCFTRISA;
		volatile unsigned int PCFBUFFER;
		volatile int PCFaddress;
		unsigned int PCFIntPin;
		volatile unsigned int PCFINT[16];
		volatile FunctionPointer PCFJMP[16];
		void resetRegister();
		void i2cSend();
		void i2cSend(unsigned int mask);
		void i2cRead();
		unsigned int i2cRead(unsigned int value);
};
 

#endif
