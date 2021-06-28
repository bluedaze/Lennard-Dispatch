#include "DebugUtils.h"
extern uint8_t RADIO_ID = 1;             // Our radio's id.
extern uint8_t DESTINATION_RADIO_ID = 0; // Id of the radio we will transmit to.
extern uint8_t PIN_RADIO_CE = 9;
extern uint8_t PIN_RADIO_CSN = 10;
extern unsigned long count;
#ifdef DEBUG

    void serial_debugger(){
        while(!Serial) {   }
        Serial.println("Starting...");
    }

    void checkRadioConnection() {
        bool hasConnection = false;
        while(hasConnection == false) {
          count++;
          Serial.println();
          Serial.print("Loop Number: ");
          Serial.println(count);
          Serial.println("Checking radio connection...");
          if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)) {
            Serial.println("Cannot communicate with radio");
          }
          else {
            hasConnection = true;
            Serial.println("ConnectionStatus: True");
            Serial.println();
          }
        }
        hasConnection = false;
    }

#else

     
      void serial_debugger(){}
      
      void checkRadioConnection(){
          if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
          {
      
          }
      }

#endif
