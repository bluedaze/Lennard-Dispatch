#include "Dispatcher.h"
#include "DebugUtils.h"

    Dispatcher::Dispatcher(uint8_t RADIO_ID, uint8_t DESTINATION_RADIO_ID) {
      this->RADIO_ID = RADIO_ID;
      this->DESTINATION_RADIO_ID = DESTINATION_RADIO_ID;
    }

    void Dispatcher::broadCast(RadioPacket packets[], int numPackets){
      DEBUG_PRINTLN("Sending packets");
      this->packets = packets;
      this->numPackets = numPackets;
      createTransmission();
    }

    void Dispatcher::sendPacket(RadioPacket packet) {
        DEBUG_PRINT("\tSize of radio data: ");
        DEBUG_PRINTLN(sizeof(packet));
        if (_radio.send(DESTINATION_RADIO_ID, &packet, sizeof(packet), NRFLite::NO_ACK)) {
            DEBUG_PRINT("\t...Success");
        } else {   
            DEBUG_PRINT("\t...Failed");
        }
        DEBUG_PRINTLN();
    }

    void Dispatcher::createTransmission() {
      for(int i = 0; i < numPackets; i++) {
        RadioPacket packet = packets[i];
        packet.FromRadioId = RADIO_ID;
        DEBUG_PRINT("\tSending packet ");
        DEBUG_PRINT(i+1);
        DEBUG_PRINT(" of ");
        DEBUG_PRINT(numPackets);
        DEBUG_PRINTLN(".");
        DEBUG_PRINT("\tPacket contents: \"");
        DEBUG_PRINT(packet.Message);
        DEBUG_PRINTLN("\"");
        sendPacket(packet);
        }
    }
