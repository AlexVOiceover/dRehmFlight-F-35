//Arduino/Teensy Flight Controller - dRehmFlight
//Author: Nicholas Rehm
//Project Start: 1/6/2020
//Version: Beta 1.2

//========================================================================================================================//

//This file contains all necessary functions and code used for radio communication to avoid cluttering the main code

#include <Arduino.h>

//External pin definitions from main.cpp (COMMENTED for SBUS setup)
/*
extern int ch1Pin; //throttle
extern int ch2Pin; //ail
extern int ch3Pin; //ele
extern int ch4Pin; //rudd
extern int ch5Pin; //gear
extern int ch6Pin; //aux1
*/

//PWM variables (COMMENTED for SBUS setup)
/*
unsigned long rising_edge_start_1, rising_edge_start_2, rising_edge_start_3, rising_edge_start_4, rising_edge_start_5, rising_edge_start_6; 
unsigned long channel_1_raw, channel_2_raw, channel_3_raw, channel_4_raw, channel_5_raw, channel_6_raw;

//Function declarations
void getCh1();
void getCh2();
void getCh3();
void getCh4();
void getCh5();
void getCh6();
*/

//SBUS variables and setup
#if defined USE_SBUS_RX
  #include "SBUS.h"
  SBUS sbus(Serial5);
  uint16_t sbusChannels[16];
  bool sbusFailSafe;
  bool sbusLostFrame;
#endif
void radioSetup() {
  #if defined USE_SBUS_RX
    //SBUS Receiver Setup
    sbus.begin();
  #else
    //PWM Receiver Setup (COMMENTED - uncomment to revert to PWM)
    /*
    //Declare interrupt pins 
    pinMode(ch1Pin, INPUT_PULLUP);
    pinMode(ch2Pin, INPUT_PULLUP);
    pinMode(ch3Pin, INPUT_PULLUP);
    pinMode(ch4Pin, INPUT_PULLUP);
    pinMode(ch5Pin, INPUT_PULLUP);
    pinMode(ch6Pin, INPUT_PULLUP);
    delay(20);
    //Attach interrupt and point to corresponding ISR functions
    attachInterrupt(digitalPinToInterrupt(ch1Pin), getCh1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ch2Pin), getCh2, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ch3Pin), getCh3, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ch4Pin), getCh4, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ch5Pin), getCh5, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ch6Pin), getCh6, CHANGE);
    delay(20);
    */
  #endif
}

unsigned long getRadioPWM(int ch_num) {
  //DESCRIPTION: Get current radio commands (SBUS or PWM)
  unsigned long returnPWM = 1500; //default failsafe value
  
  #if defined USE_SBUS_RX
    //SBUS: Read from SBUS channels (converted to PWM-like values)
    if (ch_num >= 1 && ch_num <= 6) {
      //SBUS scaling: typical range 172-1811, convert to 1000-2000
      float scale = 0.615;
      float bias = 895.0;
      returnPWM = sbusChannels[ch_num-1] * scale + bias;
    }
  #else
    //PWM: Get from interrupt routines (COMMENTED for SBUS setup)
    /*
    if (ch_num == 1) {
      returnPWM = channel_1_raw;
    }
    else if (ch_num == 2) {
      returnPWM = channel_2_raw;
    }
    else if (ch_num == 3) {
      returnPWM = channel_3_raw;
    }
    else if (ch_num == 4) {
      returnPWM = channel_4_raw;
    }
    else if (ch_num == 5) {
      returnPWM = channel_5_raw;
    }
    else if (ch_num == 6) {
      returnPWM = channel_6_raw;
    }
    */
  #endif
  
  return returnPWM;
}



//========================================================================================================================//



//INTERRUPT SERVICE ROUTINES (for reading PWM - COMMENTED for SBUS setup)
/*
void getCh1() {
  int trigger = digitalRead(ch1Pin);
  if(trigger == 1) {
    rising_edge_start_1 = micros();
  }
  else if(trigger == 0) {
    channel_1_raw = micros() - rising_edge_start_1;
  }
}

void getCh2() {
  int trigger = digitalRead(ch2Pin);
  if(trigger == 1) {
    rising_edge_start_2 = micros();
  }
  else if(trigger == 0) {
    channel_2_raw = micros() - rising_edge_start_2;
  }
}

void getCh3() {
  int trigger = digitalRead(ch3Pin);
  if(trigger == 1) {
    rising_edge_start_3 = micros();
  }
  else if(trigger == 0) {
    channel_3_raw = micros() - rising_edge_start_3;
  }
}

void getCh4() {
  int trigger = digitalRead(ch4Pin);
  if(trigger == 1) {
    rising_edge_start_4 = micros();
  }
  else if(trigger == 0) {
    channel_4_raw = micros() - rising_edge_start_4;
  }
}

void getCh5() {
  int trigger = digitalRead(ch5Pin);
  if(trigger == 1) {
    rising_edge_start_5 = micros();
  }
  else if(trigger == 0) {
    channel_5_raw = micros() - rising_edge_start_5;
  }
}

void getCh6() {
  int trigger = digitalRead(ch6Pin);
  if(trigger == 1) {
    rising_edge_start_6 = micros();
  }
  else if(trigger == 0) {
    channel_6_raw = micros() - rising_edge_start_6;
  }
}
*/
