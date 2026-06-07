#ifndef LOGGER_H
#define LOGGER_H
#include <fstream>
#include <vector>
#include "Alert.h"
#include "Packet.h"


class Logger
{
    private:
        std::string logFilePath;
        std::ofstream logFile;
    
    public:
        Logger(std::string pathAA);
        ~Logger();
        void logAlerts(const Alert& a);
        void logPacket(const Packet* p);
        void logEvent(std::string event);
        void exportAlerts(std::vector<Alert> alert);
};


#endif