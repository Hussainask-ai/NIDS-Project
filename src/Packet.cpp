#include "Packet.h"
#include <iostream>

Packet::Packet()
{
    sourcePort = 0;
    destPort = 0;
    timestamp = "";
    payload = "";
    sourceIP = "";
    destIP = "";
}

Packet::Packet(int sPort, int dPort, std::string dIP, std::string sIP, std::string pl, std::string time)
{
    sourcePort = sPort;
    destPort = dPort;
    timestamp = time;
    payload = pl;
    sourceIP = sIP;
    destIP = dIP;
}

int Packet::getSourcePort() const
{
    return sourcePort;
}

int Packet::getDestinationPort() const
{
    return destPort;
}

std::string Packet::getSourceIP() const
{
    return sourceIP;
}

std::string Packet::getDestinationIP() const
{
    return destIP;
}

std::string Packet::getPayload() const
{
    return payload;
}

std::string Packet::getTimeStamp() const
{
    return timestamp;
}

void Packet::setPayload(std::string p)
{
    payload = p;
}

