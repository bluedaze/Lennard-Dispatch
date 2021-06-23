#include <SPI.h>
#include <NRFLite.h>
char buf[160];
int count = 1;
const static uint8_t RADIO_ID = 1;             // Our radio's id.
const static uint8_t DESTINATION_RADIO_ID = 0; // Id of the radio we will transmit to.
const static uint8_t PIN_RADIO_CE = 9;
const static uint8_t PIN_RADIO_CSN = 10;
int lastCheck = 1000;
struct RadioPacket
{
    uint8_t FromRadioId;
    char Message[30];
    uint8_t packetNumber;
};
struct dispatch {
    RadioPacket packets[80];
};

NRFLite _radio;

int readline(int readch, char *buffer, int len){
  static int pos = 0;
  int rpos;

  if (readch > 0){
//    Serial.println(readch);
    switch (readch){
      case '\r': // ignore CR
        break;
      case '\n':
        rpos = pos;
        pos = 0; // reset position index ready for next time
        return rpos;
      default:
        if (pos < len-1){
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
    }
  }
  return 0;
}

void setup()
{
    Serial.begin(115200);
    
    // By default, 'init' configures the radio to use a 2MBPS bitrate on channel 100 (channels 0-125 are valid).
    // Both the RX and TX radios must have the same bitrate and channel to communicate with each other.
    // You can run the 'ChannelScanner' example to help select the best channel for your environment.
    // You can assign a different bitrate and channel as shown below.
    //   _radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE2MBPS, 100) // THE DEFAULT
    //   _radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE1MBPS, 75)
    //   _radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE250KBPS, 0)
    if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)){
        Serial.println("Cannot communicate with radio");
        while (1); // Wait here forever.
    }

    while(!Serial){
      
    }
    Serial.println("Starting...");
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
        Serial.println("ConnectionStatus: True");
        Serial.println();
      }
    delay(500);
    }
    hasConnection = false;
}


class Dispatcher {
public:
    int index = 0;
    int count = 0;

    char *msg;
    RadioPacket packets[80];

    Dispatcher(char msg[]) {
        this->msg = msg;
        splitMessage();
    }

    void advance(String &str, char &c){
        str+= c;
        count++;
        c = msg[count];
    }

    void createPacket(String &str){
        RadioPacket packet{};
        char temp[30];
        strcpy(temp, str.c_str());
        strcpy(packet.Message, temp);
        packet.packetNumber = index;
        packets[index] = packet;
        str = "";
        index++;
    }

    void splitMessage() {
        String str = "";
        char c = msg[count];
        while (count < strlen(msg) +1) {
            if (c == '\0'){
                createPacket(str);
                break;
            }
            else if ((count % 29 != 0 || count == 0)) {
                advance(str, c);
            } else {
                createPacket(str);
                advance(str, c);
            }
        }
    }
};

void createTransmission(){
    Serial.println();
    Serial.println("User Input:");
    Serial.print("\t>");
    Serial.print(buf);
    Serial.println("<");
    Serial.println();
    Serial.print("\tLength of string: ");
    Serial.println(strlen(buf));
    Serial.println();
    Dispatcher dispatcher(buf);
    for(int i = 0; i < dispatcher.index; i++) {
      RadioPacket packet = dispatcher.packets[i];
      packet.FromRadioId = RADIO_ID;
      Serial.print("\tSending packet ");
      Serial.print(i+1);
      Serial.print(" of ");
      Serial.print(dispatcher.index);
      Serial.println(".");
      Serial.print("\tPacket contents: ");
      Serial.print("\"");
      Serial.print(packet.Message);
      Serial.print("\"");
      Serial.println();
      sendPacket(packet);
    }
}

void sendPacket(RadioPacket packet) {
    if (_radio.send(DESTINATION_RADIO_ID, &packet, sizeof(packet)), NRFLite::NO_ACK) {
        Serial.println("\t...Success");
        Serial.println();
    } else {   
        Serial.print("\tSize of radio data: ");
        Serial.println(sizeof(packet));
        Serial.println("\t...Failed");
        Serial.println();
    }
}

void checkRadio(){
//  Serial.println("Function: sendPing()");
  if (millis() > lastCheck){
    checkRadioConnection();
    lastCheck = millis() + 10000;
  }
}

void loop()
{
  if(readline(Serial.read(), buf, 160) > 0) {
    createTransmission();
  }
  checkRadio();
}
