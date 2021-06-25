/*
Basic_RX.ino
Leonardo

Demonstrates simple RX and TX operation.
Any of the Basic_TX examples can be used as a transmitter.
Please read through 'NRFLite.h' for a description of all the methods available in the library.

Radio    Arduino
CE    -> 9
CSN   -> 10 (Hardware SPI SS)
MOSI  -> 11 (Hardware SPI MOSI)
MISO  -> 12 (Hardware SPI MISO)
SCK   -> 13 (Hardware SPI SCK)
IRQ   -> No connection
VCC   -> No more than 3.6 volts
GND   -> GND

*/

#include <SPI.h>
#include <NRFLite.h>

const static uint8_t RADIO_ID = 0;       // Our radio's id.  The transmitter will send to this id.
const static uint8_t PIN_RADIO_CE = 11;
const static uint8_t PIN_RADIO_CSN = 12;
int count = 0;
char buf[80];
int lastCheck = 1000;
struct RadioPacket {
    uint8_t FromRadioId;
    char Message[30];
    uint8_t packetNumber;
};

NRFLite _radio;
RadioPacket _radioData;

void setup()
{
    Serial.begin(115200);
    while(!Serial){
      
    }
    Serial.println("Intializing");
    checkRadioConnection();
}

void checkRadioConnection(){
    bool hasConnection = false;
    while(hasConnection == false){
      count++;
      Serial.println();
      Serial.print("Loop Number: ");
      Serial.println(count);
      Serial.println("Checking radio connection...");
      if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)){
        Serial.println("Cannot communicate with radio");
      } else {
        hasConnection = true;
        Serial.println("Has a connection, starting program");
      }
    }
}

void checkRadio(){
  if (millis() > lastCheck){
    Serial.println(_radio.hasData());
    Serial.println("Ping");
    lastCheck = millis() + 1500;
  }
}

void loop() {
    checkRadio();
    uint32_t packetSize = _radio.hasData();
    if (packetSize == sizeof(RadioPacket)) {
        _radio.readData(&_radioData);

        String msg = String(_radioData.Message);

        Serial.print("Received '");
        Serial.print(msg);
        Serial.print("' from radio ");
        Serial.println(_radioData.FromRadioId);
    }
}
