/*
  Knock Sensor

  This sketch reads a piezo element to detect a knocking sound.  It
  reads an analog pin and compares the result to a set threshold.  If
  the result is greater than the threshold, it writes "knock" to the
  serial port, and toggles the LED on pin 13.

  The circuit:
  * + connection of the piezo attached to analog in 0
  * - connection of the piezo attached to ground
  * 1-megohm resistor attached from analog in 0 to ground

  http://www.arduino.cc/en/Tutorial/Knock

  created 25 Mar 2007
  by David Cuartielles <http://www.0j0.org>
  modified 30 Jun 2009
  by Tom Igoe

  Ported to the Maple
  by LeafLabs
*/

// these constants won't change:
const int sensorR = 5;
//const int sensorR = 6;
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

void setup() {
    // Declare the knockSensor as an analog input:
    pinMode(sensorR, INPUT_ANALOG);
    pinMode(sensorRM, INPUT_ANALOG);
    pinMode(sensorM, INPUT_ANALOG);
    pinMode(sensorLM, INPUT_ANALOG);
    pinMode(sensorL, INPUT_ANALOG);
      
    // declare the built-in LED pin as an output:
//    pinMode(BOARD_LED_PIN, OUTPUT);
}

void loop() {
    // read the sensor and store it in the variable sensorReading:
    
    sensorReadingR = 4095 - analogRead(sensorR);
    sensorReadingRM = 4095 - analogRead(sensorRM);
    sensorReadingM = 4095 - analogRead(sensorM);
    sensorReadingLM = 4095 - analogRead(sensorLM);
    sensorReadingL = 4095 - analogRead(sensorL);
    
//    sensorReading = 4095 - sensorReading;
    
    SerialUSB.print(sensorReadingL);
    SerialUSB.print("  ");
    SerialUSB.print(sensorReadingLM);
    SerialUSB.print("  ");
    SerialUSB.print(sensorReadingM);
    SerialUSB.print("  ");
    SerialUSB.print(sensorReadingRM);
    SerialUSB.print("  ");
    SerialUSB.print(sensorReadingR);
    SerialUSB.println();
    
   // if the sensor reading is greater than the threshold:
//    if (sensorReading >= threshold) {
//        // toggle the built-in LED
//        toggleLED();
//        // send the string "Knock!" back to the computer, followed by newline
//        SerialUSB.println("Knock!");
//    }
    delay(500);  // delay to avoid printing too often
}
