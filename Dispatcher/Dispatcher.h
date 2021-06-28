/*
  Dispatcher.h - Library for dispatching messages the radio.
  Created by Sean Pedigo, June 25, 2021.
  Released into the public domain.
*/

#ifndef Dispatcher_h
#define Dispatcher_h

#include "Arduino.h"
#include "RadioPacket.h"
#include <NRFLite.h>

extern NRFLite _radio;
class Dispatcher {

  public:
    uint8_t RADIO_ID;             // Our radio's id.
    uint8_t DESTINATION_RADIO_ID; // Id of the radio we will transmit to.
    int numPackets;
    RadioPacket *packets;
    Dispatcher(uint8_t RADIO_ID, uint8_t DESTINATION_RADIO_ID);
    void broadCast(RadioPacket packets[], int numPackets);
    void sendPacket(RadioPacket packet);
    bool readIO();
    int readline(int readch, char *buffer, int len);
    void createTransmission();
};
#endif
