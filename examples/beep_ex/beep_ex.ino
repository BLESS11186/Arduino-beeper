#include <Beeper.h>
/* each 5ms update beeper */
#define UPDATE_FREQ 5
/* Use beeper pin with 4, queue size is 5*/
Beeper beep(12, 5);

void setup() {
  // set timer for multiprocessing
  noInterrupts();
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
  interrupts();

  /* beep 200ms & off 100ms */
  beep.push(200, 100);
  beep.push(200, 100);
  beep.push(200, 100);
  beep.push(200, 100);
  beep.push(200, 100);
  delay(5000);
}

/* Update signal */
SIGNAL(TIMER0_COMPA_vect) 
{
  unsigned long currentMillis = millis();
  if(currentMillis % UPDATE_FREQ == 0)
    beep.Update(currentMillis);
} 

void loop() {
}
