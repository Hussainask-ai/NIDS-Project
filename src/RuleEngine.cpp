#include "RuleEngine.h"
#include <iostream>
#include <fstream>
#include <sstream>


static int globalAlertID = 0; //For live Alert ID generation

RuleEngine::RuleEngine(std::string filepath)
{
    rulesFilePath = filepath;
    loadRules();
}

void RuleEngine::loadRules()
{
    std::ifstream file(rulesFilePath);

    if(!file.is_open())
    {
        std::cout << "Error: Could not open rules file: " 
        << rulesFilePath << std::endl;
        return;
    }

    std::string line;
    while(getline(file, line))
    {
        //for skipping the empty lines we use this
        if(line.empty() || line[0] == '#')
            continue;

        //to split line by | character 
        std::stringstream ss(line);
        std::string pieces[8];
        int i = 0;

        while(getline(ss, pieces[i], '|') && i < 8) 
            i++;

        // to create rule objects from pieces 
        Rule r(
            std::stoi(pieces[0]), //ruleID
            pieces[1], // Protocol
            pieces[2], // sourceIP
            pieces[3],//destIP
            std::stoi(pieces[4]), //destport 
            pieces[5], // action
            pieces[6], // description
            pieces[7] //severity
        );

        rules.push_back(r);
    }


    file.close();
    std::cout << "Loaded " << rules.size() << " rules." << std::endl;
}

std::vector<Alert> RuleEngine::analyzePacket(Packet* pkt)
{
    std::vector <Alert> triggeredAlerts;

    for(size_t i = 0; i < rules.size(); i++)
    {
        if (rules[i].matches(pkt))
        {
            Alert ai(
                ++globalAlertID,  // increments globally across all packets
                pkt->getTimeStamp(), 
                pkt->getSourceIP(),
                pkt->getDestinationIP(),
                pkt->getProtocol(),
                rules[i].getSeverity(), 
                rules[i].getDescription(), 
                rules[i].getRuleID() 
            );
            triggeredAlerts.push_back(ai);
        }
    }
    
    return triggeredAlerts;
}

void RuleEngine::addRule(Rule r) {rules.push_back(r);}

void RuleEngine::removeRule(int ruleID)
{
    for(size_t i = 0; i < rules.size(); i++)
    {
        if (rules[i].getRuleID() == ruleID)
        {
            rules.erase(rules.begin() + i);
            break;
        }
    }
} 

void RuleEngine::displayRules() const
{
    for(size_t i = 0; i < rules.size(); i++)
    {
        std::cout << "\nID:" << rules[i].getRuleID() << " | "
                  << rules[i].getProtocol() << " | "
                  << rules[i].getDestPort() << " | "
                  << rules[i].getSeverity() << " | "
                  << rules[i].getDescription() << " | " << std::endl;
    }
}

void RuleEngine::saveRules()
{
    std ::ofstream file(rulesFilePath);
    if(!file.is_open())
    {
        std::cout << "Error: Could not open rules file for writing: " 
        << rulesFilePath << std::endl;
        return;
    }

    for(size_t i = 0; i < rules.size(); i++)
    {
        file << rules[i].getRuleID() << "|"
             << rules[i].getProtocol() << "|"
             << rules[i].getSourceIP() << "|"
             << rules[i].getDestIP() << "|"
             << rules[i].getDestPort() << "|"
             << rules[i].getAction() << "|"
             << rules[i].getDescription() << "|"
             << rules[i].getSeverity() << std::endl;
    }
    file.close();
}

int RuleEngine::getRuleCount() const { return rules.size(); }
