#include "runningArea.h" // <1>
#include "stdio.h"
#include "complex"

RunningArea::RunningArea()://車輪ごとにポート割り当て
  leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_3), touchSensor(PORT_1) { // <2>
  }

void RunningArea::init() {
  init_f("RunningArea");
}

void RunningArea::terminate() {//停止処理
  msg_f("Stopped.", 1);
  leftWheel.stop();  // <1>
  rightWheel.stop();
}
//pwm 70 pid(1.44,0,0.32)
float RunningArea::PID(int max,int r,float Kp,float Ki,float Kd){//PID制御(最大値,目標値,P値,I値,D値)

  et[1] = et[0];
  et[0] = colorSensor.getBrightness() - r;//偏差
  total += (et[0] + et[1]) / 2 * 0.05;

  const float P = Kp * et[0];
  const float I = Ki * total;
  const float D = Kd * (et[0] - et[1]) / 0.05;
  //printf("%f,%f,%f■",P,I,D);

  float ret = P + I + D;
  if(-max > ret){//retの範囲を -max <= ret <= max にする 
    ret = -max;
  }else if(max < ret){
    ret = max;
  }
  return P + I + D;
}

uint64_t RunningArea::blueTime(uint16_t threshold){//青ライン判定している間の時間を返す (ms)
  int64_t ret = 0;
  if((rgb_val.b-rgb_val.r) > threshold){
    ret = clock.now()/1000 - blueClock;
  }else{
    blueClock = clock.now()/1000;
  }
  return ret;
}

bool RunningArea::run() {//ライントレースのメイン処理
  colorSensor.getRawColor(rgb_val);

  if(startCheck == true){
    if(clock.now()/1000 < 1000){
      curve = PID(pwm,22,0.9,0,0.20);
      pwm = 35;
    }else{
      curve = PID(pwm,22,1.44,0,0.32);
      pwm = 70;
    }
    if(blueTime(50) > 300){//青ライン踏んだら終了
      endCheck = true;
    }
  }else{
    if(touchSensor.isPressed() == true){
      startCheck = true;
      clock.reset();
    }
    pwm = 0;
  }

  leftWheel.setPWM((pwm) - curve);//pwmからPID処理で算出したカーブ量を減算
  rightWheel.setPWM((pwm) + curve);//pwmからPID処理で算出したカーブ量を加算
  curve = 0;

  return endCheck;
}
