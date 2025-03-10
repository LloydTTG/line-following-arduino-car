#include <Servo.h>

Servo myServo;

int servoPin = 8;

int ena = 5; //right speed control
int in1 = 6; //right forward
int in2 = 7; //right backward

int enb = 9; //left speed control
int in3 = 10; //left forward
int in4 = 11; //left backward

int outLeft = 12; // input pin of left ir sensor
int outRight = 13; // input pin of right ir sensor

int trigPin = 3; // output pin of ultrasonic sensor
int echoPin = 4; // input pin of ultrasonic sensor

int motorAspeed = 140;
int motorBspeed = 107;
int motorAturnspeed = 70;
int motorBturnspeed = 54;


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
  Serial.print(9600);
}

void move(int direction){
  if(direction == 1){ // moving forward
      analogWrite(ena, motorAspeed);
      analogWrite(enb, motorBspeed);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);

  }
  else if(direction == 2){ //turning left
    analogWrite(ena, motorAturnspeed);
    analogWrite(enb, motorBturnspeed);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if(direction == 3){ //turning right
    analogWrite(enb, motorBturnspeed);
    analogWrite(ena, motorAturnspeed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);  
  }

}


void loop() {
 
  duration = pulseIn(echoPin, HIGH);
  distanceCM = (duration*0.034)/2;
  Serial.println(duration);

  //both detect white, go forward, ultrasonic sensor detects nothing
  if (digitalRead(outLeft)==LOW && digitalRead(outRight)==LOW && distanceCM<=20){
      analogWrite(ena, motorAspeed);
      analogWrite(enb, motorBspeed);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
  }
  //only left detects white, turn right
  else if (digitalRead(outLeft)==LOW && digitalRead(outRight)==HIGH && distanceCM<=20){
    analogWrite(enb, motorBturnspeed);
    analogWrite(ena, motorAturnspeed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); 
  }

  //only right detects white, turn left
  else if (digitalRead(outLeft)==HIGH && digitalRead(outRight)==LOW && distanceCM<=20){
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






//moving forward is 1, moving left is 2, moving right is 3

  if (distanceCM <=20){
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
        delay(500); // 45 degree turn to the right
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
