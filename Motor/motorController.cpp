//const int analogInPin = ; // Analog input pin that the potentiometer
                            // is attached to
//const int analogInPin2 = ;

const int pwmOutPin = 26;    // PWM pin that the LED is attached to
const int Ain2 = 22;
const int Ain1 = 21;
const int stby = 17;

const int pwmOutPin2 = 25; 
const int Bin2 =19;
const int Bin1 =20; 


// These variables will change:
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM


int sensorValue2 = 0;        // value read from the pot
int outputValue2 = 0;        // value output to the PWM

bool motor1=1, motor2=1;

void setup() {
    // Configure the ADC pin
   // pinMode(analogInPin, INPUT_ANALOG);
//    // Configure LED pin
//    pinMode(pwmOutPin, PWM);
  pinMode(pwmOutPin, PWM);
  pinMode(Ain2, OUTPUT);
  pinMode(Ain1, OUTPUT);
  pinMode(stby, OUTPUT);
 
  pinMode(pwmOutPin2, PWM); 
  pinMode(Bin2, OUTPUT);
  pinMode(Bin1, OUTPUT);
  
  digitalWrite(stby, HIGH); // stby

}

void loop() {
    // read the analog in value:
   // sensorValue = analogRead(analogInPin);
    //sensorValue2 = analogRead(analogInPin2);
//    // map it to the range of the analog out:
// digitalWrite(13, HIGH);
  
  //digitalWrite(stby2, HIGH);

 // outputValue = map(sensorValue, 0, 4095, 0, 65535);
  //outputValue2 = map(sensorValue2, 0, 4095, 0, 65535);
//    // change the analog out vaue:
    // int pwmValue = 80;
     // int outputValue = map(pwmValue, 0, 100, 0, 65535);
     outputValue = 600;
    pwmWrite(pwmOutPin, outputValue * 16);
   
   pwmWrite(pwmOutPin2, outputValue * 16);

}

void goStraight() {
  // motor1, motor2
  // Ain2 = HIGH => Forward
  // Ain2 = LOW => Backward
  digitalWrite(Ain2, );
  digitalWrite(Ain1, HIGH);
  

  // Bin2 = HIGH => Forward
  // Bin2 = LOW => Backward
  digitalWrite(Bin2, LOW);
  digitalWrite(Bin1, HIGH);
}

