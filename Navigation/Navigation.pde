#define leftMotor 5
#define rightMotor 6

void setup()
{
  pinMode( leftMotor, OUTPUT );
  pinMode( rightMotor, OUTPUT );
}

void turnLeft()
{
  digitalWrite( leftMotor, HIGH );
  digitalWrite( rightMotor, LOW );
}

void turnRight()
{
  digitalWrite( leftMotor, LOW );
  digitalWrite( rightMotor, HIGH );
}

void straight()
{
  digitalWrite( leftMotor, HIGH );
  digitalWrite( rightMotor, HIGH );
}

void motorControl(unsigned long leftSpeed, unsigned long rightSpeed )
{
  analogWrite( leftMotor, leftSpeed );
  analogWrite( rightMotor, rightSpeed );
}

void stop()
{
  digitalWrite( leftMotor, LOW );
  digitalWrite( rightMotor, LOW );
}

