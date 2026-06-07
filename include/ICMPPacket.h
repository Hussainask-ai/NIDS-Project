#ifndef ICMPPACKET_H
#define ICMPPACKET_H
#include "Packet.h"

class ICMPPacket : public Packet
{
    private:
    int type;
    int code;

    public:
    ICMPPacket();
    ICMPPacket(std::string dIP, std::string sIP, std::string pl, std::string time, int type, int code);
    //ICMP has no concept of ports. So remove sPort and dPort from the parameterized constructor.
    int getType() const;
    int getCode() const;

    std::string getProtocol() const override;
    void analyze() override;
    void display() const override;
};




#endif