#include "Tracer.h" // <1>
#include "stdio.h"
#include "complex"

Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_3) { // <2>
  }

void Tracer::init() {
  init_f("Tracer");
}

void Tracer::reset(){
  total = 0;
  printf("------リセット------\n");
}

void Tracer::set_turn(int8_t T){
  turn = T;
}

void Tracer::terminate() {
  msg_f("Stopped.", 1);
  leftWheel.stop();  // <1>
  rightWheel.stop();
}
//pwm 70 pid(1.24,0,0.32)
float Tracer::PID(int max,int r,float Kp,float Ki,float Kd){//PID制御

  et[1] = et[0];
  et[0] = colorSensor.getBrightness() - r;//偏差
  total += (et[0] + et[1]) / 2 * 0.05;

  const float P = Kp * et[0];
  const float I = Ki * total;
  const float D = Kd * (et[0] - et[1]) / 0.05;
  //printf("%f,%f,%f■",P,I,D);

  float ret = P + I + D;
  if(-max > ret){
    ret = -max;
  }else if(max < ret){
    ret = max;
  }
  return P + I + D;
}

void Tracer::run() {
  msg_f("running...", 1);

  //printf("%o,",colorSensor.getBrightness()); //明るさ表示用 暗 0~50 明
if(turn == 0){//走行状態
  curve = PID(pwm,22,1.24,0,0.32);
  leftWheel.setPWM((pwm) - curve);
  rightWheel.setPWM((pwm) + curve);
}else{//回転状態
  if(turn > 1){//
    curve = 40;
    turn--;
  }else{
    curve = PID(20,6,2,0,0.3);
    if(4 > colorSensor.getBrightness()){
      turn = 0;
    }
  }
  leftWheel.setPWM(-curve);
  rightWheel.setPWM(curve);
}

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
