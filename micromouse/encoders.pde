int motorA_count, motorA_A_SIG=0, motorA_B_SIG=1;
int motorB_count, motorB_A_SIG=0, motorB_B_SIG=1;

#define motorA_encoderA 2
#define motorA_encoderB 3
#define motorB_encoderA 12
#define motorB_encoderB 13

void attachInterrupts(){
  attachInterrupt(motorA_encoderA, motorA_A_RISE, RISING);
  attachInterrupt(motorA_encoderB, motorA_B_RISE, RISING);
  
  attachInterrupt(motorB_encoderA, motorB_A_RISE, RISING);
  attachInterrupt(motorB_encoderB, motorB_B_RISE, RISING);
}//setup

void printEncoderTicks() {
  
 SerialUSB.print("Encoder Counts: ");
 SerialUSB.print(motorA_count);
 
   SerialUSB.print("  ");
  SerialUSB.print(motorB_count);
     SerialUSB.print("     ");
  

  delay(500);
}

void resetMotorCounts() {
  if(motorA_count >= 3768)
    motorA_count = 0;  
  
  if(motorB_count >= 3768)
    motorB_count = 0;
    
  if(motorA_count <= -3768)
    motorA_count = 0;  
  
  if(motorB_count <= -3768)
    motorB_count = 0;
}

void motorA_A_RISE(){
 detachInterrupt(motorA_encoderA);

 motorA_A_SIG=1;


 if(motorA_B_SIG==0)
 motorA_count++;//moving forward
 if(motorA_B_SIG==1)
 motorA_count--;//moving reverse

 attachInterrupt(motorA_encoderA, motorA_A_FALL, FALLING);
  resetMotorCounts();
}

void motorA_A_FALL(){
 detachInterrupt(motorA_encoderA);

  motorA_A_SIG=0;

 
 if(motorA_B_SIG==1)
 motorA_count++;//moving forward
 if(motorA_B_SIG==0)
 motorA_count--;//moving reverse

 attachInterrupt(motorA_encoderA, motorA_A_RISE, RISING);
  resetMotorCounts();
}

void motorA_B_RISE(){
 detachInterrupt(motorA_encoderB);

  motorA_B_SIG=1;

 
 if(motorA_A_SIG==1)
 motorA_count++;//moving forward
 if(motorA_A_SIG==0)
 motorA_count--;//moving reverse
  
 attachInterrupt(motorA_encoderB, motorA_B_FALL, FALLING);
  resetMotorCounts();
}

void motorA_B_FALL(){
 detachInterrupt(motorA_encoderB);

  motorA_B_SIG=0;

 
 if(motorA_A_SIG==0)
 motorA_count++;//moving forward
 if(motorA_A_SIG==1)
 motorA_count--;//moving reverse
 
 attachInterrupt(motorA_encoderB, motorA_B_RISE, RISING);
  resetMotorCounts();
}


void motorB_A_RISE(){
 detachInterrupt(motorB_encoderA);
 motorB_A_SIG=1; 
 
 if(motorB_B_SIG==0)
 motorB_count++;//moving forward
 if(motorB_B_SIG==1)
 motorB_count--;//moving reverse

   attachInterrupt(motorB_encoderA, motorB_A_FALL, FALLING);
     resetMotorCounts();
}

void motorB_A_FALL(){
 detachInterrupt(motorB_encoderA);
   motorB_A_SIG=0;

    if(motorB_B_SIG==1)
 motorB_count++;//moving forward
 if(motorB_B_SIG==0)
 motorB_count--;//moving reverse

  attachInterrupt(motorB_encoderA, motorB_A_RISE, RISING); 
  resetMotorCounts();
}

void motorB_B_RISE(){
 detachInterrupt(motorB_encoderB);
motorB_B_SIG=1;

 if(motorB_A_SIG==1)
 motorB_count++;//moving forward
 if(motorB_A_SIG==0)
 motorB_count--;//moving reverse

  attachInterrupt(motorB_encoderB, motorB_B_FALL, FALLING);
    resetMotorCounts();
}

void motorB_B_FALL(){
 detachInterrupt(motorB_encoderB);
motorB_B_SIG=0;

 if(motorB_A_SIG==0)
 motorB_count++;//moving forward
 if(motorB_A_SIG==1)
 motorB_count--;//moving reverse
  
 attachInterrupt(motorB_encoderB, motorB_B_RISE, RISING); 
  resetMotorCounts();
}












