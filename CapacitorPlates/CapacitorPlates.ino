#include <CapacitiveSensor.h>

CapacitiveSensor   plate1 = CapacitiveSensor(4,2);        // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
CapacitiveSensor   plate2 = CapacitiveSensor(4,6);        // 10 megohm resistor between pins 4 & 6, pin 6 is sensor pin, add wire, foil
//CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10 megohm resistor between pins 4 & 8, pin 8 is sensor pin, add wire, foil

int recentReadsLength = 10;
long recentReads[50];

long globalStart = millis();

void setup()                    
{

  plate1.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  plate2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);

  for (int i = 0; i < recentReadsLength; i++) {
    recentReads[i] = 0;
  }
}

long readingToDistance(long reading)
{
  if (reading == 0) return 0;
  return (long) (10000 / (sqrt(reading)));
}

void loop()                    
{
    long start = millis();
    long total1 =  plate1.capacitiveSensor(30);
    long total2 =  plate2.capacitiveSensor(30);
    //long total3 =  cs_4_8.capacitiveSensor(30);

//    Serial.print(millis() - start);        // check on performance in milliseconds
//    Serial.print("\t");                    // tab character for debug windown spacing

    Serial.print(millis() - globalStart);
    Serial.print("\t");
    Serial.print(total1);                    // time to charge
    Serial.print("\t");
    Serial.println(total2);                  // print sensor output 2
    
//    Serial.print("\t");
//    Serial.println(total3);                // print sensor output 3

    //delay(50);                             // arbitrary delay to limit data to serial port 
}

