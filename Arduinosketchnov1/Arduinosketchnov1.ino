#include <AFmotor.h>

#define I_TO_O_MUL 4
#define INPUT_MAX 1023
#define OUTPUT_MAX 255

int brightness = 0;

void setup (){
    Serial.begin(57600);
    pinMode(11, OUTPUT);
    pinMode(5, INPUT);
}



void loop ()
{
  int interval = analogRead(5) / I_TO_O_MUL;
  delay(interval);
  
  brightness += 10;
  if (brightness >= OUTPUT_MAX) {
    brightness = 0;
  }
  
  
  analogWrite(11, brightness * brightness / OUTPUT_MAX);
}

