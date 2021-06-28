/*
  PacketFactory.h - Library for splitting and creating radio packets
  Created by Sean Pedigo, June 25, 2021.
  Released into the public domain.
*/
#ifndef PacketFactory_h
#define PacketFactory_h
#include "Arduino.h"
#include "RadioPacket.h" 

class PacketFactory {
  public:
    int index = 0;
    int count = 0;

    char *msg;
    RadioPacket packets[80];
    RadioPacket* getPackets(char msg[]);
    void advance(String &str, char &c);
    void createPacket(String &str);
    void splitMessage();
    
};

#endif
