/*
 Author: Alberto Tam Yong
 Date: 09-07-14
 
 PCA9555 Breakout Board
 Blink LED on pin 0.1
 
 LED circuit
 VCC --- |>|---/\/\---PCA9555
 LED   R=220
 
 Using a Teensy 2.0 for testing.
 If using and Arduino UNO, change LED pin to 13.
 */

#include <Wire.h>

//Define the devices you'll use
#define LED 11 //using a Teensy 2.0, LED is on pin 11
#define i2c_address 0x21

byte io = B11111111; //keeps track of the state of each output
//By default, they are all sourcing.

void setup()
{
  pinMode(LED,OUTPUT);
  delay(10);
  digitalWrite(LED,HIGH);

  Wire.begin(); //set microcontroller as master
  Wire.beginTransmission(i2c_address);
  Wire.write(0x06); //configure PORT0
  Wire.write(0x00); //B00000000, 0-7 output
  Wire.endTransmission();

  Wire.beginTransmission(i2c_address);
  Wire.write(0x02); //output PORT0
  Wire.write(io); //default. sourcing.
  Wire.endTransmission();

  delay(1000);
  digitalWrite(LED,LOW);
}

void loop()
{
  //Blink LED on 0.1
  Wire.beginTransmission(i2c_address);
  Wire.write(0x02); //output PORT0
  Wire.write(B11111110); //0=sinking, 1-7 sourcing
  Wire.endTransmission();
  delay(500);

  Wire.beginTransmission(i2c_address);
  Wire.write(0x02); //output PORT0
  Wire.write(B11111111); //0-7 sourcing
  Wire.endTransmission();
  delay(500);
}


