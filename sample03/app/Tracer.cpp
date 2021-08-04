#include "Tracer.h" // <1>
#include "stdio.h"
#include "complex"

Tracer::Tracer()://車輪ごとにポート割り当て?
  leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_3) { // <2>
  }

void Tracer::init() {
  init_f("Tracer");
}

void Tracer::reset(){//Ｉ制御の合計のリセット
  total = 0;
  printf("------リセット------\n");
}

void Tracer::terminate() {//停止処理?
  msg_f("Stopped.", 1);
  leftWheel.stop();  // <1>
  rightWheel.stop();
}
//pwm 70 pid(1.44,0,0.32)
float Tracer::PID(int max,int r,float Kp,float Ki,float Kd){//PID制御(最大値,目標値,P値,I値,D値)

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

void Tracer::run() {//ライントレースのメイン処理
  msg_f("running...", 1);

  curve = PID(pwm,22,1.44,0,0.32);
  leftWheel.setPWM((pwm) - curve);//pwmからPID処理で算出したカーブ量を減算
  rightWheel.setPWM((pwm) + curve);//pwmからPID処理で算出したカーブ量を加算

  //printf("%o,",colorSensor.getBrightness()); //明るさ表示用 暗 0~50 明

/*
  if(colorSensor.getBrightness() >= mThreshold) { // <1>
    leftWheel.setPWM(0);
    rightWheel.setPWM(pwm);
  } else {   // <2>
    leftWheel.setPWM(pwm);
    rightWheel.setPWM(0);
    
  }
*/
}
