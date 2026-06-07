#ifndef TCPPACKET_H
#define TCPPACKET_H
#include "Packet.h"

class TCPPacket : public Packet
{
    private:
        int flags;
        bool isSYN;
        bool isACK;
        bool isFIN;
        int windowSize;

    public:
        TCPPacket();
        TCPPacket (int sPort, int dPort, std::string dIP, std::string sIP, std::string pl, std::string time, 
                     int f, bool syn, bool ack, bool fin, int wSize);
        int getFlags() const;
        bool getACK() const;
        bool getSYN() const;
        int getWindowSize() const;
        bool getFIN() const;

        std::string getProtocol() const override;
        void analyze() override;
        void display() const override;
};
#endif