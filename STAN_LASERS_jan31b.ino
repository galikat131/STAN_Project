#include <AFmotor.h>

void setup (){
    Serial.begin(9600);
    pinMode(0, INPUT);
    pinMode(1, INPUT);
}

void loop ()
{
  startRead();  
}

int startRead() {
  Serial.print(analogRead(0));
  Serial.print("        ");
   Serial.println(analogRead(1));
  delay (400);
}
st
