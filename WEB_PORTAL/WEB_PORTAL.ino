#include "SERVO_esp32.h"
// #include "SERVO_ESP32_BLUE.h"
#include "websockets_arm.h"

#define s1Pin 13
#define s2Pin 12
#define s3Pin 14
#define s4Pin 27
#define s5Pin 26
#define s6Pin 25
#define s7Pin 33
#define s8Pin 32

SERVO s1,s2,s3,s4,s5,s6,s7,s8;



const char* ssid = "ROBOCON LDCE";
const char* password = "RBCN2025";

void setup() {
  Serial.begin(115200);
  pinMode(2, 1);

  //SERVO SETUP
  setupServo(s1, s1Pin);
  setupServo(s2, s2Pin);
  setupServo(s3, s3Pin);
  setupServo(s4, s4Pin);
  setupServo(s5, s5Pin);
  setupServo(s6, s6Pin);
  setupServo(s7, s7Pin);
  setupServo(s8, s8Pin);

  //WiFi SETUP
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(2, !digitalRead(2));
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  setupWebSocket();

  delay(1000);
}

int inp = 0;

void loop() {

  updateWebSocket();


  if(Serial.available()) inp = Serial.parseInt();

  setServo(s1, s1Inp);
  setServo(s2, s2Inp);
  setServo(s3, s3Inp);
  setServo(s4, s4Inp);
  setServo(s5, s5Inp);
  setServo(s6, s6Inp);
  setServo(s7, s7Inp);
  setServo(s8, s8Inp);

  Serial.print(s1Inp);
  Serial.print("\t");
  Serial.print(s2Inp);
  Serial.print("\t");
  Serial.print(s3Inp);
  Serial.print("\t");
  Serial.print(s4Inp);
  Serial.print("\t");
  Serial.print(s5Inp);
  Serial.print("\t");
  Serial.print(s6Inp);
  Serial.print("\t");
  Serial.print(s7Inp);
  Serial.print("\t");
  Serial.print(s8Inp);
  Serial.print("\t");
  Serial.println();
}
