#ifndef __BEEPER_h
#define __BEEPER_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define QUEUE_DEFAULT_MAX_LEN 50

class Queue
{
    private:
        unsigned long *queue;
        int top;
        int bottom;
        int s;
        int max_len;

    public:
        Queue(int max_len);
        int getSize();
        bool isEmpty();
        bool push(unsigned long v);
        unsigned long pop();
};

class Beeper
{
    private:
        int beepPin;      
        unsigned long OnTime;     // milliseconds of on-time
        unsigned long OffTime;    // milliseconds of off-time
        Queue *OnTimeQueue;
        Queue *OffTimeQueue;
    
        // These maintain the current state
        volatile int state;                     // ledState used to set the LED
        volatile unsigned long previousMillis;      // will store last time LED was updated
 
  // Constructor - creates a Flasher 
  // and initializes the member variables and state
    public:
        Beeper(int pin, int max_len = QUEUE_DEFAULT_MAX_LEN);

        void push(unsigned long ontime, unsigned long offtime);
        
        void Update(unsigned long currentMillis);
};

#endif