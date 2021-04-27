#include <Servo.h>

#define ESC_PIN 3
#define RELAY_PIN 4

#define PIN_BT1 5 // MAX SPEED
#define PIN_BT2 6 // FIRE/BREAK

#define MODE_DISARM 0
#define MODE_ARM 1
#define MODE_MAX_SPEED 2

#define relay_active false

int mode;
Servo esc;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting......................");
  pinMode(RELAY_PIN, OUTPUT); // relay init
  digitalWrite(RELAY_PIN, !relay_active); // off relay

  esc.attach(3, 1000, 2000);//motor init
  Serial.println("esc attached");
  mode = MODE_DISARM;

  delay(500);
}

void loop() {
  if (mode == MODE_DISARM) {
    arm_esc();
  } else if (mode == MODE_ARM) {
    if (digitalRead(PIN_BT1)) {
      max_speed();
    }
  } else if (mode == MODE_MAX_SPEED) {
    if (digitalRead(PIN_BT2)) {
      motor_break();
    } else if (!digitalRead(PIN_BT1)) {
        slow_down();
  }
}

void arm_esc() {
  esc.write(0);//motor arm
  Serial.print("esc arm start");
  delay(3000);
  Serial.println("-done");
  mode = MODE_ARM;
}

void max_speed() {
  mode = MODE_MAX_SPEED;
  esc.write(i);
  delay(4000);//speed up delay
  tone(PIN_BUZZER, 6000, 500);
  Serial.print("max speed");
  Serial.println("-done");
}

void motor_break() {
  esc.write(0);
  Serial.print("motor stopped");

  //motor breaking 
  digitalWrite(RELAY_PIN, relay_active); // on relay
  Serial.print("relay on");
  tone(PIN_BUZZER, 6000, 100);
  delay(100);
  digitalWrite(RELAY_PIN, !relay_active); // off relay
  Serial.println("-done");
  mode = MODE_DISARM;
}

void slow_down() {
  esc.write(0);
  Serial.print("motor stopped");
  mode = MODE_ARM;
  delay(2000);
  Serial.println("-done");
}

