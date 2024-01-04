
#define red 0
#define green 1
#define blue 2

uint8_t incomingByte = 0;
int r = 5; // green LED gpio 5
int g = 16;    // Red LED gpio 16
int b = 4;  // blue LED
int adcPin = A0;
double adcValue = 0;
int counter = 0;

double r_val = 0;
double g_val = 0;
double b_val = 0;
int adcRaw = 0;
int adcScaled = 0;
int radianer = 0;


int rgb_index = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Serial.setTimeout(1000);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  /* Exercise 7 */
  if(Serial.available() > 0)
  {
    incomingByte = Serial.parseInt();
    Serial.print("i received: ");
    Serial.println(incomingByte);
    if (rgb_index == red)
    {
      analogWrite(r,incomingByte);
    }
    if (rgb_index == green)
    {
      analogWrite(g,incomingByte);
    }
    if (rgb_index == blue)
    {
      analogWrite(b,incomingByte);
    }
    rgb_index++;
    if (rgb_index > 3)
    {
      rgb_index = 0;
    }
    
  }

  /* exercise 8 */
  adcRaw = analogRead(A0);
  adcValue = (double)(adcRaw*3300./1024);


  if (adcRaw <= 341)
  {
    adcScaled = adcRaw*2550/341;
    r_val = 128 - (adcScaled/10);
    g_val = 0;
    b_val = 128 + (adcScaled/10);
  }
  else if ((adcRaw > 341) && (adcRaw < 683))
  {
    adcScaled = (adcRaw-341)*2550/340;
    r_val = 0;
    g_val = adcScaled/10;
    b_val = 255 - (adcScaled/10);
  }
  else if (adcRaw >= 683)
  {
    adcScaled = (adcRaw-683)*2550/340;
    r_val = (adcScaled/10);
    g_val = 255 - (adcScaled/10);
    b_val = 0;
  }

  if(r_val < 0){r_val = 0;}
  if(r_val > 255){r_val = 255;}
  if(g_val < 0){g_val = 0;}
  if(g_val > 255){g_val = 255;}
  if(b_val < 0){b_val = 0;}
  if(b_val > 255){b_val = 255;}


  analogWrite(r,r_val);
  analogWrite(g,g_val);
  analogWrite(b,b_val);

  counter++;
  if (counter == 2000)
  {
    Serial.println(r_val, 3);
    Serial.println(g_val, 3);
    Serial.println(b_val, 3);
    Serial.println("___________");
    counter = 0;
  }
  

  
}
