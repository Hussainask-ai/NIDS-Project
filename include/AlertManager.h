#ifndef ALERTMANAGER_H
#define ALERTMANAGER_H
#include "Alert.h"
#include <vector>

class AlertManager
{
    private:
        std::vector<Alert> alerts;
        int criticalCount;
        int highCount;
        int mediumCount;
        int lowCount;

    public:
        AlertManager();
        void addAlert(Alert a);
        void displayAllAlerts() const;
        void displayBySeverity(std::string severity) const;
        void clearAlerts();
        void displayStats() const;
        int getTotalAlerts() const;
        std::vector<Alert> getAlerts() const;

};




#endif