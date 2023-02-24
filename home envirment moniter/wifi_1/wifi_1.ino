#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <TridentTD_LineNotify.h>
#define LINE_TOKEN "Qc3pWHBH6McWjc0VmLhlu8ieaM3ecdsH8O3cINKklmQ"


int GAS;
int FLAME;
int TempH;
int TempL;
int C0;
const char* ssid = "Tenda";
const char* password = "0000000000";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("arduino test");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  TempH = digitalRead(D1);
  if (TempH == 1) {
    pinMode(D0, OUTPUT);
    digitalWrite(D0, HIGH);
    delay(500);
    digitalWrite(D0, LOW);
    delay(500);
    digitalWrite(D0, HIGH);
    delay(500);
    digitalWrite(D0, LOW);
    delay(500);
    digitalWrite(D0, HIGH);
    Serial.println("The temperature is too high");
    LINE.setToken(LINE_TOKEN);
    LINE.notify("室內溫度過高");
    delay(2000);
  }
  if (TempH == 0) {
    pinMode(D0, OUTPUT);
    digitalWrite(D0, LOW);
  }
  TempL = digitalRead(D2);
  if (TempL == 1) {
    pinMode(D0, OUTPUT);
    digitalWrite(D0, HIGH);
    delay(500);
    digitalWrite(D0, LOW);
    delay(500);
    digitalWrite(D0, HIGH);
    delay(500);
    digitalWrite(D0, LOW);
    delay(500);
    digitalWrite(D0, HIGH);
    Serial.println("The temperature is too low");
    LINE.setToken(LINE_TOKEN);
    LINE.notify("室內溫度過低");
    delay(2000);
  }
  if (TempL == 0) {
    pinMode(D0, OUTPUT);
    digitalWrite(D0, LOW);
  }
  GAS = digitalRead(D5);
  if (GAS == 1) {
    pinMode(D0, OUTPUT);
    digitalWrite(D0, HIGH);
    delay(500);
    digitalWrite(D0, LOW);
    delay(500);
    digitalWrite(D0, HIGH);
    delay(500);
    digitalWrite(D0, LOW);
    delay(500);
    digitalWrite(D0, HIGH);
    Serial.println("Gas conc. is too high");
    LINE.setToken(LINE_TOKEN);
    LINE.notify("瓦斯濃度過高");
    delay(2000);
  }
  if (GAS == 0) {
    pinMode(D0, OUTPUT);
    digitalWrite(D0, LOW);
  }
  FLAME = digitalRead(D7);
  if (FLAME == 1) {
    pinMode(D0, OUTPUT);
    digitalWrite(D0, HIGH);
    delay(500);
    digitalWrite(D0, LOW);
    delay(500);
    digitalWrite(D0, HIGH);
    delay(500);
    digitalWrite(D0, LOW);
    delay(500);
    digitalWrite(D0, HIGH);
    Serial.println("Fire Detected");
    LINE.setToken(LINE_TOKEN);
    LINE.notify("偵測到有火源");
    delay(2000);
  }
  if (FLAME == 0) {
    pinMode(D0, OUTPUT);
    digitalWrite(D0, LOW);
  }
  C0 = digitalRead(D8);
  if (C0 == 1) {
    pinMode(D0, OUTPUT);
    digitalWrite(D0, HIGH);
    delay(500);
    digitalWrite(D0, LOW);
    delay(500);
    digitalWrite(D0, HIGH);
    delay(500);
    digitalWrite(D0, LOW);
    delay(500);
    digitalWrite(D0, HIGH);
    Serial.println("Fire Detected");
    LINE.setToken(LINE_TOKEN);
    LINE.notify("一氧化碳濃度過高");
    delay(2000);
  }
  if (C0 == 0) {
    pinMode(D0, OUTPUT);
    digitalWrite(D0, LOW);
  }
}
