#pragma once
#include "stdio.h"
#include "Clock.h"

using namespace ev3api;

class Status{//データ解析及び計測
public:
  void updateStatus();

  uint64_t getTime();

  uint64_t getPWMTime();
  void setPWMTime();

  uint64_t getSectionTime();
  void resetSection();

  uint8_t getRunningSection();
  void setRunningSection(uint8_t num);

private:
  Clock statusClock;
  uint8_t runningSection = 1;
  uint64_t resetSectionTime;//直近resetSection実行時の時間
  uint64_t PWMTime;
  uint64_t time;//経過時間
};
