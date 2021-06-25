/*
  SerialReader.h - Library for reading over the Serial Monitor.
  Created by Sean Pedigo, June 25, 2021.
  Released into the public domain.
*/
#ifndef SerialReader_h
#define SerialReader_h
#include "Arduino.h"
extern char SerialBuffer[160];
class SerialReader {
  public:
    bool readIO();
    int readline(int readch, char *buffer, int len);
};


#endif
