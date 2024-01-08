
uint8_t incomingByte = 0;
int a = 16;    // Red LED gpio 16
int b = 5; // Yellow LED gpio 5
int c = 4;  // Green LED
int e = 14; // d5 gpio 14
int d = 2; // gpio 2
int lsb = 0; // gpio 0


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);


}

  char mychar = '4';
  int val = mychar-'0';
void loop() {
  // put your main code here, to run repeatedly:
  mychar = (char)(val+'A'-1);
  if(Serial.available() > 0)
  {
    incomingByte = Serial.read();
    Serial.print("i received: ");
    Serial.print((char)incomingByte);
    Serial.println();
    Serial.println((char)mychar);
    // resets LEDs
    if(incomingByte != 10) // enter
    {
      digitalWrite(a,LOW);
      digitalWrite(b,LOW);
      digitalWrite(c,LOW);
      digitalWrite(d,LOW);
      digitalWrite(e,LOW);
    }

    switch(incomingByte)
    {
      case 'a':
        digitalWrite(a,HIGH);
        break;
      case 'b':
        digitalWrite(b,HIGH);
        break;
      case 'c':
        digitalWrite(c,HIGH);
        break;
      case 'd':
        digitalWrite(d,HIGH);
        break;
      case 'e':
        digitalWrite(e,HIGH);
        break;  
      default:

        break;
    }
    
  }
  
}
