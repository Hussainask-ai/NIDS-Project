#ifndef UDPPACKET_H
#define UDPPACKET_H
#include "Packet.h"

class UDPPacket : public Packet 
{
    private:
        int length;

    public:
    UDPPacket();
    UDPPacket(int sPort, int dPort, std::string dIP, std::string sIP, std::string pl, std::string time, int len);
    int getLength() const;
    
    std::string getProtocol() const override;
    void analyze() override;
    void display() const override;
};

#endif