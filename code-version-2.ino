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

const int offsetA = -1;
const int offsetB = 1;

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
int baseSpeed = 220;
int kp = 25;

void loop() {

  int values[6] = {0, 0, 0, 0, 0, 0};
  int t = 800;

 
  if(analogRead(d6) > t){
    values[0] = 1;
  }
  if(analogRead(d5) > t){
    values[1] = 1;
  }
  if(analogRead(d4) > t){
    values[2] = 1;
  }
  if(analogRead(d3) > t){
    values[3] = 1;
  }
  if(analogRead(d2) > t){
    values[4] = 1;
  }
  if(analogRead(d1) > t){
    values[5] = 1;
  }
  error = 6;

  for(int i = 0; i < 6; i++){
    if(values[i] == 1){
      error = i;
      break;
    }
  }

  error -= 3;
  Serial.println(error);
  if(error == 3){
    motorr.drive(-135);

    motorl.drive(110);
  }
  else if(error == -3){
    motorr.drive(110);

    motorl.drive(-135);

  }

  else{

  if(error < 0){
    motorl.drive(baseSpeed + kp*error);
    if(baseSpeed - kp*error > 255){
      motorr.drive(255);
    }
    else{
      motorr.drive(baseSpeed - kp*error);
    }
    
  }

  if(error > 0){
    motorr.drive(baseSpeed - kp*error);
    if(baseSpeed + kp*error > 255){
      motorl.drive(255);
    }
    else{
      motorl.drive(baseSpeed + kp*error);
    }
    
  }

  if(error == 0){
    
    motorr.drive(baseSpeed);
    motorl.drive(baseSpeed);
  
  }

  }
  
}
