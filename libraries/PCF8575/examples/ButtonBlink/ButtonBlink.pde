#include <PCF8575.h> // Required for ... all 

#include <Wire.h> // Required for I2C communication

PCF8575 expander; // Create object from PCF8575 class

void setup(){

  Serial.begin(9600); // Setup serial for read echo
  
  expander.pinMode(0,OUTPUT); // Setup pin D0 as output
  expander.pinMode(15,OUTPUT); // Setup pin D1 as output
  expander.pinMode(3,INPUT); // Setup pin D3 as input

  expander.begin(0x20);
  
  expander.pullUp(3); // Enable pull-up resistor on pin D3 (button)
  
  expander.enableInterrupt(8,ISRgateway); // Enable interrupt by attach interruption handler to arduino pin D8 and save ISRgateway as callback function
  
  expander.attachInterrupt(3,ISRexpander,FALLING); // Attach an virtual interrupt on the pin D3 (button) of the PCF8575
}

void ISRgateway(){
  expander.checkForInterrupt(); // ISRgateway act as an wrapper for attachInterrupt from namespace PCF8575:: to the global scope
}

void ISRexpander(){ // ISRexpander will be call when the PCF8574 pin D3 will goes from high to low
  expander.blink(15,5,200); // Blink the led on pin D0 on PCF8574 (to test TWI into an ISR called function /debug)
}

void loop(){
 expander.blink(0,5,200);
 delay(1000);
} // Loop forever
