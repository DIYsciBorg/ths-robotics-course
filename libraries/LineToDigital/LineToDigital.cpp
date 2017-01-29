/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "LineToDigital.h"

LineToDigital::LineToDigital(int Lpin, int Cpin, int Rpin, int Lthresh, int Cthresh, int Rthresh)
{
  pinMode(Lpin, INPUT);
  pinMode(Cpin, INPUT);
  pinMode(Rpin, INPUT);
  _lpin = Lpin;
  _cpin = Cpin;
  _rpin = Rpin;
  _lthresh = Lthresh;
  _cthresh = Cthresh;
  _rthresh = Rthresh;
}

int LineToDigital::LineLeft()
{
  if (int l = analogRead(_lpin) > _lthresh){
    return 1;
  }else{
    return 0;  
  }
}

int LineToDigital::LineCenter()
{
  if (int c = analogRead(_cpin) > _cthresh){
    return 1;
  }else{
    return 0;  
  }
}

int LineToDigital::LineRight()
{
  if (int r = analogRead(_rpin) > _rthresh){
    return 1;
  }else{
    return 0;  
  }
}
