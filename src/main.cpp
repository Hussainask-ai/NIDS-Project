#include <iostream>
#include <csignal>
#include "Scanner.h"
#include "RuleEngine.h"
#include "AlertManager.h"
#include "Logger.h"
#include "UI.h"

Scanner* globalScanner = nullptr;

void signalHandler(int signum)
{
    std::cout << "\n[!] Interrupt received. Stopping capture..." << std::endl;
    if (globalScanner != nullptr)
        globalScanner->stopCapture();
}

int main()
{
    signal(SIGINT, signalHandler);

    RuleEngine re("rules/default.rules");
    AlertManager am;
    Logger l("logs/alerts.txt");
    Scanner scanner("wlp2s0", &re, &am, &l);
    UI ui(&am, &re, &scanner, &l);

    globalScanner = &scanner;

    ui.run();

    return 0;
}