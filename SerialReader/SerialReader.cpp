#include "SerialReader.h"
char SerialBuffer[160];


bool SerialReader::readIO() {
    if (readline(Serial.read(), SerialBuffer, 160) > 0) {
      return true;
    } else {
      return false;
    }
}

int SerialReader::readline(int readch, char *buffer, int len) {
    static int pos = 0;
    int rpos;

    if (readch > 0) {
      switch(readch) {
        case '\r': // ignore CR
          break;
        case '\n':
          rpos = pos;
          pos = 0; // reset position index ready for next time
          return rpos;
        default:
          if (pos < len-1) {
            buffer[pos++] = readch;
            buffer[pos] = 0;
          }
        }
      }
      return 0;
     }
