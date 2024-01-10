// Written by Nick Gammon
// February 2011
/**
 * Send arbitrary number of bits at whatever clock rate (tested at 500 KHZ and 500 HZ).
 * This script will capture the SPI bytes, when a '\n' is recieved it will then output
 * the captured byte stream via the serial.
 */

#include <SPI.h>

#define SS_PIN 10

char buf[100];
uint8_t pos;
uint8_t process_it;

char message[100] = "Hello Master!";

void setup (void)
{
  Serial.begin (115200);   // debugging

  // have to send on master in, *slave out*
  // pinMode(SS_PIN, INPUT_PULLUP);
  pinMode(MISO, OUTPUT);

  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  
  // get ready for an interrupt 
  pos = 0;   // buffer empty
  process_it = 0;

  // now turn on interrupts
  SPI.attachInterrupt();

}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;  // grab byte from SPI Data Register
  
  // add to buffer if room
  if (pos < sizeof(buf))
  {
    buf[pos] = c;
    pos++;
    // Serial.println(pos);
    // example: newline means time to process buffer
    if (c == '\n')
    {
      // Serial.println(pos);
      // Serial.println("Entered SPI ISR");
      process_it = 1;
      
    }
  }  // end of room available
  // for(int i=0;i<sizeof(message) ; i++)
  // {
  //   SPDR = message[i];
  // }
}  // end of interrupt routine SPI_STC_vect

// main loop - wait for flag set in interrupt routine
void loop (void)
{
  if (process_it == 1)
    {
    buf[pos] = 0;  
    // Serial.print ("Buffer value: ");
    Serial.print(buf);
    pos = 0;
    process_it = 0;
      for(int i=0;i<sizeof(message) ; i++)
      {
        SPI.transfer(message[i]);
      }
    }  // end of flag set
    
}  // end of loop