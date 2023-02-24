#include <DHT22.h>
#define data 2
DHT22 dht22(data);

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(5, 6);  // RX, TX
DFRobotDFPlayerMini myDFPlayer;

#include <MQUnifiedsensor.h>

int MQ5 = A0;
int MQ5SENSORTHRESHOLD = 120;

int isFlame = HIGH;

MQUnifiedsensor MQ7("Arduino UNO", 5, 10, A1, "MQ-7");

void setup() {
  Serial.begin(115200);
  mySoftwareSerial.begin(9600);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true) {
      delay(0);  // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30

  MQ7.setRegressionMethod(1);  //_PPM =  a*ratio^b
  MQ7.setA(99.042);
  MQ7.setB(-1.518);  // Configurate the ecuation values to get CO concentration
  MQ7.init();
  float calcR0 = 0;
  for (int i = 1; i <= 10; i++) {
    MQ7.update();  // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += MQ7.calibrate(27.5);
  }
  MQ7.setR0(calcR0 / 10);
  MQ7.serialDebug(true);

  pinMode(7, INPUT);
}

void loop() {
  temperature();
  gas();
  flame();
  C0();
  delay(2000);
}

void temperature() {
  dht22.debug();
  float t = dht22.getTemperature();
  Serial.print("Temperature=");
  Serial.print(t, 2);
  Serial.println(" C");
  if (t > 40) {
    Serial.println("The temperature is too high");
    pinMode(8, OUTPUT);
    digitalWrite(8, HIGH);
    myDFPlayer.play(4);
    delay(4000);
  } else if (t < 10) {
    Serial.println("The temperature is too low");
    pinMode(9, OUTPUT);
    digitalWrite(9, HIGH);
    myDFPlayer.play(5);
    delay(4000);
  } else if (t > 10 and t < 40) {
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
}

void gas() {
  int MQ5analogSensor = analogRead(MQ5);
  if (MQ5analogSensor > MQ5SENSORTHRESHOLD) {
    Serial.println("Gas conc. is too high");
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
    myDFPlayer.play(1);
    delay(4000);
  } else {
    Serial.println("Gas conc. is normal");
    pinMode(10, OUTPUT);
    digitalWrite(10, LOW);
  }
}

void flame() {
  isFlame = digitalRead(7);
  if (isFlame == 0) {
    Serial.println("Fire Detected");
    pinMode(12, OUTPUT);
    digitalWrite(12, HIGH);
    myDFPlayer.play(3);
    delay(4000);
  } else {
    Serial.println("No Fire");
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
  }
}

void C0() {
  MQ7.update();                    // Update data, the arduino will be read the voltage on the analog pin
  float COppm = MQ7.readSensor();  // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
  Serial.print("CO= ");
  Serial.print(COppm);
  Serial.println(" ppm");
  if (COppm > 100) {
    Serial.println("C0 conc. is high");
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    myDFPlayer.play(6);
    delay(4000);
  } else {
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
  }
}
