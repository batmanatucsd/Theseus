#ifndef PID_H
#define PID_H

#include "header.h"

const int sensorR = 6;
const int sensorRM = 7;
const int sensorM = 8;
const int sensorLM = 9;
const int sensorL = 10; // the piezo is connected to analog pin 0
//const int threshold = 100;  // threshold value to decide when the detected sound is a knock or not

// these variables will change:
int sensorReadingR = 0;      // variable to store the value read from the sensor pin
int sensorReadingRM = 0;
int sensorReadingM = 0;
int sensorReadingLM = 0;
int sensorReadingL = 0;


int runOnce =0;
int DC =25;
float dutyCycle = 4095*DC/100.0;
int errorP = 0;
int errorD = 0;
int oldErrorP =0;
float totalError = 0;
float P = 0.02;
float D = 0.05;

 float dutyCycleL = dutyCycle;
  float dutyCycleR = dutyCycle;
//float dutyCycleR = 4095*30/100.0;

#define hasLeftWall 400
#define hasRightWall 500

#define stby 17
#define MOTOR_A 26    // motor A
#define Ain2 22
#define Ain1 21

#define MOTOR_B 25 // motor B
#define Bin2 19
#define Bin1 20 



void readSensors() {
    // Declare the knockSensor as an analog input:
    pinMode(sensorR, INPUT_ANALOG);
    pinMode(sensorRM, INPUT_ANALOG);
    pinMode(sensorM, INPUT_ANALOG);
    pinMode(sensorLM, INPUT_ANALOG);
    pinMode(sensorL, INPUT_ANALOG);
    
    
    
    pinMode(MOTOR_A, PWM);
    pinMode(Ain2, OUTPUT);
    pinMode(Ain1, OUTPUT);
    pinMode(stby, OUTPUT);
 
    pinMode(MOTOR_B, PWM); 
    pinMode(Bin2, OUTPUT);
    pinMode(Bin1, OUTPUT);
  
    digitalWrite(stby, HIGH); // stby  
    // declare the built-in LED pin as an output:
//    pinMode(BOARD_LED_PIN, OUTPUT);
}

void testPID() {
    // read the sensor and store it in the variable sensorReading:
    
    sensorReadingR = 4095 - analogRead(sensorR);
    sensorReadingRM = 4095 - analogRead(sensorRM);
    sensorReadingM = 4095 - analogRead(sensorM);
    sensorReadingLM = 4095 - analogRead(sensorLM);
    sensorReadingL = 4095 - analogRead(sensorL);
    

    
    SerialUSB.print(sensorReadingL);
    SerialUSB.print("  ");
    SerialUSB.print(sensorReadingLM);
    SerialUSB.print("  ");
    SerialUSB.print(sensorReadingM);
    SerialUSB.print("  ");
    SerialUSB.print(sensorReadingRM);
    SerialUSB.print("  ");
    SerialUSB.print(sensorReadingR);
    SerialUSB.print("             ");

    SerialUSB.print(sensorReadingR - sensorReadingL - 1380);
    SerialUSB.println();

	 setSpeed(dutyCycle, dutyCycle);
	 dutyCycleL = dutyCycle;
	 dutyCycleR = dutyCycle;

   straight();
    PID();

    delay(100);  // delay to avoid printing too often
}


