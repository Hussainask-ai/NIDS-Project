#include "UI.h"
#include <iostream>
#include <limits>
#include <csignal>
#include <vector>
#include <string>
#include <fstream>

UI::UI(AlertManager* am, RuleEngine* re, Scanner* s, Logger* l)
{
    alertManager = am;
    ruleEngine = re;
    scanner = s;
    logger = l;
}

void UI::showMainMenu()
{
    std::cout << "\n╔══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║        NETWORK INTRUSION DETECTION SYSTEM            ║" << std::endl;
    std::cout << "║                    v1.0 — NIDS                       ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║  [1] Start Live Capture                              ║" << std::endl;
    std::cout << "║  [2] Analyze PCAP File                               ║" << std::endl;
    std::cout << "║  [3] View All Alerts                                 ║" << std::endl;
    std::cout << "║  [4] View Alerts by Severity                         ║" << std::endl;
    std::cout << "║  [5] Alert Statistics                                ║" << std::endl;
    std::cout << "║  [6] Manage Rules                                    ║" << std::endl;
    std::cout << "║  [7] Export Logs                                     ║" << std::endl;
    std::cout << "║  [8] Blacklist Manager                               ║" << std::endl;
    std::cout << "║  [9] About                                           ║" << std::endl;
    std::cout << "║  [0] Exit                                            ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\nEnter your choice: ";
}

void UI::showAlerts()
{
    std::cout << "\n[+] Displaying All Alerts:" << std::endl;
    alertManager->displayAllAlerts();
}

void UI::showStats()
{
    std::cout << "\n[+] Displaying Alert Statistics:" << std::endl;
    alertManager->displayStats();
}

void UI::manageRules()
{
    int choice;
    std::cout << "\n╔══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                  RULE MANAGER                        ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║  [1] View All Rules                                  ║" << std::endl;
    std::cout << "║  [2] Add Rule                                        ║" << std::endl;
    std::cout << "║  [3] Remove Rule                                     ║" << std::endl;
    std::cout << "║  [0] Back                                            ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\nEnter your choice: ";
    std::cin >> choice;

    if(choice == 1)
    {
        ruleEngine->displayRules();
    }
    else if(choice == 2)
    {
        int  id, dport;
        std::string proto, sIP, dIP, action, desc, severe;

        std::cout << "Enter Rule ID: "; std::cin>>id;
        std::cout << "Enter Destination Port: "; std::cin>>dport;
        std::cout << "Enter Protocol: "; std::cin>>proto;
        std::cout << "Enter Source IP: "; std::cin>>sIP;
        std::cout << "Enter Destination IP: "; std::cin>>dIP;
        std::cout << "Enter Action: "; std::cin>>action;
        std::cout << "Enter Description: "; std::cin>>desc;
        std::cout << "Enter Severity (Low/Medium/High/Critical): "; std::cin>>severe;
        std::cin.ignore(); // Clear input buffer

        Rule r(id, proto, sIP, dIP, dport, action, desc, severe);
        ruleEngine->addRule(r);
        ruleEngine->saveRules();
        std::cout << "[+] Rule added and saved successfully." << std::endl;    
    }
    else if(choice == 3)
    {
        int id;
        std::cout << "Enter Rule ID to remove: "; std::cin>>id;
        ruleEngine->removeRule(id);
        ruleEngine->saveRules();
        std::cout << "[+] Rule removed and saved successfully." << std::endl;    
    }
}

void UI::manageBlackList()
{
    std::cout << "\n╔══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║               BLACKLIST MANAGER                      ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║  [1] View Blacklisted IPs                            ║" << std::endl;
    std::cout << "║  [2] Add IP to Blacklist                             ║" << std::endl;
    std::cout << "║  [3] Remove IP from Blacklist                        ║" << std::endl;
    std::cout << "║  [0] Back                                            ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\nEnter your choice: ";

    int choice;
    std::cin >> choice;

    std::fstream blacklistFile;
    std::string ip;

    if(choice == 1)
    {
        std::ifstream file("blacklist.txt");
        if (!file.is_open())
        {
            std::cout << "No blacklisted IPs found." << std::endl;
            return;
        }
        std::string line;
        std::cout << "\nBlacklisted IPs:" << std::endl;
        while (std::getline(file, line))
        {
            std::cout << "- " << line << std::endl;
        }
        file.close();
    }
    else if(choice == 2)
    {
        std::cout << "Enter IP to blacklist: ";
        std::cin >> ip;
        std::ofstream file("blacklist.txt", std::ios::app);
        file << ip << "\n";
        file.close();
        std::cout << "[+] IP added to blacklist." << std::endl;
    }
    else if (choice == 3)
    {
        std::cout << "Enter IP to remove: ";
        std::cin >> ip;
        std::ifstream file("blacklist.txt");
        std::vector<std::string> ips;
        std::string line;
        while (getline(file, line))
            if (line != ip) ips.push_back(line);
        file.close();
        std::ofstream outFile("blacklist.txt");
        for (size_t i = 0; i < ips.size(); i++)
            outFile << ips[i] << "\n";
        outFile.close();
        std::cout << "[+] IP removed from blacklist." << std::endl;
    }
}

void UI::showAbout()
{
    std::cout << "\n╔══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                     ABOUT NIDS                       ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║  Network Intrusion Detection System v1.0             ║" << std::endl;
    std::cout << "║  Built with C++17, libpcap, ncurses                  ║" << std::endl;
    std::cout << "║  Developed by: Hussain, Aayan and AR                 ║" << std::endl;
    std::cout << "║  Air University Karachi — BS Cybersecurity           ║" << std::endl;
    std::cout << "║  OOP Final Project — 2026                            ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════╝" << std::endl;
}


void UI::run()
{
    int choice;

    while (true)
    {
        showMainMenu();
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                int count;
                std::string iface;
                std::cout << "Enter interface (e.g. wlp2s0): ";
                std::cin >> iface;
                std::cout << "Enter packet count (0 for unlimited): ";
                std::cin >> count;
                scanner->startCapture(count);
                break;
            }
            case 2:
            {
                std::string pcapFile;
                std::cout << "Enter pcap file path: ";
                std::cin >> pcapFile;
                scanner->readFromFile(pcapFile);
                break;
            }
            case 3:
                showAlerts();
                break;
            case 4:
            {
                std::string severity;
                std::cout << "Enter severity (LOW/MEDIUM/HIGH/CRITICAL): ";
                std::cin >> severity;
                alertManager->displayBySeverity(severity);
                break;
            }
            case 5:
                showStats();
                break;
            case 6:
                manageRules();
                break;
            case 7:
            {
                logger->exportAlerts(alertManager->getAlerts());
                std::cout << "[+] Alerts exported to log file." << std::endl;
                break;
            }
            case 8:
                manageBlackList();
                break;
            case 9:
                showAbout();
                break;
            case 0:
                std::cout << "\n[+] Exiting NIDS. Goodbye!\n" << std::endl;
                return;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    }
}