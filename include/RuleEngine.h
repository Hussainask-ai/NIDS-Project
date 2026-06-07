#ifndef RULEENGINE_H
#define RULEENGINE_H
#include "Rule.h"
#include "Alert.h"
#include <vector>


class RuleEngine
{
    private:
        std::vector<Rule> rules;
        std::string rulesFilePath;
        void loadRules();

    public:
        RuleEngine(std::string filePath);
        std::vector<Alert> analyzePacket(Packet* pkt);
        void addRule(Rule r);
        void removeRule(int ruleID);
        void displayRules() const;
        void saveRules();
        int getRuleCount() const;
};

#endif