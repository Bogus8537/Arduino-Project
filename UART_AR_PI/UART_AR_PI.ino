#include <SoftwareSerial.h>

#define RXP 2
#define TXP 3

SoftwareSerial Serial_PI(RXP, TXP);

void setup() {
  Serial.begin(9600);
  Serial.println("===== UART ARD-PI =====");
  Serial_PI.begin(9600);
}

void loop() {
  
  // Raspberry Pi -> Arduino UNO
  if(Serial_PI.available())
  {
    char data_PI = Serial_PI.read(); 
    Serial.write(data_PI);
  }

  // Arduino -> Raspberry Pi
  if(Serial.available())
  {
    char data_AR = Serial.read();
    Serial.print(data_AR);
    Serial_PI.write(data_AR);
  }
}
