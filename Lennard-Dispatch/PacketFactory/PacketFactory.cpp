#include "PacketFactory.h"

    RadioPacket* PacketFactory::getPackets(char msg[]) {
      this->msg = msg;
      splitMessage();
      return packets;
    }

    void PacketFactory::advance(String &str, char &c) {
        str+= c;
        count++;
        c = msg[count];
    }

    void PacketFactory::createPacket(String &str) {
        RadioPacket packet{};
        char temp[30];
        strcpy(temp, str.c_str());
        strcpy(packet.Message, temp);
        packet.packetNumber = index;
        packets[index] = packet;
        str = "";
        index++;
    }

    void PacketFactory::splitMessage() {
        String str = "";
        char c = msg[count];
        while (count < strlen(msg) +1) {
            if (c == '\0') {
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
