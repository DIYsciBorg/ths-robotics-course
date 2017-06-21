/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "line_sensor.h"

Line::Line(int Lpin, int Cpin, int Rpin)
{
  pinMode(Lpin, INPUT);
  pinMode(Cpin, INPUT);
  pinMode(Rpin, INPUT);
  _lpin = Lpin;
  _cpin = Cpin;
  _rpin = Rpin;
}

int Line::LineLeft()
{
  return analogRead(_lpin);  
}

int Line::LineCenter()
{
  return analogRead(_cpin); 
}

int Line::LineRight()
{
  return analogRead(_rpin); 
}
