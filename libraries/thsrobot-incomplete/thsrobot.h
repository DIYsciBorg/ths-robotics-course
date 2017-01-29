/*
  line_sensor.h - Library for reading simple 3 element line sensor
  Created by Emery Premeaux, January 22, 2017.
  Released into the public domain.
*/
#ifndef thsrobot_h
#define thsrobot_h

#include "Arduino.h"

class PhotoSensor
{
  public:
    PhotoSensor(int PSpin, int PSthreshold);
    int getAnalog();
    int getDigital();
  private:
    int _PSpin;
    int _PSthreshold;
};

class Wheel
{
  public:
    Wheel(int Wpin, int WFF, int WFS, int WBF, int WBS);
    void setSpeed(int Wspeed);
    int getSpeed();
  private:
    int _Wpin;
    int _Wspeed;
    int _WFF;
	int _WFS;
	int _WBF;
	int _WBS;
};


#endif

