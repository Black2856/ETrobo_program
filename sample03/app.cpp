#include "app.h" // <1>
#include "Tracer.h" // <2>
#include "Clock.h"  // <3>
using namespace ev3api;

Tracer tracer;  // <4>
Clock clock;    // <5>

//uint32_t dt = 0;

void tracer_task(intptr_t exinf) { // <1>
  //printf("%d, ",clock.now() - dt);
  //dt = clock.now();
  tracer.run(); // <2>
  ext_tsk();
}

void main_task(intptr_t unused) { // <1>
  const uint32_t duration = 100; // <2>
  tracer.init(); // <3>
  sta_cyc(TRACER_CYC); // <4>
  
  while (!ev3_button_is_pressed(LEFT_BUTTON)) { // <1>
      clock.sleep(duration);   // <2>
      if(ev3_button_is_pressed(RIGHT_BUTTON)){
      }
  }

  stp_cyc(TRACER_CYC); // <3>
  tracer.terminate(); // <4>
  ext_tsk(); // <5>
}

