#include <Servo.h>

// Motor control pins
int ena = 5; 
int enb = 9;
int in1 = 6, in2 = 7, in3 = 10, in4 = 11;

// IR sensors
int out1 = 12, out2 = 13;

// Ultrasonic sensor
int trigPin = 3, echoPin = 4;

// Servo motor
int servoPin = 8;
Servo myServo;

// Speed settings
int speedright = 112;
int speedleft = 112;

float duration, distanceCM;

void setup() {
  pinMode(out1, INPUT);
  pinMode(out2, INPUT);

  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(servoPin);
  myServo.write(90); // Start servo at center position

  Serial.begin(9600);
}

// Function to measure distance using ultrasonic sensor
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return (duration * 0.034) / 2;
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(ena, 0);
  analogWrite(enb, 0);
}

// Function to move forward
void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, speedright);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, speedleft);
}

// Function to turn left
void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, speedright);
  analogWrite(enb, speedleft);
}

// Function to turn right
void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(ena, speedright);
  analogWrite(enb, speedleft);
}

// Function to avoid obstacle
void avoidObstacle() {
  stopMotors();
  delay(500);

  // Check left
  myServo.write(150);
  delay(500);
  float leftDistance = getDistance();

  // Check right
  myServo.write(30);
  delay(500);
  float rightDistance = getDistance();

  // Reset servo to center
  myServo.write(90);
  delay(500);

  if (leftDistance <= 20 && rightDistance <= 20) {
    Serial.println("Obstacle on both sides! Stopping.");
    stopMotors();
    return;
  } else if (rightDistance > 20) {
    Serial.println("Turning right in a semi-circular path.");
    turnRight();
    delay(1000);
    moveForward();
    delay(1000);
    turnLeft();
    delay(1000);
  } else {
    Serial.println("Turning left in a semi-circular path.");
    turnLeft();
    delay(1000);
    moveForward();
    delay(1000);
    turnRight();
    delay(1000);
  }
}

void loop() {
  distanceCM = getDistance();
  Serial.print("Distance: ");
  Serial.print(distanceCM);
  Serial.println(" cm");

  if (distanceCM <= 20) {
    avoidObstacle();
  } else {
    // Line Following Logic
    if (digitalRead(out1) == LOW && digitalRead(out2) == LOW) {
      Serial.println("IR1: white, IR2: white, move forward");
      moveForward();
    } else if (digitalRead(out1) == HIGH && digitalRead(out2) == LOW) {
      Serial.println("IR1: black, IR2: white, turn left");
      turnLeft();
    } else if (digitalRead(out1) == LOW && digitalRead(out2) == HIGH) {
      Serial.println("IR1: white, IR2: black, turn right");
      turnRight();
    } else {
      Serial.println("Both IR sensors detected black. Stopping.");
      stopMotors();
    }
  }
}





