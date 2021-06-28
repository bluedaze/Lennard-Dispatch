#include "common.h"
#include "DebugUtils.h"
#include <SPI.h>
#include "SerialReader.h"
#include "Dispatcher.h"
#include "PacketFactory.h"
unsigned long lastCheck = 1000;
unsigned long count;
Dispatcher dispatcher(1,0);
SerialReader sr;


void setup() {
    DEBUG_BAUD(115200);
    serial_debugger();
    checkRadioConnection();
}

void checkRadio() {
  if (millis() > lastCheck){
    checkRadioConnection();
    lastCheck = millis() + 2000;
  }
}

void loop() {
  checkRadio();
  PacketFactory packetFactory;
  if (sr.readIO()) {
      DEBUG_PRINT("You entered: >");
      DEBUG_PRINT(SerialBuffer);
      DEBUG_PRINTLN("<\n");
      RadioPacket* packets = packetFactory.getPackets(SerialBuffer);
      int numPackets = packetFactory.index;
      dispatcher.broadCast(packets, numPackets);
  }
}
