/*
    SPI Slave Demo Sketch
    Connect the SPI Master device to the following pins on the esp8266:

    GPIO    NodeMCU   Name  |   Uno
  ===================================
     15       D8       SS   |   D10
     13       D7      MOSI  |   D11
     12       D6      MISO  |   D12
     14       D5      SCK   |   D13

    Note: If the ESP is booting at a moment when the SPI Master has the Select line HIGH (deselected)
    the ESP8266 WILL FAIL to boot!
    See SPISlave_SafeMaster example for possible workaround

*/

#include <SPI.h>

#define BUFFER_LENGTH 12

const int SS_PIN = 15;  // GPIO15 for Slave Select

char receivedbyte = 0;
char rxBuff[BUFFER_LENGTH] = { 0 };

unsigned long time_now = 0;
uint16_t period = 1000;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Initialize SPI
  pinMode(SS_PIN, OUTPUT);  // SS must be output for Master mode to work
  SPI.begin();              // Initialize SPI interface

  // Configure SPI
  SPI.setFrequency(50000);     // 50kHz as slow as possible outside dog audible range :')
  SPI.setDataMode(SPI_MODE0);  // Set SPI mode to MODE0
  SPI.setBitOrder(MSBFIRST);   // Most systems use MSB first
  time_now = millis();
}

void loop() 
{

  if (millis() > time_now + period) // 1 second
  {
    char message[100] = "Hello Slave!";
    transmitSPI(&message[0], BUFFER_LENGTH);
    time_now = millis();
    for (int i = 0; i < BUFFER_LENGTH; i++) {
      Serial.print(rxBuff[i]);
    }
    Serial.println();
  }

  // Wait a bit
}


void transmitSPI(char* data, uint16_t length) 
{
  for (int i = 0; i < length; i++) 
  {
    digitalWrite(SS_PIN, LOW);          // Select the slave
    rxBuff[i] = SPI.transfer(data[i]);  // Send a byte
    // rxBuff[i] = receivedbyte;
    // Serial.print(receivedbyte);
    digitalWrite(SS_PIN, HIGH);  // Deselect the slave
  }
  Serial.println("");
}
