/*
  Dispatcher.h - Library for dispatching messages the radio.
  Created by Sean Pedigo, June 25, 2021.
  Released into the public domain.
*/

#include <NRFLite.h>
#include "Arduino.h"
//#define DEBUG
#ifndef debugUtils_H
#define debugUtils_H
      extern NRFLite _radio;
      void serial_debugger();
      void checkRadioConnection();
      void DEBUG_BAUD(long const x);
      #ifdef DEBUG
          #define DEBUG_BAUD(x) Serial.begin(x);
          #define DEBUG_PRINTLN(x) Serial.println(x);
          #define DEBUG_PRINT(x) Serial.print(x);
      #else
          #define DEBUG_BAUD(x);
          #define DEBUG_PRINTLN(x);
          #define DEBUG_PRINT(x);
    
#endif
#endif
