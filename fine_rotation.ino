int leftW;
int rightW;
int echo = 12;
int trigger = 13;
long int echPulse;
int prevTime = 0;
int count = 0;
int timeCur;

void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  pinMode(echo, INPUT);
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

  timeCur = millis();
  
  leftW = digitalRead(A0);
  rightW = digitalRead(A1);
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  echPulse = pulseIn(echo, HIGH);
  float distance = (echPulse * 0.0343) / 2;
  
  Serial.println(count);
  
  if(distance <= 20){
    stopW();
  }else{
    forward();
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
//      stopW();
      if(timeCur - prevTime >= 1000){
        count++;
        prevTime = timeCur;
      }
      if(count == 4){
        right();
        count = 0;
        delay(1500);
      }
      if(count == 3){
        forward();
        stopW();
        delay(500);
      }
      else{
        forward();
      }
    }
  }
}