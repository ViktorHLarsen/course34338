// Written by Nick Gammon
// February 2011
/**
 * Send arbitrary number of bits at whatever clock rate (tested at 500 KHZ and 500 HZ).
 * This script will capture the SPI bytes, when a '\n' is recieved it will then output
 * the captured byte stream via the serial.
 */

#include <SPI.h>

#define SS_PIN 10
#define BUFFER_LENGTH 12

char RxBuf[100];
uint8_t pos;
uint8_t it_flag;

char TxBuf[100] = "Hello Master";

void setup (void)
{
  Serial.begin (115200);   // debugging

  initSlaveSPI();

}  // end of setup



uint16_t j = 0;
// main loop - wait for flag set in interrupt routine
void loop (void)
{
  if (it_flag == 1)
    {
      j++;
      // Serial.println(pos);
      // buf[pos] = 0;  
      // Serial.print ("Buffer value: ");
      Serial.print(RxBuf);
      Serial.println();
      pos = 0;
      it_flag = 0; // reset flag
    }  // end of flag set
}  // end of loop
    
// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;  // Rx
  SPDR = (uint8_t)TxBuf[pos]; // Tx

  RxBuf[pos] = c; // Buckets in to RxBuffer

  pos++;          // increments array position

  if (pos >= BUFFER_LENGTH) // last array position
  {
    it_flag = 1; // set interrupt flag
    pos = 0;        // reset buffer position
  }
}

void initSlaveSPI()
{
  pinMode(MISO, OUTPUT); // Slave so MISO is output

  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  
  // get ready for an interrupt 
  pos = 0;   // buffer empty
  it_flag = 0;

  // now turn on interrupts
  SPI.attachInterrupt();
  uint8_t empty = 0;
  for (int i = 0; i<4; i++) // read out anything from Rx fifo in to clear it
  {
    empty = SPDR;
  }
}