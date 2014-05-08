#ifndef PID_H
#define PID_H

#define KP 1
#define KD 1

/* Function Declarations */
void pid_compute(); 
void pid_init();
void set_setpoint(float);

/* Working Variables */
float old_error;
float setpoint;
float input, output;

#endif
