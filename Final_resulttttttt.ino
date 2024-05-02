#include <NewPing.h>
#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

#define trigPin1 A4
#define echoPin1 A5
#define trigPin2 A0
#define echoPin2 A1
#define trigPin3 A2
#define echoPin3 A3

long duration, distance, RightSensor, BackSensor,FrontSensor,LeftSensor;

void setup(){

 motor1.setSpeed(255);
 motor2.setSpeed(255);
 motor3.setSpeed(255);
 motor4.setSpeed(255);
 
 motor1.run(RELEASE);
 motor2.run(RELEASE);
 motor3.run(RELEASE);
 motor4.run(RELEASE);
 
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);
}


void loop(){
  
SonarSensor(trigPin1, echoPin1);
RightSensor = distance;
SonarSensor(trigPin2, echoPin2);
LeftSensor = distance;
SonarSensor(trigPin3, echoPin3);
FrontSensor = distance;


if( (FrontSensor<=25 && LeftSensor<=30) || LeftSensor<=20 )
{
  Serial.println("Turn right");
  Right();
  delay(750);
}

else if((FrontSensor<=25 &&  RightSensor<=30) || RightSensor<=20 )
{
  Serial.println("Turn left");
  Left();
  delay(750);
}

else if(FrontSensor<=25)
{
  Serial.println("Turn");
 Stop();
 delay(100);
 Backward();
 delay(500);
  Right();
  delay(2000);
}

else
{
  Serial.println("Forward");
  Forward();
}
delay(5);
 
}

//FUNCTIONS

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = duration/58.2; 
}

void Stop(){

 motor1.run(RELEASE);
 motor2.run(RELEASE);
 motor3.run(RELEASE);
 motor4.run(RELEASE);
 delay(200);
}


void Forward()
{
 Serial.println("Backward");
 
 motor1.run(BACKWARD);
 motor2.run(BACKWARD);
 motor3.run(BACKWARD);
 motor4.run(BACKWARD);
}


void Backward()
{
 Serial.println("Forward");

 motor1.run(FORWARD);
 motor2.run(FORWARD);
 motor3.run(FORWARD);
 motor4.run(FORWARD);
}


void Right()
{
 Serial.println("Right");
 
 motor1.run(FORWARD);
 motor2.run(FORWARD);
 motor3.run(BACKWARD);
 motor4.run(BACKWARD);
}


void Left()
{
 Serial.println("Left");
 
 motor1.run(BACKWARD);
 motor2.run(BACKWARD);
 motor3.run(FORWARD);
 motor4.run(FORWARD);
}