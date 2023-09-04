//Libraries
#include <Wire.h>                     //https://www.arduino.cc/en/reference/wire
#include <Adafruit_PWMServoDriver.h>  //https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
#include "I2C_SCANNER.h"

I2C_SCANNER scanner;

//Objects
Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);

void setup() {
  //Init Serial USB
  Serial.begin(9600);

  while (!isI2Cconnected()) {}
  Serial.println("PCA9685 connect successful");
  pca.begin();
  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't
   * that precise. You can 'calibrate' this by tweaking this number until
   * you get the PWM update frequency you're expecting!
   * The int.osc. for the PCA9685 chip is a range between about 23-27MHz and
   * is used for calculating things like writeMicroseconds()
   * Analog servos run at ~50 Hz updates, It is importaint to use an
   * oscilloscope in setting the int.osc frequency for the I2C PCA9685 chip.
   * 1) Attach the oscilloscope to one of the PWM signal pins and ground on
   *    the I2C PCA9685 chip you are setting the value for.
   * 2) Adjust setOscillatorFrequency() until the PWM update frequency is the
   *    expected value (50Hz for most ESCs)
   * Setting the value here is specific to each individual I2C PCA9685 chip and
   * affects the calculations for the PWM update frequency. 
   * Failure to correctly set the int.osc value will cause unexpected PWM results
   */
  pca.setOscillatorFrequency(27000000);
  // pca.setPWMFreq(1600);  // This is the maximum PWM frequency
  pca.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  // Wire.setClock(400000);
}


int ang = 0;
int servo_index = 0;

void loop() {

  for (servo_index = 0; servo_index < 4; servo_index++) {
    for (ang = 0; ang < 181; ang++) {
      int pulse = ang2pulse(ang);
      Serial.print(servo_index);
      Serial.print("\t");
      Serial.print(ang);
      Serial.print("\t");
      Serial.print(pulse);
      Serial.println();

      pca.writeMicroseconds(servo_index, pulse);
      delay(1);
    }
  }
}

bool isI2Cconnected() {
  bool isConnected = false;
  scanner.begin();
  for (int addr = 0; addr < 128; addr++) {
    // if (addr % 8 == 0) Serial.println();
    if (scanner.ping(addr)) {
      Serial.print(addr);
      isConnected = true;
      Serial.println();
    }
  }
  if (!isConnected) {
    Serial.println("disconnected");
  }
  return isConnected;
}

int ang2pulse(long ang) {
  long SERVOMIN = 550;
  long SERVOMAX = 2450;
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);  // map angle of 0 to 180 to Servo min and Servo max
  return pulse;
}