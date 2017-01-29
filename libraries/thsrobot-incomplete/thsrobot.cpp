/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "LineSensor.h"

PhotoSensor::PhotoSensor(int PSpin, int PSthreshold)
{
  pinMode(PSpin, INPUT);
  _PSpin = PSpin;
  _PSthreshold = PSThreshold;

}

int PhotoSensor::getAnalog()
{
  return analogRead(_PSpin);  
}

int PhotoSensor::getDigital()
{
  if (int l = analogRead(_PSpin) > _PSthreshold){
    return 1;
  }else{
    return 0;  
  }
}