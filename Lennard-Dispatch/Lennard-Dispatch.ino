#include <SPI.h>
#include <NRFLite.h>
#include <SerialReader.h>
#include <Dispatcher.h>
#include <PacketFactory.h>
int count = 0;
const static uint8_t RADIO_ID = 1;             // Our radio's id.
const static uint8_t DESTINATION_RADIO_ID = 0; // Id of the radio we will transmit to.
const static uint8_t PIN_RADIO_CE = 9;
const static uint8_t PIN_RADIO_CSN = 10;
int lastCheck = 1000;


SerialReader sr;

void setup() {
    Serial.begin(115200);
    while(!Serial) {   }
    Serial.println("Starting...");
    checkRadioConnection();
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
      } else {
        hasConnection = true;
        Serial.println("ConnectionStatus: True");
        Serial.println();
      }
    }
    hasConnection = false;
}


void checkRadio() {
  if (millis() > lastCheck){
    checkRadioConnection();
    lastCheck = millis() + 5000;
  }
}



Dispatcher dispatcher(1,0);
void loop() {
  PacketFactory packetFactory;
  if (sr.readIO()) {
      Serial.print("You entered: >");
      Serial.print(SerialBuffer);
      Serial.println("<\n");
      RadioPacket* packets = packetFactory.getPackets(SerialBuffer);
      int numPackets = packetFactory.index;
      dispatcher.broadCast(packets, numPackets);
  }
}
