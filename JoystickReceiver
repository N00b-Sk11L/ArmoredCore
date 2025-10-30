#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "ARMORED_NET";
const char* password = "12345678";

WiFiUDP udp;
const int udpPort = 4210;

const int LEFT_IN1 = 5;
const int LEFT_IN2 = 6;
const int LEFT_PWM = 7;
const int RIGHT_IN1 = 8;
const int RIGHT_IN2 = 9;
const int RIGHT_PWM = 10;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  udp.begin(udpPort);

  pinMode(LEFT_IN1, OUTPUT); pinMode(LEFT_IN2, OUTPUT); pinMode(RIGHT_IN1, OUTPUT); pinMode(RIGHT_IN2, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT); pinMode(RIGHT_PWM, OUTPUT);
}

void loop() 
{
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char buffer[64];
    int len = udp.read(buffer, sizeof(buffer) - 1);
    if (len > 0) buffer[len] = '\0';

    int j1x, j1y, j2x, j2y;
    if (sscanf(buffer, "%d,%d,%d,%d", &j1x, &j1y, &j2x, &j2y) == 4) {
      int forward  = ((j1y - 2048) * 255) / 2048;
      int rotation = ((j2x - 2048) * 255) / 2048;

      int leftPWM  = constrain(forward - rotation, -255, 255);
      int rightPWM = constrain(forward + rotation, -255, 255);

      setSpeed(LEFT_IN1, LEFT_IN2, LEFT_PWM, leftPWM);
      setSpeed(RIGHT_IN1, RIGHT_IN2, RIGHT_PWM, rightPWM);

      Serial.printf("L=%d  R=%d  (F=%d  Rot=%d)\n", leftPWM, rightPWM, forward, rotation);
    }
  }
}

void setSpeed(int in1, int in2, int pwmPin, int speed) {
  if (speed > 0) { digitalWrite(in1, HIGH); digitalWrite(in2, LOW); }
  else if (speed < 0) { digitalWrite(in1, LOW); digitalWrite(in2, HIGH); speed = -speed; }
  else { digitalWrite(in1, LOW); digitalWrite(in2, LOW); }
  analogWrite(pwmPin, constrain(speed, 0, 255));
}
