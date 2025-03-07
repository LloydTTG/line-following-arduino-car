#include <Servo.h>

Servo myServo;

int servoPin = 8

int ena = 5; //right speed control
int in1 = 6; //right forward
int in2 = 7; //right backward

int enb = 9; //left speed control
int in3 = 10; //left forward
int in4 = 11; //left backward

int outLeft = 12; // input pin of left ir sensor
int outRight = 13; // input pin of right ir sensor

int trigPin = 3; // 
int echoPin = 4;


float duration;
float distanceCM;

void setup() {
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(outLeft, INPUT);
  pinMode(outRight, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(servoPin);
  analogWrite(ena,0);
  analogWrite(enb,0);
  myServo.write(90);
}

void loop() {
 
  //both detect white, go forward
  if (digitalRead(outLeft)==LOW && digitalRead(outRight)==LOW){
    move(1);
  }
  //only left detects white, turn right
  else if (digitalRead(outLeft)==LOW && digitalRead(outRight)==HIGH){
    move (3);
  }

  //only right detects white, turn left
  else if (digitalRead(outLeft)==HIGH && digitalRead(outLeft)==LOW){
    move(2);
  }
  
  else{
    analogWrite(ena,0);
    analogWrite(enb,0);
  }



  duration = pulseIn(echoPin, HIGH);
  distanceCM = (duration*0.034)/2;

  if (distanceCM <=15){
    myServo.write(150); 
    delay(1000); // checking left
    if (distanceCM <=20){ // detecting obstacle
      myServo.write(30); 
      delay(1000); // checking right
      if (distanceCM<=20){
        exit(0); // die if obstacles
      }
      else if (distanceCM >=20){ // turn right if nothing on the right
        move(3);
        delay(500); // 45 degree turn
        move(1);
        delay(500);
        move(2);
        delay(500);
        move(1);
        delay(500);
        move(2);
        delay(500);
        move(1);
        delay(500);
            
      }
    }
    else if (distanceCM >= 20){ // turn left if nothing on the left
      move(2);
      delay(500);
      move(1);
      delay(500);
      move(3);
      delay(500);
      move(1);
      delay(500);
      move(3);
      delay(500);
      move(1);
      delay(500);
    }
    }
    else{
      myServo.write(90); // continue moving forward, no obstacle
    }
  }

}

void move(int direction){
  if(direction == 1){ // moving forward
  analogWrite(ena, 110);
  analogWrite(enb, 110);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  }
  else if(direction == 2){ //turning left
  analogWrite(ena, 50);
  analogWrite(enb, 110);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  }
  else if(direction == 3){ //turning right
  analogWrite(ena, 110);
  analogWrite(enb, 50);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  }
