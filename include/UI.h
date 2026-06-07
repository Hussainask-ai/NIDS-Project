#ifndef UI_H
#define UI_H
#include "AlertManager.h"
#include "Scanner.h"
#include "RuleEngine.h"
#include "Logger.h"

class UI
{
    private:
        AlertManager* alertManager;
        Logger* logger;
        Scanner* scanner;
        RuleEngine* ruleEngine;
    
    public:
        UI(AlertManager* am, RuleEngine* re, Scanner* s, Logger* l);
        void showMainMenu();
        void showAlerts();
        void showStats();
        void manageRules();
        void manageBlackList();
        void showAbout();
        void run();
};


#endif