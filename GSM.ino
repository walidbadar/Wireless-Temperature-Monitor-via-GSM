#include <DHT.h>
#include <SoftwareSerial.h>
#include "Timer.h"

Timer t1, t2, t3;
SoftwareSerial mySerial(9, 8); // RX, TX
DHT dht(7, DHT22);

float temperature;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  Serial.println("DHT22 Started");
  dht.begin();
  delay(60000);
  boot();
  t1.every(300000, readTemp);
  t2.every(7200000, SendMessage1);
  t3.every(7200000, SendMessage2);
}

void loop() {
  t1.update(); // tick the time
  t2.update(); // tick the time
  t3.update(); // tick the time
}

void readTemp() {
  temperature = dht.readTemperature();
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  if (temperature > 7.00) {
    Serial.println("Warning Critical Temperature");
    WarningMessage1();
    WarningMessage2();
  }
}

void boot() { 
  mySerial.println("AT+CMGF=1\r\n");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second 
  mySerial.print("AT+CMGS=\"");
  mySerial.print("+92xxxxxxxxxx");
  mySerial.print("\"\r\n");
  delay(2000);
  mySerial.println("CoolCell 2 Temperature Monitor Started");
  delay(10);
  mySerial.write(0x1A);
  delay(4000);
  return;
}

void SendMessage1() {
  temperature = dht.readTemperature();
  
  mySerial.println("AT+CMGF=1\r\n");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second 
  mySerial.print("AT+CMGS=\"");
  mySerial.print("+92xxxxxxxxxx");
  mySerial.print("\"\r\n");
  delay(2000);
  mySerial.print("CoolCell 2 Current Temperature: ");
  delay(10);
  mySerial.print(temperature);
  delay(10);
  mySerial.println(" C");
  delay(10);
  mySerial.write(0x1A);
  delay(4000);
  return;
}

void SendMessage2() {
  temperature = dht.readTemperature();
  
  mySerial.println("AT+CMGF=1\r\n");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second 
  mySerial.print("AT+CMGS=\"");
  mySerial.print("+92xxxxxxxxxx");
  mySerial.print("\"\r\n");
  delay(2000);
  mySerial.print("CoolCell 2 Current Temperature: ");
  delay(10);
  mySerial.print(temperature);
  delay(10);
  mySerial.println(" C");
  delay(10);
  mySerial.write(0x1A);
  delay(4000);
  return;
}

void WarningMessage1() {
  mySerial.println("AT+CMGF=1\r\n");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second 
  mySerial.print("AT+CMGS=\"");
  mySerial.print("+92xxxxxxxxxx");
  mySerial.print("\"\r\n");
  delay(2000);  
  mySerial.println("Warning CoolCell 2 Critical Temperature");
  delay(10);
  mySerial.write(0x1A);
  delay(4000);
  return;
}

void WarningMessage2() {
  mySerial.println("AT+CMGF=1\r\n");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second 
  mySerial.print("AT+CMGS=\"");
  mySerial.print("+92xxxxxxxxxx");
  mySerial.print("\"\r\n");
  delay(2000);  
  mySerial.println("Warning CoolCell 2 Critical Temperature");
  delay(10);
  mySerial.write(0x1A);
  delay(4000);
  return;
}

