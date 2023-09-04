//Libraries
#include <Wire.h>                     //https://www.arduino.cc/en/reference/wire
#include <Adafruit_PWMServoDriver.h>  //https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library

#include "I2C_SCANNER.h"

I2C_SCANNER scanner;

//Constants
#define nbPCAServo 16
//Parameters
int MIN_IMP[nbPCAServo] = { 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500 };
int MAX_IMP[nbPCAServo] = { 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500 };
int MIN_ANG[nbPCAServo] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int MAX_ANG[nbPCAServo] = { 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180 };

int isI2CConnected = 0;
//Objects
Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);

void setup() {
  //Init Serial USB
  Serial.begin(9600);
  // while (!Serial);
  // Serial.println();
  // Serial.println(__FILE__);
  // Serial.print("I2C_SCANNER_LIB_VERSION: ");
  // Serial.println(I2C_SCANNER_LIB_VERSION);

  // scanner.begin();

  // for (int addr = 0; addr < 128; addr++)
  // {
  //   // if (addr % 8 == 0) Serial.println();
  //   if (scanner.ping(addr))
  //   {
  //     Serial.print(addr);
  //     isI2CConnected = 1;
  //     Serial.println();
  //   }
  // }
  // if (!isI2CConnected)
  // {
  //   Serial.println("disconnected");
  // }
  // Serial.println();
  // Serial.println();

  // delay(500);

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
void loop() {
  pcaScenario();
}
void pcaScenario() { /* function pcaScenario */
  ////Scenario to test servomotors controlled by PCA9685 I2C Module
  for (int i = 0; i < 6; i++) {
    Serial.print("Servo");
    Serial.println(i);
    //int middleVal=((MAX_IMP[i]+MIN_IMP[i])/2)/20000*4096; // conversion µs to pwmval
    //pca.setPWM(i,0,middleVal);
    for (int pos = (MAX_IMP[i] + MIN_IMP[i]) / 2; pos < MAX_IMP[i]; pos += 10) {
      pca.writeMicroseconds(i, pos);
      delay(10);
    }
    for (int pos = MAX_IMP[i]; pos > MIN_IMP[i]; pos -= 10) {
      pca.writeMicroseconds(i, pos);
      delay(10);
    }
    for (int pos = MIN_IMP[i]; pos < (MAX_IMP[i] + MIN_IMP[i]) / 2; pos += 10) {
      pca.writeMicroseconds(i, pos);
      delay(10);
    }
    pca.setPin(i, 0, true);  // deactivate pin i
  }
}

int jointToImp(double x, int i) { /* function jointToImp */
  ////Convert joint angle into pwm command value
  int imp = (x - MIN_ANG[i]) * (MAX_IMP[i] - MIN_IMP[i]) / (MAX_ANG[i] - MIN_ANG[i]) + MIN_IMP[i];
  imp = max(imp, MIN_IMP[i]);
  imp = min(imp, MAX_IMP[i]);
  return imp;
}