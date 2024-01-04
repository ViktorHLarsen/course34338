
uint8_t incomingByte = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    incomingByte = Serial.read();
    Serial.print("i received: ");
    Serial.print((char)incomingByte);
    Serial.println();
  }
}
