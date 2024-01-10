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

const int SS_PIN = 15; // GPIO15 for Slave Select

char receivedbyte = 0;
char message[100] = "Hello Slave!";


void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Initialize SPI
  pinMode(SS_PIN, OUTPUT); // SS must be output for Master mode to work
  SPI.begin(); // Initialize SPI interface

  // Configure SPI
  SPI.setFrequency(1000000); // Set clock to 1 MHz or as per your requirement
  SPI.setDataMode(SPI_MODE0); // Set SPI mode to MODE0
  SPI.setBitOrder(MSBFIRST); // Most systems use MSB first
}

void loop() {
  // Example of sending and receiving a byte
  delay(1000);
  Serial.print ("Received byte: ");
  transmitSPI(message,sizeof(message));
  // Wait a bit
}


void transmitSPI(char * data, uint16_t length)
{
  digitalWrite(SS_PIN, LOW); // Select the slave
  for (int i = 0; i<length; i++)
  {
    receivedbyte = SPI.transfer(data[i]);        // Send a byte
    Serial.print(receivedbyte);
  }
  receivedbyte = SPI.transfer((char)'\n');        // Send a byte
  Serial.print(receivedbyte);
  Serial.println("");
  digitalWrite(SS_PIN, HIGH); // Deselect the slave
}

