#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() 
{
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  mySwitch.enableTransmit(7);
  
}

void loop() 
{
    mySwitch.send(0x000010001000, 12);
    delay(500);
}
