#include "Rule.h"
#include <iostream>

Rule::Rule()
{
    ruleID = 0;
    protocol = "";
    sourceIP = "";
    destIP = "";
    destPort = 0;
    action = "";
    description = "";
    severity = "";
} 

Rule::Rule(int id, std::string proto, std::string sIP, std::string dIP, int dPort,
        std::string act, std::string desc, std::string severe)
    {
        ruleID = id;
        protocol = proto;
        sourceIP = sIP;
        destIP = dIP;
        destPort = dPort;
        action = act;
        description = desc;
        severity = severe;
    }

// matches() — checks if a packet triggers this rule
bool Rule::matches(Packet *pkt) const
{
    if (protocol != "ANY" && protocol != pkt->getProtocol())
        return false;
    if (sourceIP != "ANY" && sourceIP != pkt->getSourceIP())
        return false;
    if (destIP != "ANY" && destIP != pkt->getDestinationIP())
        return false;
    if (destPort != 0 && destPort != pkt->getDestinationPort())
        return false;
    return true;
}

int Rule::getRuleID() const
{
    return ruleID;
}

std::string Rule::getProtocol() const
{
    return protocol;
}

std::string Rule::getSourceIP() const
{
    return sourceIP;
}

std::string Rule::getDestIP() const
{
    return destIP;
}

int Rule::getDestPort() const 
{
    return destPort;
}

std::string Rule::getAction() const
{
    return action;
}

std::string Rule::getDescription() const
{
    return description;
}

std::string Rule::getSeverity() const
{
    return severity;
}

