#include <AFmotor.h>

void setup (){
    pinMode(11, OUTPUT);
    pinMode(13, INPUT);
}

int brightness = 0;
int isButtonDepressed;

void loop ()
{
  
  isButtonDepressed = digitalRead(13);
  
  if (isButtonDepressed)
  {
   
  analogWrite(11, brightness);
  
  brightness+=5;
  if (brightness > 200){
    brightness = 0;
  }
  
  }
  
  delay(50);
}

