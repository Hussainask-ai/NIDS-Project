#include "Alert.h"
#include <iostream>

Alert::Alert()
{
    alertID = 0;
    timestamp = "";
    sourceIP = "";
    destIP = "";
    protocol = "";
    severity = ""; 
    description = ""; 
    ruleID = 0;
}

Alert::Alert(int aID, std::string time, std::string sIP, std::string dIP, std::string pro, 
            std::string severe, std::string descrip, int rID)
{
    alertID = aID;
    timestamp = time;
    sourceIP = sIP;
    destIP = dIP;
    protocol = pro;
    severity = severe; 
    description = descrip; 
    ruleID = rID;
}

int Alert::getAlertID() const
{
    return alertID;
}

std::string Alert::getTimeStamp() const
{
    return timestamp;
}

std::string Alert::getSourceIP() const 
{
    return sourceIP;
}

std::string Alert::getDestIP() const
{
    return destIP;
}

std::string Alert::getProtocol() const 
{
    return protocol;
}

std::string Alert::getSeverity() const
{
    return severity;
}

std::string Alert::getDescription() const
{
    return description;
}

int Alert::getRuleID() const
{
    return ruleID;
}

void Alert::display() const
{
    std::cout << "\n====================================" << std::endl;
    std::cout << "Alert ID: " << alertID << std::endl;
    std::cout << "Timestamp: " << timestamp << std::endl;
    std::cout << "Source IP: " << sourceIP << std::endl;
    std::cout << "Destination IP: " << destIP << std::endl;
    std::cout << "Protocol: " << protocol << std::endl;
    std::cout << "Severity: " << severity << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Rule ID: " << ruleID << std::endl;
    std::cout << "====================================" << std::endl;
}

std::string Alert::toString() const
{
    return "Alert ID: " + std::to_string(alertID) + "\n" +
           "Timestamp: " + timestamp + "\n" +
           "Source IP: " + sourceIP + "\n" +
           "Destination IP: " + destIP + "\n" +
           "Protocol: " + protocol + "\n" +
           "Severity: " + severity + "\n" +
           "Description: " + description + "\n" +
           "Rule ID: " + std::to_string(ruleID) + "\n";
}