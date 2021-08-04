#include "Motor.h"       // <1>
#include "ColorSensor.h" // <2>
#include "util.h"        // <3>

using namespace ev3api;  // <4>

class Tracer {  // <1>
public:
  Tracer();
  void run();       // <2>
  void init();
  void terminate();

  float PID(int max,int r,float Kp,float Ki,float Kd);
  void reset();

private:
  Motor leftWheel;
  Motor rightWheel;
  ColorSensor colorSensor; // <3>
  const int8_t pwm = 70;//速度
  float total = 0;
  int8_t et[2];
  int8_t curve = 0;
};
