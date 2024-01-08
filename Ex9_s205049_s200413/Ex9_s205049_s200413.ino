
int adcPin = A0;
int adcRaw = 0;
double voltage = 0;
double temp = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  // pinMode(adcPin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  adcRaw = analogRead(adcPin);
  voltage = adcRaw*3270/1024;
  temp = ((voltage-100)/10)-40;
  delay(500);
  Serial.print("Temperature value is: ");
  Serial.print(temp);
  Serial.println("°C");
  Serial.print("voltage value is: ");
  Serial.print(voltage);
  Serial.println("mV");
  Serial.println("_____________________");
}
