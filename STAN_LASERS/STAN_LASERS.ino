boolean laser1 = false;
boolean laser2 = false;
int initial1;
int initial2;
// Only print every 20 values
int printDelay = 0;
// One laser activated
boolean pending = false;
int first;
int counter = 0;

void setup (){
    Serial.begin(9600);
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    initial1 = analogRead(0);
    initial2 = analogRead(1);
}

void loop ()
{
  startRead();  
}

int startRead() {
  printDelay++;
  laser1 = laserBlocked(analogRead(0)-initial1);
  laser2 = laserBlocked(analogRead(1)-initial2);
  crossingDirection();
  delay (20);
  
  if (printDelay == 20) {
    //Serial.print(analogRead(0)-initial1);
    //Serial.print("        ");
    //Serial.println(analogRead(1)-initial2);
    printDelay=0;
  }
  
}


boolean laserBlocked(int brightness){
  return (brightness > 400);
}

void crossingDirection(){
  
  // only laser 1 blocked
  if(laser1 && !laser2){
    if (!pending) {
      pending = true;
      first = 1;
    }
    else if (first == 2) {
      pending = false;
      Serial.print("ENTERING\n");
      counter++;
      Serial.print(counter);
      Serial.print(" people in the room\n");
    }
    //Serial.print("Laser1 Blocked \n");
  }
  
  // only laser 2 blocked
  else if(laser2 && !laser1){
    if (!pending) {
      pending = true;
      first = 2;
    }
    else if (first == 1) {
      pending = false;
      Serial.print("EXITING\n");
      counter--;
      Serial.print(counter);
      Serial.print(" people in the room\n");
    }
    //Serial.print("Laser2 Blocked \n");
  }
  
  // both blocked
  else if(laser1 && laser2){
    //Serial.print("Both Lasers Blocked \n");
    while(laser1 && laser2) {
      // Wait until person has entered room
       laser1 = laserBlocked(analogRead(0)-initial1);
       laser2 = laserBlocked(analogRead(1)-initial2);
    }
  }

  
}
