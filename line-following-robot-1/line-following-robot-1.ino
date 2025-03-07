int ena = 5; //right speed control
int in1 = 6; //right forward
int in2 = 7; //right backward

int motorAspeed = 140;
int motorBspeed = 107;

int motorAturnspeed = 70
int motorBturnspeed = 54

int enb = 9; //left speed control
int in3 = 10; //left forward
int in4 = 11; //left backward

int outLeft = 12; // input pin of left ir sensor
int outRight = 13; // input pin of right ir sensor

void setup() {
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(outLeft, INPUT);
  pinMode(outRight, INPUT);
  analogWrite(ena,0);
  analogWrite(enb,0);
  Serial.print(9600);
}

void loop() {
 
 Serial.print("Left (HIGH = black): ");
 Serial.print(digitalRead(outLeft));
 Serial.print(", Right (HIGH = black): ");
 Serial.print(digitalRead(outRight));

  //both detect white, go forward
  if (digitalRead(outLeft)==LOW && digitalRead(outRight)==LOW){
      analogWrite(ena, motorAspeed);
      analogWrite(enb, motorBspeed);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
  }
  //only left detects white, turn right
  else if (digitalRead(outLeft)==LOW && digitalRead(outRight)==HIGH){
    analogWrite(enb, motorBturnspeed);
    analogWrite(ena, motorAturnspeed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);  }

  //only right detects white, turn left
  else if (digitalRead(outLeft)==HIGH && digitalRead(outRight)==LOW){
    analogWrite(ena, motorAturnspeed);
    analogWrite(enb, motorBturnspeed);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  
  else{
    analogWrite(ena,0);
    analogWrite(enb,0);
  }
}
