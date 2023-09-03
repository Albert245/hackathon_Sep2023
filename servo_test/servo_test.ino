#include <Servo.h>
static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;

int servo = 2;
int goc;


Servo myServo;


void setup() 
{ 
    Serial.begin(115200);
    
    myServo.attach(servo,500,2400); 
}

 
void loop() 
{ 
    myServo.write(0);
    goc = myServo.read();
    Serial.print("Góc hiện tại: "); Serial.println(goc);
    delay(250);
  
    myServo.write(90);
    goc = myServo.read();
    Serial.print("Góc hiện tại: "); Serial.println(goc);
    delay(250);
  
    myServo.write(180);
    goc = myServo.read();
    Serial.print("Góc hiện tại: "); Serial.println(goc);
    delay(250);

}
