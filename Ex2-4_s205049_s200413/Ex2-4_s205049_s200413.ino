// Define LED pins
int redLED = 16;    // Red LED gpio 16
int yellowLED = 5; // Yellow LED gpio 5
int greenLED = 4;  // Green LED
int msb = 14; // d5 gpio 14
int secbit = 2; // gpio 2
int lsb = 0; // gpio 0
int button = 13; // d7 
int counter = 0;

void setup() {
  // Set baud rate for serial communication
  Serial.begin(115200);

  // Set LED pins as output
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(msb, OUTPUT);
  pinMode(secbit, OUTPUT);
  pinMode(lsb, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  /* EXERCISE 2 */
  // f_counter();
  // stop();
  // f_counter();
  // start();
  // f_counter();
  // go();
  // f_counter();
  // caution();

  /* Exercise 3 */
  if(digitalRead(button) != true)
  {
    digitalWrite(greenLED, HIGH);
  }
  digitalWrite(greenLED, LOW);



}

void stop()
{
  digitalWrite(redLED, HIGH);
  Serial.println("STOP");
  delay(2000);
  digitalWrite(redLED, LOW);
  Serial.println("GO");
}
void start()
{
  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  Serial.println("START");
  delay(1000);
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
}
void go()
{
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, HIGH);
  Serial.println("GO");
  delay(5000);
  digitalWrite(greenLED, LOW);
}

void caution()
{
  digitalWrite(yellowLED, HIGH);
  Serial.println("CAUTION");
  delay(1000);
  digitalWrite(yellowLED, LOW);

}

void f_counter()
{
  counter++;
  digitalWrite(lsb, counter & 0x01);
  digitalWrite(secbit, counter & 0x02);
  digitalWrite(msb, counter & 0x04);

  // Optional: Change all LEDs to red
  if (counter == 7) {
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  }

  // Print the current value of the counter in binary
  Serial.print("Counter: ");
  Serial.println(counter, BIN);
}


