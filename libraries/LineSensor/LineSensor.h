/*
  line_sensor.h - Library for reading simple 3 element line sensor
  Created by Emery Premeaux, January 22, 2017.
  Released into the public domain.
*/
#ifndef LineSensor_h
#define LineSensor_h

#include "Arduino.h"

class Line
{
  public:
    Line(int Lpin, int Cpin, int Rpin);
    int LineLeft();
    int LineCenter();
    int LineRight();
  private:
    int _lpin;
    int _cpin;
    int _rpin;
};

#endif

