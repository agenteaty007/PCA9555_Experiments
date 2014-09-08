/*
 Author: Alberto Tam Yong
 Date: 09-07-14
 
 PCA9555 Breakout Board
 Button testing
 
 LED circuit
 VCC --- |>|---/\/\---PCA9555
 LED   R=220
 
 Button circuit
 PCA9555 ---./ .---GND
 
 Using a Teensy 2.0 for testing.
 If using and Arduino UNO, change LED pin to 13.
 */

#include <Wire.h>

//Define the devices you'll use
#define LED 11 //using a Teensy 2.0, LED is on pin 11
#define INT 10
#define i2c_address 0x21

byte io = B11111111; //keeps track of the state of each output
//By default, they are all sourcing.

void setup()
{
  pinMode(INT,INPUT);
  pinMode(LED,OUTPUT);
  delay(10);
  digitalWrite(LED,HIGH);

  Wire.begin(); //set microcontroller as master
  Wire.beginTransmission(i2c_address);
  Wire.write(0x06); //configure PORT0
  Wire.write(0x80); //B10000000, 0-6 output, 7 input
  Wire.endTransmission();

  Wire.beginTransmission(i2c_address);
  Wire.write(0x02); //output PORT0
  Wire.write(io); //default. all off, sourcing.
  Wire.endTransmission();

  delay(1000);
  digitalWrite(LED,LOW);
}

void loop()
{
  //Read inputs from PCA9555
  Wire.beginTransmission(0x21);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(0x21,1);
  byte input = Wire.read();

  //Is button grounded?
  if(input == B01111111)
  {
    Wire.beginTransmission(i2c_address);
    Wire.write(0x02); //output PORT0
    Wire.write(B00000000); //0-7 sinking
    Wire.endTransmission();
  }
  else
  {
    Wire.beginTransmission(i2c_address);
    Wire.write(0x02); //output PORT0
    Wire.write(B11111111); //0-7 sourcing
    Wire.endTransmission();
  }
}



