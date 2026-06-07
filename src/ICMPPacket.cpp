#include "ICMPPacket.h"
#include "Packet.h"
#include <iostream>

ICMPPacket::ICMPPacket()
{
    type = 0;
    code = 0;
}

/*Packet's constructor signature is:
cppPacket(int sPort, int dPort, std::string dIP, std::string sIP, std::string pl, std::string time);
It expects 6 parameters starting with two ints for ports.
But ICMP has no ports so you're only passing 4 parameters. The compiler doesn't know what to do with that.
The fix:
Since ICMP has no ports we just pass 0 for both ports*/

ICMPPacket::ICMPPacket(std::string dIP, std::string sIP, std::string pl, std::string time, int type, int code)
: Packet(0, 0, dIP, sIP, pl, time)
{
    this->type = type;
    this->code = code; 
}

/*Also notice this->type = type. 
We use this-> here because the parameter name type and the member variable name type are the same.
this->type refers to the member variable, type alone refers to the parameter. This avoids confusion.
*/

int ICMPPacket::getType() const
{
    return type;
} 

int ICMPPacket::getCode() const
{
    return code;
}

std::string ICMPPacket::getProtocol() const
{
    return "ICMP";
}

void ICMPPacket::analyze() 
{}

void ICMPPacket::display() const
{
    std::cout << "ICMP Packet" << std::endl;
    std::cout << "Source IP: " << getSourceIP() << std::endl;
    std::cout << "Destination IP: " << getDestinationIP() << std::endl;
    std::cout << "Type: " << getType() << std::endl;
    std::cout << "Code: " << getCode() << std::endl;
}