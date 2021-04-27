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
  
  delay(3000);// delay for motor reaching to max
  
  esc.write(0);//esc stopped
  Serial.println("motor stopped");
}

void loop() {
  
}
