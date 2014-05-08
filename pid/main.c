#include <stdio.h>
#include "pid.h"  

  /* In this program, you will insert the sensor inputs
   * but in the real program, there will be a function
   * for reading sensor inputs: readsensors();
   * 
   * We have a choice of reading inputs in pid function
   * or do it separately. I say we do it separately
   * so that we can use that information somewhere else
   * in the program. 
   * 
   * Let us(the software team) know what everyone thinks 
   * about this so we can change the code accordingly.
   * 
   * In this program, the setpoint is set to 5
   * so output changes accordingly.
   * The proportional and derivative gain is set to 1
   */

int main() {

  /* set setpoint
   * set arbitrarily to 5
   */ 
  set_setpoint(5);

  /* initializes pid */
  pid_init();

  /* read sensors */
  printf("Insert sensor input: ");

  while(scanf("%f", &input)) {
    /* call pid 
     * compute the errors
     * and give resulting output
     */
    pid_compute();

    /* print out the results */
    printf("  input is:  %5.2f\n", input); 
    printf("  output is: %5.2f\n", output); 

    printf("Insert sensor input: ");
  }

  printf("The program is exiting\n");
  return 0;
}
