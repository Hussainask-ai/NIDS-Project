#ifndef SCANNER_H
#define SCANNER_H
#include <pcap.h>
#include <map>
#include <set>
#include "RuleEngine.h"
#include "AlertManager.h"
#include "Logger.h"

class Scanner
{
    private:
        std::string interface;
        bool isRunning;
        int packetCount;
        pcap_t* handle;
        RuleEngine* ruleEngine;
        AlertManager* alertManager;
        Logger* logger;
        std::map<std::string, std::set<int>> portScanTracker;
        std::map<std::string, int> icmpCounter;
    
    public:
        Scanner(std::string iface, RuleEngine* re, AlertManager* am, Logger* l);
        ~Scanner();
        void startCapture(int count);
        void stopCapture();
        void readFromFile(std::string pcapFile);
        bool getIsRunning() const;
        int getPacketCount() const;
        static void packetHandler(u_char* args, const struct pcap_pkthdr* header, const u_char* packet);
};


#endif