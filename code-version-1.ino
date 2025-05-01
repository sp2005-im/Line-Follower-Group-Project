#include<Arduino.h>
#include<Servo.h>
#include <SparkFun_TB6612.h>

int d1 = A0;
int d2 = A1;
int d3 = A2;
int d4 = A3;
int d5 = A4;
int d6 = A5;


#define AIN1 9
#define BIN1 10
#define AIN2 8
#define BIN2 11
#define PWMA 3
#define PWMB 5
#define STBY 2

const int offsetA = 1;
const int offsetB = -1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motorr = Motor(AIN1, AIN2, PWMA, offsetA, STBY); //yellow wire
Motor motorl = Motor(BIN1, BIN2, PWMB, offsetB, STBY);


void setup(){

  pinMode(d1, INPUT);
  pinMode(d2, INPUT);
  pinMode(d3, INPUT);
  pinMode(d4, INPUT);
  pinMode(d5, INPUT);
  pinMode(d6, INPUT);
  Serial.begin(9600);
  delay(1000);

  motorr.drive(0);
  motorl.drive(0);
}

int error = 8;
int baseSpeed = 160;
int kp = 25;

void loop() {

  int values[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // right to left

  if(analogRead(d1) >800){
    values[0] = 1;
    motorl.drive(255);
    motorr.drive(0);
    Serial.println("RIGHTTTTT");
  }
  else if(analogRead(d2) > 800){
    values[1] = 1;
    motorl.drive(230);
    motorr.drive(0);
    Serial.println("RIGHT");
  }
  else if(analogRead(d3) > 800){
    values[2] = 1;
    motorl.drive(200);
    motorr.drive(0);
    Serial.println("right");
  }
  else if(analogRead(d4) > 800){
    values[3] = 1;
    motorr.drive(200);
    motorl.drive(0);
    Serial.println("left");
  }
  else if(analogRead(d5) > 800){
    values[4] = 1;
    motorr.drive(230);
    motorl.drive(0);
    Serial.println("LEFT");
  }
  else if(analogRead(d6) > 800){
    values[5] = 1;
    motorr.drive(255);
    motorl.drive(0);
    Serial.println("LEFTTTT");
    
  }
  delay(100);
}
