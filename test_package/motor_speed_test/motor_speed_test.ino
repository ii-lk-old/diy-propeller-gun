#include <Servo.h>
#define ESC_PIN 3 // Use any pwm pin

Servo esc;

void setup() {
  Serial.begin(115200);//baudrate 115200
  esc.attach(ESC_PIN,1000,3000); 

  esc.write(0);
  delay(3000);//arming delay 

  esc.write(180);
  delay(3000); 
}

void loop() {
  
}
