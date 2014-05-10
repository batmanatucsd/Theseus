

#define stby 17
#define MOTOR_A 26    // motor A
#define Ain2 22
#define Ain1 21

#define MOTOR_B 25 // motor B
#define Bin2 19
#define Bin1 20 

void setup() {
  pinMode(MOTOR_A, PWM);
  pinMode(Ain2, OUTPUT);
  pinMode(Ain1, OUTPUT);
  pinMode(stby, OUTPUT);
 
  pinMode(MOTOR_B, PWM); 
  pinMode(Bin2, OUTPUT);
  pinMode(Bin1, OUTPUT);
  
  digitalWrite(stby, HIGH); // stby
}

void loop() {
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
  digitalWrite(Ain2, HIGH); // A breaks
  digitalWrite(Ain1, HIGH);
  digitalWrite(Bin2, HIGH); // B break
  digitalWrite(Bin1, HIGH);
}

void setSpeed(unsigned char leftSpeed, unsigned char rightSpeed ) {
   pwmWrite(MOTOR_A, 4095 * 16 * leftSpeed/100);
   pwmWrite(MOTOR_B, 4095*16*rightSpeed/100);
}

// reset Encoder counts function
// void resetEncoder();
