#include <Servo.h>
#define ESC_PIN 3
#define RELAY_PIN 4

Servo esc;

void setup() {
  Serial.begin(115200);
  esc.attach(ESC_PIN,1000,3000);
  Serial.println("esc attached");

  pinMode(RELAY_PIN, OUTPUT); // relay init
  digitalWrite(RELAY_PIN, HIGH); // off relay
  
  esc.write(0);
  delay(3000);
  Serial.println("esc ready");

  esc.write(180);
  Serial.println("reaching to max speed");
  delay(3000);
  
  esc.write(0);
  Serial.println("motor stopped");
  
    //motor breaking
  delay(10);
  digitalWrite(RELAY_PIN, LOW); // on relay
  Serial.println("relay on");
  delay(100);
  digitalWrite(RELAY_PIN, HIGH); // off relay
  Serial.println("relay off");
}

void loop() {
  
}
