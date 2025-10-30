#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "ARMORED_NET";
const char* password = "12345678";

WiFiUDP udp;
const char* receiverIP = "192.168.4.2";
const int udpPort = 4210;

const int joy1X = 0;
const int joy1Y = 1;
const int joy2X = 2;
const int joy2Y = 3;

void setup() {
  Serial.begin(115200);
  pinMode(joy1X, INPUT);
  pinMode(joy1Y, INPUT);
  pinMode(joy2X, INPUT);
  pinMode(joy2Y, INPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

void loop() {
  int j1x = analogRead(joy1X);
  int j1y = analogRead(joy1Y);
  int j2x = analogRead(joy2X);
  int j2y = analogRead(joy2Y);

  char buffer[64];
  snprintf(buffer, sizeof(buffer), "%d,%d,%d,%d", j1x, j1y, j2x, j2y);

  udp.beginPacket(receiverIP, udpPort);
  udp.print(buffer);
  udp.endPacket();

  Serial.println(buffer);
  delay(50);
}
