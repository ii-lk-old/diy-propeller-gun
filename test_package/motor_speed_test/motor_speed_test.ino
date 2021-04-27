#include <Servo.h>
#define ESC_PIN 3 // Use any pwm pin

Servo esc;

void setup() {
  Serial.begin(115200);//baudrate 115200
  esc.attach(ESC_PIN,1000,3000); 
  Serial.println("esc attached");

  esc.write(0);
  delay(3000);//arming delay 
  Serial.println("esc ready");

  esc.write(180);
  Serial.println("reaching to max speed"); 
}

void loop() {
  
}
