#include "app.h"
#include "section.h"
#include "Clock.h" 

Section section;
Clock clock;
bool endcheck = false;

void tracer_task(intptr_t exinf) {
  endcheck = section.run();
  ext_tsk();
}

void main_task(intptr_t unused) {
  const uint32_t duration = 100;
  sta_cyc(TRACER_CYC);
  
  while (endcheck == false) {
      clock.sleep(duration);  
  }

  stp_cyc(TRACER_CYC);
  ext_tsk();
}

