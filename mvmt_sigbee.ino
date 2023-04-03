// K forward

int leftW;
int rightW;
int echo = 12;
int trigger = 13;
long int echPulse;
int prevTime = 0;
int count = 0;
int pin = 4;
int timeCur;
bool mv = false;

void setup() {
  Serial.begin(9600);
  pinMode(A2, INPUT);
  pinMode(A0, INPUT);
  pinMode(echo, INPUT);
  pinMode(pin, INPUT);
  pinMode(trigger, OUTPUT);
  for (int i = 5; i < 9; i++) {
    pinMode(i, OUTPUT);
  }
  timeCur = 0;
}
void stopW(){
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}
void forward()
{
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}
void left()
{
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}
void right()
{
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}
void loop() {
  leftW = digitalRead(A0);
  rightW = digitalRead(A2);
  if(Serial.available() > 0){
    char s = Serial.read();
    switch(s){
      case 'K':
        moveFunc();
        break;
      case 'M':
        stopW();
        break;
      case 'W':
        forward();
        break;
      case 'A':
        left();
        break;
//      case 'S':
//        backward();
      case 'D':
        right();
        
    }
  }
  if(mv){
    moveFunc();
  }
}

void moveFunc(){
    if (leftW == 1 && rightW == 1) {
      forward();
    }
    else if (leftW == 1 && rightW == 0) {
      right();
    }
    else if (leftW == 0 && rightW == 1) {
      left();
    }
    else {
      forward();
//      if(timeCur - prevTime >= 1000){
//        count++;
//        prevTime = timeCur;
//      }
//      if(count == 4){
//        right();
//        count = 0;
//        delay(1500);
//      }
//      if(count == 3){
//        forward();
//        stopW();
//        delay(500);
//      }
//      else{
//        forward();
//      }
    }
}
