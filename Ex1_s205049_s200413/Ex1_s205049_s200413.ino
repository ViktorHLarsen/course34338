
#define PAUSE 300
#define MORSE_L 500
#define MORSE_S 100
#define LED_BUILTIN 2

// uint16_t i = 0;

void setup(){
pinMode (LED_BUILTIN, OUTPUT);
Serial.begin(9600);
}

const char ord1[30] = "viktorogjonas";

void loop() {
  morse_word(ord1);
}

/* Function that takes a C string and turns it into morse  */ 
void morse_word(const char * myWord)
{
  uint16_t word_length = 0;
  word_length = strlen(myWord);

  for (uint8_t inc = 0; inc < word_length; inc++)
  {
    ascii_to_morse(myWord[inc]);
  }
  
}

/* function that takes a char and turns it into morse LED beep sequence */
void ascii_to_morse(uint8_t letter)
{
  switch(letter)
  {
    case 'a':
      a();
      break;
    case 'b':
      b();
      break;
    case 'c':
      c();
      break;
    case 'd':
      d();
      break;
    case 'e':
      e();
      break;
    case 'f':
      f();
      break;
    case 'g':
      g();
      break;
    case 'h':
      h();
      break;
    case 'i':
      i();
      break;
    case 'j':
      j();
      break;
    case 'k':
      k();
      break;
    case 'l':
      l();
      break;
    case 'm':
      m();
      break;
    case 'n':
      n();
      break;
    case 'o':
      o();
      break;
    case 'p':
      p();
      break;
    case 'q':
      q();
      break;
    case 'r':
      r();
      break;
    case 's':
      s();
      break;
    case 't':
      t();
      break;
    case 'u':
      u();
      break;
    case 'v':
      v();
      break;
    case 'w':
      w();
      break;
    case 'x':
      x();
      break;
    case 'y':
      y();
      break;
    case 'z':
      z();
      break;
    case '0':
      zero();
      break;
    case '1':
      one();
      break;
    case '2':
      two();
      break;
    case '3':
      three();
      break;
    case '4':
      four();
      break;
    case '5':
      five();
      break;
    case '6':
      six();
      break;
    case '7':
      seven();
      break;
    case '8':
      eight();
      break;
    case '9':
      nine();
      break;
  }
    
}

void blink_l()
{
  digitalWrite(LED_BUILTIN,HIGH);
  delay(MORSE_L);
  digitalWrite (LED_BUILTIN, LOW);
  delay(PAUSE);
}

void blink_s()
{
  digitalWrite(LED_BUILTIN,HIGH);
  delay(MORSE_S);
  digitalWrite (LED_BUILTIN, LOW);
  delay(PAUSE);
}

void a()
{
  blink_s();
  blink_l();
}
void b()
{
  blink_l();
  blink_s();
  blink_s();
  blink_s();
}
void c()
{
  blink_l();
  blink_s();
  blink_l();
  blink_s();
}
void d()
{
  blink_l();
  blink_s();
  blink_s();
}
void e()
{
  blink_s();
}
void f()
{
  blink_s();
  blink_s();
  blink_l();
  blink_s();
}
void g()
{
  blink_l();
  blink_l();
  blink_s();
}
void h()
{
  blink_s();
  blink_s();
  blink_s();
  blink_s();
}
void i()
{
  blink_s();
  blink_s();
}
void j()
{
  blink_s();
  blink_l();
  blink_l();
  blink_l();
}
void k()
{
  blink_l();
  blink_s();
  blink_l();
}
void l()
{
  blink_s();
  blink_l();
  blink_s();
  blink_s();
}
void m()
{
  blink_l();
  blink_l();
}
void n()
{
  blink_l();
  blink_s();
}
void o()
{
  blink_l();
  blink_l();
  blink_l();
}
void p()
{
  blink_s();
  blink_l();
  blink_l();
  blink_s();
}
void q()
{
  blink_l();
  blink_l();
  blink_s();
  blink_l();
}
void r()
{
  blink_s();
  blink_l();
  blink_s();
}
void s()
{
  blink_s();
  blink_s();
  blink_s();
}
void t()
{
  blink_l();
}
void u()
{
  blink_s();
  blink_s();
  blink_l();
}
void v()
{
  blink_s();
  blink_s();
  blink_s();
  blink_l();
}
void w()
{
  blink_s();
  blink_l();
  blink_l();
}
void x()
{
  blink_l();
  blink_s();
  blink_s();
  blink_l();
}
void y()
{
  blink_l();
  blink_s();
  blink_l();
  blink_l();
}
void z()
{
  blink_l();
  blink_l();
  blink_s();
  blink_s();
}
void zero() 
{
  blink_l();
  blink_l();
  blink_l();
  blink_l();
  blink_l();
}
void one() 
{
  blink_s();
  blink_l();
  blink_l();
  blink_l();
  blink_l();
}

void two() 
{
  blink_s();
  blink_s();
  blink_l();
  blink_l();
  blink_l();
}

void three() 
{
  blink_s();
  blink_s();
  blink_s();
  blink_l();
  blink_l();
}

void four() 
{
  blink_s();
  blink_s();
  blink_s();
  blink_s();
  blink_l();
}

void five() 
{
  blink_s();
  blink_s();
  blink_s();
  blink_s();
  blink_s();
}

void six() 
{
  blink_l();
  blink_s();
  blink_s();
  blink_s();
  blink_s();
}

void seven() 
{
  blink_l();
  blink_l();
  blink_s();
  blink_s();
  blink_s();
}

void eight() 
{
  blink_l();
  blink_l();
  blink_l();
  blink_s();
  blink_s();
}

void nine() 
{
  blink_l();
  blink_l();
  blink_l();
  blink_l();
  blink_s();
}
