#pragma once
#include "stdio.h"
#include "util.h"

#include "control.h"
#include "status.h"

class Section01{
public:
  Section01(Status* pt1,Control* pt2);
  void entry();
  void running();
  void condition();
private:
  bool sectionEntry = false;
  const uint8_t section = 1;
  Status *pStatus;
  Control *pControl;
};

class Section10{
public:
  Section10(Status* pt1,Control* pt2);
  void entry();
  void running();
  void condition();

private:
  bool sectionEntry = false;
  const uint8_t section = 10;
  Status *pStatus;
  Control *pControl;
};

class Section11{
public:
  Section11(Status* pt1,Control* pt2);
  void entry();
  void running();
  void condition();

private:
  bool sectionEntry = false;
  const uint8_t section = 11;
  Status *pStatus;
  Control *pControl;
};

class Section12{
public:
  Section12(Status* pt1,Control* pt2);
  void entry();
  void running();
  void condition();

private:
  bool sectionEntry = false;
  const uint8_t section = 12;
  Status *pStatus;
  Control *pControl;
};

class Section13{
public:
  Section13(Status* pt1,Control* pt2);
  void entry();
  void running();
  void condition();

private:
  bool sectionEntry = false;
  const uint8_t section = 13;
  Status *pStatus;
  Control *pControl;
};

class Section14{
public:
  Section14(Status* pt1,Control* pt2);
  void entry();
  void running();
  void condition();

private:
  bool sectionEntry = false;
  const uint8_t section = 14;
  Status *pStatus;
  Control *pControl;
};

class Section15{
public:
  Section15(Status* pt1,Control* pt2);
  void entry();
  void running();
  void condition();

private:
  bool sectionEntry = false;
  const uint8_t section = 15;
  Status *pStatus;
  Control *pControl;
};

class Section16{
public:
  Section16(Status* pt1,Control* pt2);
  void entry();
  void running();
  void condition();

private:
  bool sectionEntry = false;
  const uint8_t section = 16;
  Status *pStatus;
  Control *pControl;

  uint64_t blueClock = 0;
};

class Section{//区画制御のメイン
public:
  bool run();
  void sectionRun();//sectionのrunning()を実行

private:
  bool endcheck = false;//runningSectionが0の場合true

  Status *status = new Status();
  Control *control = new Control(status);

  Section01 *section01 = new Section01(status,control);
  Section10 *section10 = new Section10(status,control);
  Section11 *section11 = new Section11(status,control);
  Section12 *section12 = new Section12(status,control);
  Section13 *section13 = new Section13(status,control);
  Section14 *section14 = new Section14(status,control);
  Section15 *section15 = new Section15(status,control);
  Section16 *section16 = new Section16(status,control);
};