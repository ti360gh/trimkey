#include <DigiJoystick.h>

const unsigned char PIN_LED = 1;
const unsigned char PIN_A = 0;
const unsigned char PIN_B = 2;
const unsigned char BUTTON_WAIT = 5;  // in milliseconds.

static unsigned char prev_signal = 0;
static unsigned char signal = 0;
static unsigned char button_counter = 0;

void setup() {
  pinMode(PIN_A, INPUT);
  pinMode(PIN_B, INPUT);
  pinMode(PIN_LED, OUTPUT);
  // register setting.
  PCMSK |= ((1 << PIN_A) | (1 << PIN_B));  // Enable encoder pins interrupt sources
  GIMSK |= (1 << PCIE);                    // Enable pin change interupts
  TIMSK |= (1 << TOIE0);                   // Enable timer interrupts
  TCCR0B |= ((1 << CS00) | (1 << CS01));   // 16.5Mhz/64 prescaling = 257.8Khz = 0.0039ms
  sei();                                   // enable global interrupt.

  // set initial value
  TCNT0 = 0x00;                                        // Timer0: overflow(interrupt) every 0.039ms*256 = about 1ms.
  prev_signal = PINB & ((1 << PIN_A) | (1 << PIN_B));  // PIN inputs.
  attachInterrupt(PCINT0, intHandler, CHANGE);
}


void loop() {
  // do nothing.
}

void push_button(char button) {
  if (button_counter == 0) {
    DigiJoystick.setButtons(button, (char)0x00);
    button_counter = BUTTON_WAIT;
  }
}


void intHandler() {
  // PinChangeINTerrupt
  /* input signal pattern is:
          positive ->
  PIN_A: 001100110011
  PIN_B: 011001100110
         <- negative

  so matrix is:
   now      prev
   A+B    pos | neg
   0+1 <- 0+0 | 1+1
   1+1 <- 0+1 | 1+0
   0+0 <- 1+0 | 0+1 
   1+0 <- 1+1 | 0+0
  */

  signal = PINB & ((1 << PIN_A) | (1 << PIN_B));
  switch (signal & (1 << PIN_A)) {  //PIN_A
    case 0:
      if (signal & (1 << PIN_B)) {  //PIN_B
        push_button((char)0x02);
      } else {
        push_button((char)0x01);
      }
      break;
    case 1:
      if (signal & (1 << PIN_B)) {  //PIN_B
        push_button((char)0x01);
      } else {
        push_button((char)0x02);
      }
      break;
  }
}

ISR(TIMER0_OVF_vect) {
  // Called every 1ms. (16.5Mhz/64 prescaling = 257.8Khz = 0.0039ms. 0.0039ms * 256 = 1ms)
  if (button_counter) {
    button_counter--;
    digitalWrite(PIN_LED, HIGH); // for debug.
  } else {
    DigiJoystick.setButtons((char)0x00, (char)0x00);  // button release.
    digitalWrite(PIN_LED, LOW);
  }
  DigiJoystick.update();
}