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
int flag = 1;
int ctr = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A2, INPUT); //right IR sensor
  pinMode(A0, INPUT); //left IR sensor
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
  int rec = digitalRead(pin);
  if(rec == HIGH){
    Serial.println("IN REC");
    stopW();
//    ctr = (ctr + 1)%3;
//    int StartTime = millis();
   int d = pulseIn(pin,HIGH);
   int gantryCounter = 0;
   if(d > 500 and d < 1500){
      //Serial.println(d);
      Serial.println("Gantry: 1");
      stopW();
      delay(1000);
    }
    else if (d> 1500 and d < 2500){
      //  Serial.println(d);
          Serial.println("Gantry: 2");
          stopW();
          delay(1000);
      }
    else if (d > 2500 and d < 3500){
     // Serial.println(d);
     
      Serial.println("Gantry: 3");
      gantryCounter=gantryCounter+1;
      Serial.print("The gantry Counter is: ");
      Serial.println(gantryCounter);
      stopW();
      delay(1000);
  
    }
   else {
       //Serial.println(d);
       Serial.println("Gantry: Unknown");
       
   }
  }
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
//      Serial.println("BLACK");
      if(timeCur - prevTime >= 1000){
        count++;
        prevTime = timeCur;
      }
      if(count == 4){
        right();
//        count = 0;
        delay(700);
      }
      if(count == 7){
        forward();
        stopW();
        right();
        delay(500);
      }
      if (count == 9){
        stopW();
        exit(0);
      }
      else{
        forward();
      }
    }
  }
}
