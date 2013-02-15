boolean laser1 = false;
boolean laser2 = false;
int initial1;
int initial2;

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
  Serial.print(analogRead(0)-initial1);
  Serial.print("        ");
  Serial.println(analogRead(1)-initial2);
  laser1 = laserBlocked(analogRead(0)-initial1);
  laser2 = laserBlocked(analogRead(1)-initial2);
  crossingDirection();
  delay (20);
}

boolean laserBlocked(int brightness){
  if(brightness > 400){
    return true;
  }
  else{
    return false;
  }
}

void crossingDirection(){
  if(laser1 && !laser2){
    Serial.print("Laser1 Blocked first");
  }
  if(laser2 && !laser1){
    Serial.print("Laser2 Blocked first");
  }
  if(laser1 && laser2){
    Serial.print("Both Lasers Blocked");
  }

  
}
