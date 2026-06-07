#ifndef RULE_H
#define RULE_H
#include "Packet.h"

class Rule
{
    private:
        int ruleID;
        std::string protocol;
        std::string sourceIP;
        std::string destIP;
        int destPort;
        std::string action;
        std::string description;
        std::string severity;

    public:
        Rule();
        Rule(int id, std::string proto, std::string sIP, std::string dIP, int dPort,
        std::string act, std::string desc, std::string severe);
        bool matches(Packet *pkt) const;
        int getRuleID() const;
        std::string getProtocol() const;
        std::string getSourceIP() const;
        std::string getDestIP() const;
        int getDestPort() const;
        std::string getAction() const;
        std::string getDescription() const;
        std::string getSeverity() const;
};


#endif