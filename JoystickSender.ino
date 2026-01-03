#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

const int PIN_J1_X = 34;
const int PIN_J1_Y = 35;
const int PIN_J1_BTN = 32;

const int PIN_J2_X = 33;
const int PIN_J2_Y = 25;
const int PIN_J2_BTN = 26;

typedef struct {
  int j1x;
  int j1y;
  int j1btn;
  int j2x;
  int j2y;
  int j2btn;
} joystickData;

joystickData myData;

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
}

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_J1_BTN, INPUT_PULLUP);
  pinMode(PIN_J2_BTN, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) 
    return;
 
  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
    return;
}

void loop() {
  myData.j1x = analogRead(PIN_J1_X);
  myData.j1y = analogRead(PIN_J1_Y);
  myData.j1btn = digitalRead(PIN_J1_BTN);

  myData.j2x = analogRead(PIN_J2_X);
  myData.j2y = analogRead(PIN_J2_Y);
  myData.j2btn = digitalRead(PIN_J2_BTN);

  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  
  delay(20);
}
