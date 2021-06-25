#include "Dispatcher.h"
NRFLite _radio;

    Dispatcher::Dispatcher(uint8_t RADIO_ID, uint8_t DESTINATION_RADIO_ID) {
      this->RADIO_ID = RADIO_ID;
      this->DESTINATION_RADIO_ID = DESTINATION_RADIO_ID;
    }

    void Dispatcher::broadCast(RadioPacket packets[], int numPackets){
      Serial.println("Sending packets");
      this->packets = packets;
      this->numPackets = numPackets;
      createTransmission();
    }

    void Dispatcher::sendPacket(RadioPacket packet) {
        Serial.print("\tSize of radio data: ");
        Serial.println(sizeof(packet));
        if (_radio.send(DESTINATION_RADIO_ID, &packet, sizeof(packet), NRFLite::NO_ACK)) {
            Serial.println("\t...Success");
        } else {   
            Serial.println("\t...Failed");
        }
        Serial.println();
    }

    void Dispatcher::createTransmission() {
      for(int i = 0; i < numPackets; i++) {
        RadioPacket packet = packets[i];
        packet.FromRadioId = RADIO_ID;
        Serial.print("\tSending packet ");
        Serial.print(i+1);
        Serial.print(" of ");
        Serial.print(numPackets);
        Serial.println(".");
        Serial.print("\tPacket contents: \"");
        Serial.print(packet.Message);
        Serial.println("\"");
        sendPacket(packet);
        }
    }

