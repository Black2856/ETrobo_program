#include "status.h"

///////////////////////////////////////////////////////////

void Status::updateStatus(){//計測 毎回行う
  time = statusClock.now()/1000;
}

///////////////////////////////////////////////////////////

uint64_t Status::getTime(){
  return time;
}

///////////////////////////////////////////////////////////

void Status::setPWMTime(){
  PWMTime = time;
}
uint64_t Status::getPWMTime(){
  return time - PWMTime;
}

///////////////////////////////////////////////////////////

void Status::resetSection(){//区画切り替え時の初期化処理
  resetSectionTime = time;
}
uint64_t Status::getSectionTime(){
  return time - resetSectionTime;
}

///////////////////////////////////////////////////////////

void Status::setRunningSection(uint8_t num){
  runningSection = num;
}
uint8_t Status::getRunningSection(){
  return runningSection;
}

///////////////////////////////////////////////////////////
