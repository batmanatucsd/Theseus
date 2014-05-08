#include "pid.h"

/* Calculate the output using PD controller */
void pid_compute() {  

  /* proportional */
  float error =  input - setpoint;

  /* derivative */
  float derror = error - old_error;

  
  /* the output */
  output =  KP*error + KD*derror;

  /* save the error for future reference */
  old_error = error;

  // changes the speed of the motor
  // if(output > 50 || output < -50)
  if(ouput != 0) {
    if(speed != MAX) { 
      rs = speed + output;
      ls = speed - output;
    }
  }

  // motorControl(ls, rs);

}


/* initialize PID controller */
void pid_init() {
  old_error = 0;
}


/* set setpoint */
void set_setpoint(float point) {
  setpoint = point;
}
