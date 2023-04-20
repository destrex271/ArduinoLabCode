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
int flag = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A2, INPUT);
  pinMode(A0, INPUT);
  pinMode(pin, INPUT);
  pinMode(echo, INPUT);
  pinMode(pin, INPUT);
  pinMode(trigger, OUTPUT);
  digitalWrite(pin , LOW);
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
  leftW = digitalRead(A2);
  rightW = digitalRead(A0);
  if(Serial.available() > 0 || flag == 0){
    char s = Serial.read();
    if(s == 'K'){
      flag = 1;
    }
  }
  if(flag == 1){
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
    }
  }
}