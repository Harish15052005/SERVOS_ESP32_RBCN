// #include "SERVO_esp32.h"
#include "SERVO_ESP32_BLUE.h"

#define tstServoPin 13
SERVO tstServo;


#define PWM_FREQ 50
#define PWM_RES 13
#define PWM_MAX 8191


void setup() {
  Serial.begin(115200);

  setupServo(tstServo, tstServoPin, 0);
}

int inp = 0;

void loop() {
  if (Serial.available()) {
    inp = Serial.parseInt();
  }
  setServo(tstServo, inp);
  Serial.println(inp);
}