void PID()       
{    
  
    if((sensorReadingL > hasLeftWall) && (sensorReadingR > hasRightWall))//has both walls
    {  //ccw direction is positive
        SerialUSB.print("  i'm here1  ");
        // When theres two walls
        errorP = sensorReadingR - sensorReadingL - 1380; //1380 is the offset between left and right sensor when mouse in the middle of cell
        
        // when angled more to right
//        if(sensorReadingRM > 3800 && sensorReadingL < 400) {
//          breakLeft();
//        }
//        
//        // when angled more to left        
//        if(sensorReadingLM > 3800 && sensorReadingR < 800) {
//          breakRight();
//        }

    }        
    else if((sensorReadingL > hasLeftWall) && !(sensorReadingR > hasRightWall))//only has left wall
    {
        // When theres left wall
        SerialUSB.print("  i'm here2  ");
        errorP = (2 * (sensorReadingLM - sensorReadingL))+690;

    }
    else if(!(sensorReadingL > hasLeftWall) && (sensorReadingR > hasRightWall))//only has right wall
    {
      // When theres right wall
              SerialUSB.print("  i'm here3  ");
        errorP = (2 * (sensorReadingRM - sensorReadingR))+2720; //1650

    }
    else if((sensorReadingL < hasLeftWall) && (sensorReadingR <hasRightWall))//no wall, use encoder or gyro
    {
         // When theres no wall
         SerialUSB.print("  i'm here4  ");
         return;
    }
    
    
    if(errorP > 100)
      errorP *= 2.2;
    
    errorD = errorP - oldErrorP;
    
    //this will get the speed for the given duty cycle
    totalError = P * errorP + D * errorD;
    oldErrorP = errorP;
    
//    SerialUSB.print(totalError);
//    SerialUSB.println("Error:  ");

    
     dutyCycleL -= totalError;
     dutyCycleR += totalError;
     
   SerialUSB.print("DutyCycle  ");
    SerialUSB.print(dutyCycleL);
    SerialUSB.print("  " );
    SerialUSB.print(dutyCycleR);
     SerialUSB.print("  " );
    SerialUSB.print(totalError);    
         SerialUSB.print("  " );
    SerialUSB.print(errorP);    
         SerialUSB.print("  " );
    SerialUSB.print(errorD);    
     SerialUSB.print("        " );
     
     SerialUSB.print("  " );
     
     
      
     setSpeed(dutyCycleL, dutyCycleR); 
         delay(25); 
   // setLeftPwm(leftBaseSpeed – totalError);
    //setRightPwm(rightBaseSpeed + totalError);    
    
    //adjust the duty cycles
//    if(totalError < -100)
//    {
//      // setSpeed(4095*(DC+1)/100,4095*(DC-1)/100);
//      
//      
//      dutyCycleL -= totalError;
//      dutyCycleR += totalError;
//      
//      setSpeed(dutyCycleL, dutyCycleR);
// // SerialUSB.print(dutyCycleL);
//   // SerialUSB.print("L:  ");
//  
// 
//    
//    }
//    else if(totalError > 100)
//    {
//       //setSpeed(4095*(DC-1)/100, 4095*(DC+1)/100);
//       
//      dutyCycleL -= totalError;
//      dutyCycleR += totalError;
//      
//      setSpeed(dutyCycle,dutyCycleR);
// // SerialUSB.print(dutyCycleR);
//  //  SerialUSB.println("R:  ");
//       
//      
//      
//    }
//    
//    else
//    {
//       setSpeed(dutyCycle, dutyCycle);
//        
//    }
        
}


// Ain2 = HIGH => Forward
// Ain2 = LOW => Backward
// Bin2 = HIGH => Forward
// Bin2 = LOW => Backward

void turnLeft() {
  // reset encoder tick count
  digitalWrite(Ain2, LOW); // A moves backwards or should break
  digitalWrite(Ain1, HIGH);
  digitalWrite(Bin2, HIGH); // B moves forwards
  digitalWrite(Bin1, LOW);
  // stop motors after certain ticks from encoders
}

void turnRight() {
  digitalWrite(Ain2, HIGH); // A moves forwards
  digitalWrite(Ain1, LOW);
  digitalWrite(Bin2, LOW); // B moves backwards or should break
  digitalWrite(Bin1, HIGH);
  // stop motors after certain ticks from encoders
}

void turn180() {
  // reset encoder tick count
  digitalWrite(Ain2, HIGH); // A moves forwards
  digitalWrite(Ain1, LOW);
  digitalWrite(Bin2, LOW); // B moves backwards or should break
  digitalWrite(Bin1, HIGH);
  // stop motors after certain ticks from encoders
}

void straight() {
  digitalWrite(Ain2, HIGH); // A forwards
  digitalWrite(Ain1, LOW);
  digitalWrite(Bin2, HIGH); // B forwards
  digitalWrite(Bin1, LOW); 
}  

void stop() {
  breakLeft();
  breakRight();
}

void breakLeft() {
  digitalWrite(Ain2, HIGH); // A breaks
  digitalWrite(Ain1, HIGH);
}

void breakRight() {
  digitalWrite(Bin2, HIGH); // B break
  digitalWrite(Bin1, HIGH);
}

void setSpeed(unsigned int leftSpeed, unsigned int rightSpeed ) {
//   pwmWrite(MOTOR_A, 4095 * 16 * leftSpeed/100);
//   pwmWrite(MOTOR_B, 4095*16*rightSpeed/100);
   pwmWrite(MOTOR_A, 16 * leftSpeed);
   pwmWrite(MOTOR_B, 16 * rightSpeed);
   
}

// reset Encoder counts function
// void resetEncoder();

#endif // PID_H
