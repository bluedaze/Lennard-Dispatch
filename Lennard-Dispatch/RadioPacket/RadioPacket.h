#ifndef RadioPacket_h
#define RadioPacket_h
#include "Arduino.h"


struct RadioPacket {
    uint8_t FromRadioId;
    char Message[30];
    uint8_t packetNumber;
};

#endif
