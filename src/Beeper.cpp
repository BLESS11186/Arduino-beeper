#include "Beeper.h"

#define WAIT -1

Queue::Queue(int max_len){
  top = 0;
  bottom = 0;
  s = 0;
  this->max_len = max_len;
  queue = new unsigned long[max_len];
}
int Queue::getSize(){
  return s;
}
bool Queue::isEmpty(){
  return s==0;
}
bool Queue::push(unsigned long v){
  if(s >= max_len) return false;
  queue[bottom++] = v;
  if(bottom == max_len) bottom = 0;
  s++;
  return true;
}
unsigned long Queue::pop(){
  if(isEmpty()) return 0;
  long ret = queue[top++];
  if(top == max_len) top = 0;
  s--;
  return ret;
}



Beeper::Beeper(int pin, int max_len = QUEUE_DEFAULT_MAX_LEN)
{
  beepPin = pin;
  pinMode(beepPin, OUTPUT);
  digitalWrite(beepPin, LOW);
    
  OnTime = 0;
  OffTime = 0;
  
  state = WAIT; 
  previousMillis = 0;

  OnTimeQueue = new Queue(max_len);
  OffTimeQueue = new Queue(max_len);
}

void Beeper::push(unsigned long ontime, unsigned long offtime)
{
  noInterrupts();
  OnTimeQueue->push(ontime);
  OffTimeQueue->push(offtime);
  interrupts();
}

void Beeper::Update(unsigned long currentMillis)
{
  /*
    *  state
    *  WAIT -> HIGH -> LOW -> WAIT
    *      pop     onT      offT
    *       ========>
    *       onT = 0
    *             ===========>
    *                offT = 0
    */
  switch (state)
  {
  case WAIT:
    if(OnTimeQueue->isEmpty()){
      break;
    }
    OnTime = OnTimeQueue->pop();
    OffTime = OffTimeQueue->pop();
    if(OnTime == 0)
      state = LOW; // WAIT -> LOW
    else{
      state = HIGH;  // WAIT->HIGH
      digitalWrite(beepPin, HIGH);
    }
    previousMillis = currentMillis;
    break;
  
  case HIGH:
    if(currentMillis - previousMillis >= OnTime){
      digitalWrite(beepPin, LOW);
      if(OffTime == 0)
        state = WAIT; // HIGH -> WAIT
      else
        state = LOW;  // WAIT->LOW
      previousMillis = currentMillis;
    }
    break;
  
  case LOW:
    if(currentMillis - previousMillis >= OffTime){
      state = WAIT;
      previousMillis = currentMillis;
    }
    break;

  default:
    break;
  }
}