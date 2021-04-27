#include <Servo.h>
#define ESC_PIN 3

Servo esc;

void setup() {
  Serial.begin(115200);
  esc.attach(ESC_PIN,1000,3000);
  Serial.println("esc attached");

  esc.write(0);
  delay(3000);
  Serial.println("esc ready");

  esc.write(180);
  Serial.println("reaching to max speed");
  delay(3000);
  
  esc.write(0);
  Serial.println("motor stopped");
}

void loop() {
  
}
