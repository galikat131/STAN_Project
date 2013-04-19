// Only print every 20 values
int printDelay = 0;
int laser1, laser2;
int initial1, initial2;
// One laser activated
int counter = 0;
int prevsLength = 4;
int prevs[4] = { 0, 0, 0, 0 };

void setup() {
    Serial.begin(9600);
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    initial1 = analogRead(0);
    initial2 = analogRead(1);
}

void loop()
{
  startRead();  
}

int startRead() {
  printDelay++;
  laser1 = laserBlocked(analogRead(0)-initial1);
  laser2 = laserBlocked(analogRead(1)-initial2);
  crossingDirection();
  delay(20);
  
  if (printDelay == 20) {
//    Serial.print(analogRead(0)-initial1);
//    Serial.print("        ");
//    Serial.println(analogRead(1)-initial2);
    printDelay=0;
  }
  
}


boolean laserBlocked(int brightness) {
  return (brightness > 400);
}

void movePrevsDown() {
  for (int i = 0; i < prevsLength - 1; i++) {
    prevs[i] = prevs[i+1];
  }
}

void crossingDirection() {
  // first bit is laser1; second bit is laser2
  int cur = laser1 | (laser2 << 1);
  if (cur != prevs[3]) {
    movePrevsDown();
    prevs[3] = cur;
    if (prevs[0] == 2 && prevs[1] == 3 && prevs[2] == 1 && prevs[3] == 0) {
      counter++;
      Serial.print("ENTERING: ");
      Serial.println(counter);
    } else if (prevs[0] == 1 && prevs[1] == 3 && prevs[2] == 2 && prevs[3] == 0) {
      counter--;
      Serial.print("EXITING: ");
      Serial.println(counter);
    }

  }
    
//  Serial.println(cur);
}


