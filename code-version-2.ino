#include <Arduino.h>
#include <SparkFun_TB6612.h>

// Pin definitions
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

Motor motorr = Motor(AIN1, AIN2, PWMA, offsetA, STBY); // Right motor
Motor motorl = Motor(BIN1, BIN2, PWMB, offsetB, STBY); // Left motor

// PID variables
float Kp = 50;    // Proportional gain
float Ki = 0;     // Integral gain (start with 0, tune later)
float Kd = 25;    // Derivative gain

float error = 0, lastError = 0, integral = 0, derivative = 0;
int baseSpeed = 200; // Base speed for motors

void setup() {
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

void loop() {
  // Read sensor values
  int sensors[6];
  sensors[0] = analogRead(d1) > 800 ? 1 : 0; // rightmost
  sensors[1] = analogRead(d2) > 800 ? 1 : 0;
  sensors[2] = analogRead(d3) > 740 ? 1 : 0;
  sensors[3] = analogRead(d4) > 800 ? 1 : 0;
  sensors[4] = analogRead(d5) > 800 ? 1 : 0;
  sensors[5] = analogRead(d6) > 800 ? 1 : 0; // leftmost

  // Assign weights
  int weights[6] = {5, 3, 1, -1, -3, -5};

  // Calculate weighted error
  int sum = 0, count = 0;
  for (int i = 0; i < 6; i++) {
    if (sensors[i]) {
      sum += weights[i];
      count++;
    }
  }

  if (count == 0) {
    // No line detected, stop or spin in place
    motorr.drive(0);
    motorl.drive(0);
    Serial.println("No line detected!");
    return;
  }

  error = (float)sum / count;

  // PID calculations
  integral += error;
  derivative = error - lastError;
  float correction = Kp * error + Ki * integral + Kd * derivative;

  // Calculate motor speeds
  int leftSpeed = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;

  // Constrain speeds
  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);

  // Drive motors
  motorl.drive(leftSpeed);
  motorr.drive(rightSpeed);

  // Debugging
  Serial.print("Error: "); Serial.print(error);
  Serial.print(" | Correction: "); Serial.print(correction);
  Serial.print(" | Left: "); Serial.print(leftSpeed);
  Serial.print(" | Right: "); Serial.println(rightSpeed);

  lastError = error;
  delay(10); // Small delay for stability
}
