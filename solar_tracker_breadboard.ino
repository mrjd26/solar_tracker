#include <Wire.h> //Include the Wire library
#include <MMA_7455.h> //Include the MMA_7455 library

MMA_7455 mySensor = MMA_7455(); //Make an instance of MMA_7455

char xVal, yVal, zVal; //Variables for the values from the sensor

const int RED = 2;
const int YELLOW = 1;
const int BLUE = 3;

const int v_EN = 6; //VERTICAL MOTOR ENABLE ON PIN 6
const int v_MC1 = 7; // vertical motor control 1
const int v_MC2 = 8; // vertical motor control 2

const int h_EN = 9; // horizontal motor enable on pin 12
const int h_MC1 = 10;  // horizontal motor control 1
const int h_MC2 = 11 ;  // horizontal motor control 2

int red_ldr = 0;
int yellow_ldr = 0;
int blue_ldr = 0;

void setup() {
  Serial.begin(9600);
  pinMode(v_EN, OUTPUT);
  pinMode(v_MC1, OUTPUT);
  pinMode(v_MC2, OUTPUT);
  pinMode(h_EN, OUTPUT);
  pinMode(h_MC1, OUTPUT);
  pinMode(h_MC2, OUTPUT);
  h_brake();
  v_brake();
  mySensor.initSensitivity(2);
}

void loop() {
  red_ldr = analogRead(RED);
  Serial.print("red ");
  Serial.println(red_ldr);
  yellow_ldr = analogRead(YELLOW);
  Serial.print("yellow ");
  Serial.println(yellow_ldr);
  blue_ldr = analogRead(BLUE);
  Serial.print("blue");
  Serial.println(blue_ldr);
  
  xVal = mySensor.readAxis('x'); //Read out the 'x' Axis
  yVal = mySensor.readAxis('y'); //Read out the 'y' Axis
  zVal = mySensor.readAxis('z'); //Read out the 'z' Axis
  
  Serial.print(xVal, DEC);
  Serial.print("\t");
  Serial.print(yVal, DEC);
  Serial.print("\t");
  Serial.println(zVal, DEC);
  
  delay(1000);
  if (blue_ldr > red_ldr + 40) {
    left(); 
    Serial.println("should be moving left");
  }
  else if (red_ldr > blue_ldr + 40) {
    right();
    Serial.println("should be moving right");
  }  
  else {
    h_brake();
  }
  
  if (yellow_ldr > red_ldr + 40) {
    //move down as long as xVal is < 65
    if (xVal < 65){
      down();
    }
    else if (xVal > 65) {
      v_brake();
      Serial.println("xVal greater than 65");
    }
    Serial.println("should be moving down");
  }
  else if (red_ldr > yellow_ldr + 40 ) {
    //move up as long as xVal is > 0
    if (xVal > 0) {
      up();
    }
    else if (xVal < 0) {
      v_brake();
      Serial.println("xVal less than 0");
    }
    Serial.println("should be moving up");
  }
  else {
    v_brake();
  }
  
}  
 void left() {
   //move panel left
   digitalWrite(h_MC1, HIGH);
   digitalWrite(h_MC2, LOW);
   digitalWrite(h_EN, HIGH);
  } 
 void right() {
   //move panel right
   digitalWrite(h_MC1, LOW);
   digitalWrite(h_MC2, HIGH);
   digitalWrite(h_EN, HIGH); 
}
 void h_brake() {
   digitalWrite(h_EN, LOW);
   digitalWrite(h_MC1, LOW);
   digitalWrite(h_MC2, LOW);
 }
 
 void v_brake() {
   digitalWrite(v_EN, LOW);
   digitalWrite(v_MC1, LOW);
   digitalWrite(v_MC2, LOW);
 }

 void up() {
  digitalWrite(v_MC1, LOW);
  digitalWrite(v_MC2, HIGH);
  digitalWrite(v_EN, HIGH); 
 }
 
 void down() {
  digitalWrite(v_MC1, HIGH);
  digitalWrite(v_MC2, LOW);
  digitalWrite(v_EN, HIGH);
 }
