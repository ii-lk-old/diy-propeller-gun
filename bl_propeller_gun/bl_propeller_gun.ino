#include <Servo.h>

#define ESC_PIN 3
#define RELAY_PIN 4

#define PIN_BT1 5 // MAX SPEED
#define PIN_BT2 6 // FIRE/BREAK
#define PIN_BUZZER 7 // BUZZER

#define MODE_DISARM 0
#define MODE_ARM 1
#define MODE_MAX_SPEED 2

int mode;

#define relay_active true
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
  pinMode(PIN_BUZZER, OUTPUT);
  tone(PIN_BUZZER, 3000, 50);
  delay(500);
}
int release_count = 0;
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
      release_count++;
      if (release_count > 5) {
        slow_down();
        return;
      }
    } else {
      release_count = 0;
    }
  }
  delay(20);
}

void arm_esc() {
  esc.write(0);//motor arm
  Serial.print("esc arm start");
  _delay(3000, 0);
  Serial.println("-done");
  mode = MODE_ARM;
}

void max_speed() {
  release_count = 0;
  mode = MODE_MAX_SPEED;
  for (int i = 50; i <= 180; i++) {
    esc.write(i);
    delay(20);
    if (!digitalRead(PIN_BT1)) {
      release_count++;
      if (release_count > 5) {
        slow_down();
        return;
      }
    } else {
      release_count = 0;
    }

  }
  tone(PIN_BUZZER, 6000, 500);

  Serial.print("max speed");
  Serial.println("-done");
}

void motor_break() {
  esc.write(0);
  Serial.print("motor stopped");
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
  _delay(2000, -1);
  Serial.println("-done");
}

void _delay(int duration, int tone_dir) {
  long ltime = millis();
  while (millis() - ltime < duration) {
    tone(PIN_BUZZER, 3000 + ((millis() - ltime)*tone_dir), 50);
    delay(100);
    if (mode == MODE_MAX_SPEED && !digitalRead(PIN_BT1)) {
      slow_down();
      return;
    } else if (mode == MODE_ARM && digitalRead(PIN_BT1)) {
      max_speed();
      return;
    }
  }
}
