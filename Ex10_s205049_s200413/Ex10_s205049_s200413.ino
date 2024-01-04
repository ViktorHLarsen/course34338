int led_r = 16;
int led_y = 5;
int led_g = 4;

int adcPin = A0;
int adcRaw = 0;
double voltage = 0;
double temp = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  // pinMode(adcPin,INPUT);
  pinMode(led_g,OUTPUT);
  pinMode(led_y,OUTPUT);
  pinMode(led_r,OUTPUT);
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
  if(temp > 37)
  {
    digitalWrite(led_g,LOW);
    digitalWrite(led_y,LOW);
    digitalWrite(led_r,HIGH);
  }
  else if ((temp > 36) && (temp <= 37))
  {
    digitalWrite(led_g,LOW);
    digitalWrite(led_y,HIGH);
    digitalWrite(led_r,LOW);
  }
  else
  {
    digitalWrite(led_g,HIGH);
    digitalWrite(led_y,LOW);
    digitalWrite(led_r,LOW);
  }

}
