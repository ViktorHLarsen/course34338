// Define LED pins
int redLED = 1;    // Red LED
int yellowLED = 2; // Yellow LED
int greenLED = 3;  // Green LED

void setup() {
  // Set baud rate for serial communication
  Serial.begin(115200);

  // Set LED pins as output
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop() {
  // Traffic light sequence
  // Green light for 5 seconds with "GO" instruction
  digitalWrite(greenLED, HIGH);
  Serial.println("GO");
  delay(5000);

  // Yellow light for 2 seconds with "CAUTION" instruction
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, HIGH);
  Serial.println("CAUTION");
  delay(2000);

  // Red light for 5 seconds with "STOP" instruction
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, HIGH);
  Serial.println("STOP");
  delay(5000);

  // Turn off red light before the next green light
  digitalWrite(redLED, LOW);

  // Binary counter sequence
  for (int counter = 0; counter < 8; counter++) {
    // Set LEDs according to the binary representation of the counter
    digitalWrite(redLED, counter & 0x01);
    digitalWrite(yellowLED, counter & 0x02);
    digitalWrite(greenLED, counter & 0x04);

    // Optional: Change all LEDs to red
    if (counter == 7) {
      digitalWrite(redLED, HIGH);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, LOW);
    }

    // Print the current value of the counter in binary
    Serial.print("Counter: ");
    Serial.println(counter, BIN);

    // Wait for a second before the next count
    delay(1000);
  }
}




