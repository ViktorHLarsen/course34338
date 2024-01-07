int led_r = 16;
int led_y = 5;
int led_g = 4;

int adcPin = A0;
int adcRaw = 0;
double voltage = 0;
double temp = 0;
double tempavg = 0;
uint8_t warning = 0;


#include  <Wire.h>
#include "LiquidCrystal_I2C.h"

//initialize the liquid crystal library
//the first parameter is  the I2C address
//the second parameter is how many rows are on your screen
//the  third parameter is how many columns are on your screen
LiquidCrystal_I2C lcd(0x27,  16, 2);

void setup() {
  // put your setup code here, to run once:
  //initialize lcd screen
  lcd.init();
  // turn on the backlight
  lcd.backlight();

  Serial.begin(115200);
  // pinMode(adcPin,INPUT);
  // pinMode(led_g,OUTPUT);
  // pinMode(led_y,OUTPUT);
  // pinMode(led_r,OUTPUT);

  lcd.setCursor(0,0);
  // tell the screen to write “hello, from” on the top  row
  lcd.print("Temperature is:");
}

void loop() {
  // put your main code here, to run repeatedly:
  adcRaw = analogRead(adcPin);
  voltage = adcRaw*3270/1024;
  temp = ((voltage-100)/10)-40;
  delay(50);
  for (int i = 0; i < 10; i++)
  {
    tempavg = 0.9*tempavg + 0.1*temp; // moving average filter
  }

  lcd.setCursor(0,0);
  lcd.print("Temperature is:");
  if (tempavg > 37.5)
  {
    if(warning == 1)
    {
      lcd.clear();
      warning = 0;
    }
    lcd.setCursor(0,1);
    lcd.print("WARNING: HOT!");
  }
  else
  {
    if(warning == 0)
    {
      lcd.clear();
      warning = 1;
    }
    lcd.setCursor(3,1);
    lcd.print(tempavg);
    lcd.setCursor(10,1);
    lcd.print("degC");
  }

  // tell the screen to write “Arduino_uno_guy”  on the bottom row
  // you can change whats in the quotes to be what you want  it to be!


  Serial.print("Temperature value is: ");
  Serial.print(tempavg);
  Serial.println("°C");
  Serial.print("voltage value is: ");
  Serial.print(voltage);
  Serial.println("mV");
  Serial.println("_____________________");
  // if(temp > 37)
  // {
  //   digitalWrite(led_g,LOW);
  //   digitalWrite(led_y,LOW);
  //   digitalWrite(led_r,HIGH);
  // }
  // else if ((temp > 36) && (temp <= 37))
  // {
  //   digitalWrite(led_g,LOW);
  //   digitalWrite(led_y,HIGH);
  //   digitalWrite(led_r,LOW);
  // }
  // else
  // {
  //   digitalWrite(led_g,HIGH);
  //   digitalWrite(led_y,LOW);
  //   digitalWrite(led_r,LOW);
  // }

}
