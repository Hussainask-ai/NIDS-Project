#include "TCPPacket.h"
#include "Packet.h"
#include <iostream>

TCPPacket::TCPPacket()
{
    flags = 0;
    isSYN = false;
    isACK = false;
    isFIN = false;
    windowSize = 0;
}

TCPPacket::TCPPacket (int sPort, int dPort, std::string dIP, std::string sIP, std::string pl, std::string time, 
                     int f, bool syn, bool ack, bool fin, int wSize)
        : Packet(sPort, dPort, dIP, sIP, pl, time) // initializer list to call the parent constructor
                    {
                        flags = f;
                        isSYN = syn;
                        isACK = ack;
                        isFIN = fin;
                        windowSize = wSize;
                    }

int TCPPacket::getFlags() const
{
    return flags;
}

bool TCPPacket::getACK() const
{
    return isACK;
}

bool TCPPacket::getSYN() const
{
    return isSYN;
}

bool TCPPacket::getFIN() const
{
    return isFIN;
}

int TCPPacket::getWindowSize() const
{
    return windowSize;
}

std::string TCPPacket::getProtocol() const
{
    return "TCP";
}

void TCPPacket::analyze()
{}

void TCPPacket::display() const
{
    std::cout << "TCP Packet" << std::endl;
    std::cout << "Source IP: " << getSourceIP() << std::endl;
    std::cout << "Destination IP: " << getDestinationIP() << std::endl;
    std::cout << "Source Port: " << getSourcePort() << std::endl;
    std::cout << "Dest Port: " << getDestinationPort() << std::endl;
    std::cout << "SYN: " << isSYN << std::endl;
    std::cout << "ACK: " << isACK << std::endl;
    std::cout << "FIN: " << isFIN << std::endl;
}