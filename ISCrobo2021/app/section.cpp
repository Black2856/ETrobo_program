#include "section.h"
#include "stdio.h"
#include "complex"

///////////////////////////////////////////////////////////

bool Section::run(){

  sectionRun();
  status->updateStatus();
  control->updateControl();

  if(status->getRunningSection() == 0){
    endcheck = true;
    control->terminate();
  }
  return endcheck;
}

void Section::sectionRun(){
  switch(status->getRunningSection()){
    case 1:
      section01->running();
      break;
    case 10:
      section10->running();
      break;
    case 11:
      section11->running();
      break;
    case 12:
      section12->running();
      break;
    case 13:
      section13->running();
      break;
    case 14:
      section14->running();
      break;
    case 15:
      section15->running();
      break;
    case 16:
      section16->running();
      break;
  }
}

///////////////////////////////////////////////////////////
Section01::Section01(Status* pt1,Control* pt2){
  pStatus = pt1;
  pControl = pt2;
}
void Section01::entry(){//エントリーしたら sectionEntry = true
  //printf("section01に遷移\n");
  sectionEntry = true;
}
void Section01::running(){
  if(sectionEntry == false){//区画切り替え時の処理 entry();
    entry();
  }
  condition();
}
void Section01::condition(){//区画から外れる場合必ずsectionEntry = false
  if(pControl->TS.isPressed() == true){
    pStatus->resetSection();
    pStatus->setRunningSection(10);
    sectionEntry = false;
  }
}

///////////////////////////////////////////////////////////

Section10::Section10(Status* pt1,Control* pt2){
  pStatus = pt1;
  pControl = pt2;
}
void Section10::entry(){
    //printf("section10に遷移\n");
    pControl->setPWM(35,35,1);
    sectionEntry = true;
}
void Section10::running(){
  if(sectionEntry == false){//区画切り替え時の処理 entry();
    entry();
  }
  pControl->setPWM(100,100,1000);
  if(pStatus->getSectionTime() > 400){
    pControl->PID(22,1.44,0,0.32);
  }
  condition();
}
void Section10::condition(){
  if(pStatus->getSectionTime() > 4400){
    pStatus->resetSection();
    pStatus->setRunningSection(11);
    sectionEntry = false;
  }
}

///////////////////////////////////////////////////////////

Section11::Section11(Status* pt1,Control* pt2){
  pStatus = pt1;
  pControl = pt2;
}
void Section11::entry(){
  //printf("section11に遷移\n");
  sectionEntry = true;
}
void Section11::running(){
  if(sectionEntry == false){//区画切り替え時の処理 entry();
    entry();
  }
  pControl->setPWM(70,70,500);
  pControl->PID(22,1.44,0,0.32);
  condition();
}
void Section11::condition(){
  if(pStatus->getSectionTime() > 3000){
    pStatus->resetSection();
    pStatus->setRunningSection(12);
    sectionEntry = false;
  }
}

///////////////////////////////////////////////////////////

Section12::Section12(Status* pt1,Control* pt2){
  pStatus = pt1;
  pControl = pt2;
}
void Section12::entry(){
  //printf("section12に遷移\n");
  sectionEntry = true;
}
void Section12::running(){
  if(sectionEntry == false){//区画切り替え時の処理 entry();
    entry();
  }
  pControl->setPWM(100,100,500);
  pControl->PID(22,1.44,0,0.32);
  condition();
}
void Section12::condition(){
  if(pStatus->getSectionTime() > 1100){
    pStatus->resetSection();
    pStatus->setRunningSection(13);
    sectionEntry = false;
  }
}

///////////////////////////////////////////////////////////

Section13::Section13(Status* pt1,Control* pt2){
  pStatus = pt1;
  pControl = pt2;
}
void Section13::entry(){
  //printf("section13に遷移\n");
  sectionEntry = true;
}
void Section13::running(){
  if(sectionEntry == false){//区画切り替え時の処理 entry();
    entry();
  }
  pControl->setPWM(65,65,500);
  pControl->PID(22,1.44,0,0.32);
  condition();
}
void Section13::condition(){
  if(pStatus->getSectionTime() > 2400){
    pStatus->resetSection();
    pStatus->setRunningSection(14);
    sectionEntry = false;
  }
}

///////////////////////////////////////////////////////////

Section14::Section14(Status* pt1,Control* pt2){
  pStatus = pt1;
  pControl = pt2;
}
void Section14::entry(){
  //printf("section14に遷移\n");
  sectionEntry = true;
}
void Section14::running(){
  if(sectionEntry == false){//区画切り替え時の処理 entry();
    entry();
  }
  pControl->setPWM(100,100,500);
  pControl->PID(22,1.44,0,0.32);
  condition();
}
void Section14::condition(){
  if(pStatus->getSectionTime() > 3300){
    pStatus->resetSection();
    pStatus->setRunningSection(15);
    sectionEntry = false;
  }
}

///////////////////////////////////////////////////////////

Section15::Section15(Status* pt1,Control* pt2){
  pStatus = pt1;
  pControl = pt2;
}
void Section15::entry(){
  //printf("section15に遷移\n");
  sectionEntry = true;
}
void Section15::running(){
  if(sectionEntry == false){//区画切り替え時の処理 entry();
    entry();
  }
  pControl->setPWM(65,65,500);
  pControl->PID(22,1.44,0,0.32);
  condition();
}
void Section15::condition(){
  if(pStatus->getSectionTime() > 1800){
    pStatus->resetSection();
    pStatus->setRunningSection(16);
    sectionEntry = false;
  }
}

///////////////////////////////////////////////////////////

Section16::Section16(Status* pt1,Control* pt2){
  pStatus = pt1;
  pControl = pt2;
}
void Section16::entry(){
  //printf("section16に遷移\n");
  sectionEntry = true;
}
void Section16::running(){
  if(sectionEntry == false){//区画切り替え時の処理 entry();
    entry();
  }
  pControl->setPWM(100,100,500);
  pControl->PID(22,1.44,0,0.32);
  condition();
}
void Section16::condition(){
  if(pStatus->getSectionTime() > 3000){
    pControl->setPWM(0,0,1200);
    pStatus->resetSection();
    pStatus->setRunningSection(0);
    sectionEntry = false;
  }
}