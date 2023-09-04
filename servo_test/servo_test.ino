#include <Servo.h>
//static const uint8_t D0   = 16;
//static const uint8_t D1   = 5;
//static const uint8_t D2   = 4;
//static const uint8_t D3   = 0;
//static const uint8_t D4   = 2;
//static const uint8_t D5   = 14;
//static const uint8_t D6   = 12;
//static const uint8_t D7   = 13;
//static const uint8_t D8   = 15;
//static const uint8_t D9   = 3;
//static const uint8_t D10  = 1;

int servo = 0;
int servo1 = 2;
int servo2 = 4;
int servo3 = 5;
int servo4 = 15;
int goc;
int delay_time = 750;


Servo myServo;
Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;



void setup() 
{ 
    Serial.begin(115200);
    
    myServo.attach(servo,700,2300); 
    myServo1.attach(servo1,700,2300);
    myServo2.attach(servo2,700,2300);
    myServo3.attach(servo3,700,2300);
    myServo4.attach(servo4,500,2400);
}

void dam()
{
    myServo.write(0);
    myServo1.write(0);
    myServo2.write(90);
    myServo3.write(0);
    delay(delay_time);

    myServo.write(90);
    myServo1.write(100);
    myServo2.write(90);
    myServo3.write(90);
    delay(delay_time*2);
}

void chem_doc()
{
    myServo.write(90);
    myServo1.write(160);
    myServo2.write(45);
    myServo3.write(180);
    delay(delay_time);
  
    myServo.write(0);
    myServo1.write(0);
    myServo2.write(90);
    myServo3.write(0);
    delay(delay_time*2);  
}

void loop() 
{ 
//    dam();
//    chem_doc();
/*  servo 1: [90: dam, 0: chem]
    servo 2 + 4: 0-180 --> xuong - len
    servo 3: 0-180 --> trai - phai
*/
    myServo.write(90); 
    myServo1.write(90);
    myServo2.write(0); // neck'
    myServo3.write(90);
    delay(delay_time*4);
    myServo.write(90);
    myServo1.write(180);
//    myServo2.write(90);
    myServo3.write(0);
    delay(delay_time*2);
////    myServo4.write(90);
//    goc = myServo.read();
//    Serial.print("Góc hiện tại: "); Serial.println(goc);
//    delay(delay_time);

}
