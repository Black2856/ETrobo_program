#include "app.h"
#include "runningArea.h"
#include "Clock.h"
using namespace ev3api;

RunningArea runningArea;
Clock clock;
bool endCheck = false;

void tracer_task(intptr_t exinf) {
  endCheck = runningArea.run();
  ext_tsk();
}

void main_task(intptr_t unused) {
  const uint32_t duration = 100;
  runningArea.init();
  sta_cyc(TRACER_CYC);
  
  while (endCheck == false) {
      clock.sleep(duration);
  }

  stp_cyc(TRACER_CYC);
  runningArea.terminate();

  ext_tsk();
}

