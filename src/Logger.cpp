#include <iostream>
#include "Alert.h"
#include "Logger.h"
#include "Packet.h"
#include <iomanip>
#include <fstream>
#include <vector>

Logger::Logger(std::string path)
{
    logFilePath = path;
    logFile.open(path, std::ios::app);

    if(!logFile.is_open())
    {
        std::cout << "Error: Could not open log file: " << path << std::endl;
    }

    // Write session start marker. This tells us that a new session has been started in the log file.
    logFile << "\n========================================" << std::endl;
    logFile << "NEW SESSION STARTED: " << std::endl;
    logFile << "========================================\n" << std::endl;
}

Logger::~Logger()
{
    if(logFile.is_open())
        logFile.close();
}

void Logger::logAlerts(const Alert& a)
{
    logFile << a.toString() << std::endl;
}

void Logger::logPacket(const Packet* p)
{
    logFile << "[PACKET] "
            << p->getProtocol() << " | "
            << p->getSourceIP() << ":" << p->getSourcePort()
            << " -> "
            << p->getDestinationIP() << ":" << p->getDestinationPort()
            << " | " << p->getTimeStamp()
            << std::endl;
}

void Logger::logEvent(std::string event)
{
    logFile << "Event: " << event << std::endl;
}

void Logger::exportAlerts(std::vector<Alert> alert)
{
    for(size_t i = 0; i < alert.size(); i++)
    {
        logFile << alert[i].toString() << std::endl;
    }
}





