#include "AlertManager.h"
#include "Alert.h"
#include <iostream>

AlertManager::AlertManager()
{
    criticalCount = 0;
    highCount = 0;
    mediumCount = 0;
    lowCount = 0;
}

void AlertManager::addAlert(Alert a)
{
    alerts.push_back(a);

    if(a.getSeverity() == "CRITICAL")
        criticalCount++;
    else if(a.getSeverity() == "HIGH")
        highCount++;
    else if(a.getSeverity() == "MEDIUM")
        mediumCount++;
    else if(a.getSeverity() == "LOW")
        lowCount++;
}

void AlertManager::displayAllAlerts() const
{
    if (alerts.empty())
    {
        std::cout << "No alerts found." << std::endl;
        return;
    }

    for(size_t i = 0; i < alerts.size(); i++)
    {
        std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
        std::cout << "║           ALERT DETECTED               ║" << std::endl;
        std::cout << "╠════════════════════════════════════════╣" << std::endl;
        std::cout << "║ Alert ID:    " << alerts[i].getAlertID() << std::endl;
        std::cout << "║ Timestamp:   " << alerts[i].getTimeStamp() << std::endl;
        std::cout << "║ Severity:    " << alerts[i].getSeverity() << std::endl;
        std::cout << "║ Protocol:    " << alerts[i].getProtocol() << std::endl;
        std::cout << "║ Source IP:   " << alerts[i].getSourceIP() << std::endl;
        std::cout << "║ Dest IP:     " << alerts[i].getDestIP() << std::endl;
        std::cout << "║ Description: " << alerts[i].getDescription() << std::endl;
        std::cout << "║ Rule ID:     " << alerts[i].getRuleID() << std::endl;
        std::cout << "╚════════════════════════════════════════╝" << std::endl; 
    }
}

void AlertManager::displayBySeverity(std::string severity) const
{
    for(size_t i = 0; i < alerts.size(); i++)
    {
        if(alerts[i].getSeverity() == severity)
        {
        std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
        std::cout << "║           ALERT (By Severity)               ║" << std::endl;
        std::cout << "╠════════════════════════════════════════╣" << std::endl;
        std::cout << "║ Alert ID:    " << alerts[i].getAlertID() << std::endl;
        std::cout << "║ Timestamp:   " << alerts[i].getTimeStamp() << std::endl;
        std::cout << "║ Severity:    " << alerts[i].getSeverity() << std::endl;
        std::cout << "║ Protocol:    " << alerts[i].getProtocol() << std::endl;
        std::cout << "║ Source IP:   " << alerts[i].getSourceIP() << std::endl;
        std::cout << "║ Dest IP:     " << alerts[i].getDestIP() << std::endl;
        std::cout << "║ Description: " << alerts[i].getDescription() << std::endl;
        std::cout << "║ Rule ID:     " << alerts[i].getRuleID() << std::endl;
        std::cout << "╚════════════════════════════════════════╝" << std::endl;  
        }
        else
            continue;
    }
}

void AlertManager::clearAlerts()
{
    alerts.clear();
    alerts.shrink_to_fit(); // Forces the vector to release unused capacity memory back to the system

    //Reset the Statistics back to zero
    criticalCount = 0;
    highCount = 0;
    mediumCount = 0;
    lowCount = 0;

    std::cout << "[+] Alert Manager storage cleared and stats reset successfully." << std::endl;
}

void AlertManager::displayStats() const
{
    size_t total = alerts.size();

    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║         NIDS ENGINE STATISTICS         ║" << std::endl;
    std::cout << "╠════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Total Alerts Generated: " << total << std::endl;
    std::cout << "╠════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Severity Breakdown:                    ║" << std::endl;
    std::cout << "║  🔴 CRITICAL: " << criticalCount << std::endl;
    std::cout << "║  🟠 HIGH:     " << highCount << std::endl;
    std::cout << "║  🟡 MEDIUM:   " << mediumCount << std::endl;
    std::cout << "║  🟢 LOW:      " << lowCount << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
}

int AlertManager::getTotalAlerts() const
{
    return alerts.size();
}

std::vector<Alert> AlertManager::getAlerts() const
{
    return alerts;
}