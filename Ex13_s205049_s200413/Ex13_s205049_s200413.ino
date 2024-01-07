#define red_l2 2
#define red_l1 0
#define green 4
#define red_r1 5
#define red_r2 16
#define button 14
#define activeLow 0

uint8_t diodes[5] = {0};
uint8_t i = 0;
uint8_t buttonState = 0;
uint16_t count = 0;
uint8_t flashIntegrator = 0;
uint16_t buttonIntegrator = 0;
uint8_t success = 0;
uint8_t fail = 0;
uint16_t speed = 0;

typedef enum{
  l2 = 0,
  l1,
  g,
  r1,
  r2,
  number_of_LEDs
}diode;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(red_l2, OUTPUT);
  pinMode(red_l1, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red_r1, OUTPUT);
  pinMode(red_r2, OUTPUT);

  pinMode(button, INPUT);

  diodes[l2] = red_l2;
  diodes[l1] = red_l1;
  diodes[g] = green;
  diodes[r1] = red_r1;
  diodes[r2] = red_r2;
}

void loop() {
  // put your main code here, to run repeatedly:
  levelDetect();

  if (count % speed == 0) // change LED every 50 ms
  {
    if ((flashIntegrator >= 10))
    {
      if(success < 8)
      {
        i++;
        if (i >= number_of_LEDs)
        {
          i = 0;
        }
        changeLED();
      }
      else if(success >= 8)
      {
        changeLEDrandom();
      }
    }
    else
    {
      if(flashIntegrator == 1)
      {
        success++;
        Serial.println("SUCCESS!");
        Serial.print("Number of success: ");
        Serial.println(success);
      }
      flashLED();
      flashIntegrator++;
    }
  }
  if (count%5 == 0) // read button every 5ms
  {
    buttonState = digitalRead(button);

    if (buttonState == activeLow) // external 1k pullup
    {
      buttonIntegrator++;
      if (buttonIntegrator < 2)
      {
        Serial.println("Button is pressed!");
      }
      if((i == g) && (buttonIntegrator < 40)) // ignore if holding button
      {
        
        flashIntegrator = 0;
      }
      else if ((i != g) && (buttonIntegrator > 5) && (buttonIntegrator < 40))
      {
        digitalWrite(red_r2,LOW);
        digitalWrite(red_r1,LOW);
        digitalWrite(green,LOW);
        digitalWrite(red_l1,LOW);
        digitalWrite(red_l2,LOW);
        success = 0;
        Serial.println("FAIL!");
        Serial.print("Number of success: ");
        Serial.println(success);
        delay(1000);
      }
      if (buttonIntegrator > 100) // 500ms
      {
        if (buttonIntegrator < 50001) // message user that button is being held down
        {
          Serial.println("Button is being hold");
        }
        buttonIntegrator = 50001;
      }
    }
    else
    {
      buttonIntegrator = 0; // reset integrator
    }
  }
  



  count++;
  delay(1);
}

void changeLED()
{
  // delay(200);
  if (i == 0)
  {
    digitalWrite(diodes[r2],LOW);
  }
  else
  {
    digitalWrite(diodes[i-1],LOW);
  }
  digitalWrite(diodes[i],HIGH);
  // delay(200);
}

void changeLEDrandom()
{
  static uint8_t lastLED = 0;
  i = random(5);
  digitalWrite(diodes[lastLED],LOW);
  digitalWrite(diodes[i],HIGH);
  lastLED = i;
  // delay(200);
}

void flashLED()
{
  static uint8_t flip = 0;
  if (flip == 0)
  {
    digitalWrite(red_r2,HIGH);
    digitalWrite(red_r1,HIGH);
    digitalWrite(green,HIGH);
    digitalWrite(red_l1,HIGH);
    digitalWrite(red_l2,HIGH);
    flip = 1;
  }
  else
  {
    digitalWrite(red_r2,LOW);
    digitalWrite(red_r1,LOW);
    digitalWrite(green,LOW);
    digitalWrite(red_l1,LOW);
    digitalWrite(red_l2,LOW);
    flip = 0;
  }

}

void levelDetect()
{
  switch(success)
  {
    case 0:
      speed = 500;
      break;
    case 1:
      speed = 450;
      break;
    case 2:
      speed = 400;
      break;
    case 3:
      speed = 350;
      break;
    case 4:
      speed = 300;
      break;
    case 5:
      speed = 250;
      break;
    case 6:
      speed = 200;
      break;
    case 7:
      speed = 150;
      break;
    case 8: // random pattern
      speed = 150;
      break;
    case 9: // random pattern
      speed = 100;
      break;
    case 10:
      speed = 10000;
      break;      
  }
}
