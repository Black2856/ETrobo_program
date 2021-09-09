#include "Motor.h"
#include "ColorSensor.h"
#include "TouchSensor.h"
#include "util.h"
#include "Clock.h"

using namespace ev3api;

class RunningArea {
public:
  RunningArea();
  bool run();
  void init();
  void terminate();

  uint64_t blueTime(uint16_t threshold);
  float PID(int max,int r,float Kp,float Ki,float Kd);

private:
  rgb_raw_t rgb_val;
  Clock clock;
  Motor leftWheel;
  Motor rightWheel;

  ColorSensor colorSensor;
  TouchSensor touchSensor;

  int8_t pwm = 70;//速度
  float total = 0;
  int8_t et[2];
  int8_t curve = 0;
  int64_t blueClock = 0;

  bool endCheck = false;
  bool startCheck = false;
};
