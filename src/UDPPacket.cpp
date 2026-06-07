#include "UDPPacket.h"
#include "Packet.h"
#include <iostream>

UDPPacket::UDPPacket()
{
    length = 0;
}

UDPPacket::UDPPacket(int sPort, int dPort, std::string dIP, std::string sIP, std::string pl, std::string time, int len)
: Packet(sPort, dPort, dIP, sIP, pl, time)
{
    length = len;
}

int UDPPacket::getLength() const
{
    return length;
}

std::string UDPPacket::getProtocol() const
{
    return "UDP";
}

void UDPPacket::analyze() 
{}

void UDPPacket::display() const
{
    std::cout << "UDP Packet" << std::endl;
    std::cout << "Source IP: " << getSourceIP() << std::endl;
    std::cout << "Destination IP: " << getDestinationIP() << std::endl;
    std::cout << "Source Port: " << getSourcePort() << std::endl;
    std::cout << "Dest Port: " << getDestinationPort() << std::endl;
    std::cout << "Length: " << length << std::endl;
}
