#include "DigiJoystick.h"


const uint8_t PIN_LED = 1;
const uint8_t PIN_A = 0;
const uint8_t PIN_B = 2;
const uint8_t BUTTON_WAIT = 17;  // in milliseconds. 60fps=16.66ms

static uint8_t change_signal = 0;
static uint8_t prev_signal = 0;
static uint8_t button_counter = 0;
static bool direction = true;


void setup() {
  pinMode(PIN_A, INPUT);
  pinMode(PIN_B, INPUT);
  pinMode(PIN_LED, OUTPUT);
  // register setting.
  TIMSK |= (1 << TOIE0);                   // Enable timer interrupts
  TCCR0B |= ((1 << CS00) | (1 << CS01));   // 16.5Mhz/64 prescaling = 257.8Khz = 0.0039ms
  sei();                                   // enable global interrupt.

  // set initial value
  TCNT0 = 0x00;                                        // Timer0: overflow(interrupt) every 0.039ms*256 = about 1ms.
  prev_signal = PINB & ((1 << PIN_A) | (1 << PIN_B));  // PIN inputs.

}


void push_button(bool direction) {
  if (button_counter == 0) {
    if (direction){
      DigiJoystick.setButtons((char)0x01, (char)0x00);
    } else {
      DigiJoystick.setButtons((char)0x02, (char)0x00);
    }
    button_counter = BUTTON_WAIT;
  }
}

void loop() {
  // Unfortunately, Digispark only has one external interrupt and we can't use interrupts on both encoder pins.
  // Also, V-USB devours all pin change interrupts, so we can't use PCINT0_vect too.
  // So we use the classic loop system.
  /* input signal pattern
          positive ->
       <- negative
  PIN_A: 001100110011
  PIN_B: 011001100110

  so matrix is:
   now      prev
   A+B    pos | neg
   0+0 <- 1+0 | 0+1 
   0+1 <- 0+0 | 1+1
   1+0 <- 1+1 | 0+0
   1+1 <- 0+1 | 1+0

  */

  uint8_t signal = PINB & ((1 << PIN_A) | (1 << PIN_B));
  change_signal = signal ^ prev_signal;
  if ( change_signal == 0 ){ // same input.
    return;
  }

  if ( change_signal & ( 1<< PIN_A) ) { // change A
    if ( 
        ( ((prev_signal & (1 << PIN_B)) >> PIN_B ) & 0x01 ) // prev B bit
        ^  ( ((signal & (1 << PIN_A)) >> PIN_A ) & 0x01 )   // now A bit
       ) { // PIN_A flag != prev PIN_B flag = negative
      direction = false;
    } else {
      direction = true;
    }
  } else { //change B
    if (
        ( ((prev_signal & (1 << PIN_A)) >> PIN_A ) & 0x01 ) // prev A bit
        ^  ( ((signal & (1 << PIN_B)) >> PIN_B ) & 0x01 )   // now B bit
       ) { // PIN_B flag != prev PIN_A flag = positive
      direction = true;
    } else {
      direction = false;
    }
  }
  prev_signal = signal;
  push_button(direction);
}


ISR(TIMER0_OVF_vect) {
  // Called every 1ms. (16.5Mhz/64 prescaling = 257.8Khz = 0.0039ms. 0.0039ms * 256 = 1ms)
  if (button_counter) {
    button_counter--;
    digitalWrite(PIN_LED, HIGH); // for debug
  } else {
    DigiJoystick.setButtons((char)0x00, (char)0x00);  // release button 
    digitalWrite(PIN_LED, LOW);
  }
  DigiJoystick.update();

}