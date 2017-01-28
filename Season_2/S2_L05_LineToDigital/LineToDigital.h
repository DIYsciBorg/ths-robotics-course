/*
  line_sensor.h - Library for reading simple 3 element line sensor
  Created by Emery Premeaux, January 22, 2017.
  Released into the public domain.
*/
#ifndef LineToDigital_h
#define LineToDigital_h

#include "Arduino.h"

class LineToDigital
{
  public:
    LineToDigital(int Lpin, int Cpin, int Rpin, int Lthresh, int Cthresh, int Rthresh);
    int LineLeft();
    int LineCenter();
    int LineRight();
  private:
    int _lpin;
    int _cpin;
    int _rpin;
    int _lthresh;
    int _cthresh;
    int _rthresh;
};

#endif

