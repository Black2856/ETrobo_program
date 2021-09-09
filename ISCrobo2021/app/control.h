#pragma once
#include "stdio.h"

#include "util.h"
#include "Motor.h"
#include "ColorSensor.h"
#include "GyroSensor.h"
#include "TouchSensor.h"

#include "status.h"

using namespace ev3api;

class Control{//走行体制御のクラス
public:
    Control(Status* pt1);
    void updateControl();
    void terminate();
    void setPWM(int left,int right, uint64_t tran);// tran(ms)で目的のPWMに調整する
    float PID(int r,float Kp,float Ki,float Kd);//PID制御
    void getColor();

    Motor leftWheel;
    Motor rightWheel;
    ColorSensor CS;
    GyroSensor GS;
    TouchSensor TS;
    rgb_raw_t rgb_val;

private:
    Status *pStatus;
    int vectorLeftPWM = 0;//変化量
    int vectorRightPWM = 0;//変化量
    int tempLeftPWM = 0;//一時保存PWM
    int tempRightPWM = 0;//一時保存PWM
    int leftPWM = 0;//現在PWM
    int rightPWM = 0;//現在PWM
    int purposeLeftPWM = 0;
    int purposeRightPWM = 0;
    uint64_t transition = 1;

    int8_t curve = 0;//PID
    float total = 0;//PID
    int8_t et[2];//PID
};