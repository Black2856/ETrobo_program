#include "control.h"

using namespace ev3api;

///////////////////////////////////////////////////////////

Control::Control(Status* pt1):
    leftWheel(PORT_C), rightWheel(PORT_B), CS(PORT_1), GS(PORT_2), TS(PORT_3){
    pStatus = pt1;
}

void Control::updateControl(){//常時動かす
    float ratio = (float)pStatus->getPWMTime() / (float)transition;
    if( ratio > 1 ){
        ratio = 1;
    }
    leftPWM = tempLeftPWM + vectorLeftPWM * ratio;
    rightPWM = tempRightPWM + vectorRightPWM * ratio;

    leftWheel.setPWM(leftPWM - curve);
    rightWheel.setPWM(rightPWM + curve);
    curve = 0;
}

void Control::terminate(){
  leftWheel.stop();
  rightWheel.stop();
}

void Control::setPWM(int left,int right, uint64_t tran){//車輪の出力量をセット transition(ms)かけて近づける
    if((purposeLeftPWM != left) || (purposeRightPWM != right) || (tran != transition)){
        vectorLeftPWM = left - leftPWM;
        vectorRightPWM = right - rightPWM;
        tempLeftPWM = leftPWM;
        tempRightPWM = rightPWM;
        purposeLeftPWM = left;
        purposeRightPWM = right;
        transition = tran;
        pStatus->setPWMTime();
    }
}

float Control::PID(int r,float Kp,float Ki,float Kd){//PID制御(目標値,P値,I値,D値) PWM値は原則左右同じであること
  int max = (leftPWM + rightPWM)/2;

  et[1] = et[0];
  et[0] = CS.getBrightness() - r;//偏差
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
  curve = P + I + D;
  return curve;
}

void Control::getColor(){
    CS.getRawColor(rgb_val);
}