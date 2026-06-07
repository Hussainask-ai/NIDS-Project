#ifndef ALERT_H
#define ALERT_H
#include <string>

class Alert
{
    private:
        int alertID;
        std::string timestamp; 
        std::string sourceIP;
        std::string destIP;
        std::string protocol;
        std::string severity; 
        std::string description; 
        int ruleID;

    public:
        Alert();
        Alert(int aID, std::string time, std::string sIP, std::string dIP, std::string pro, 
            std::string severe, std::string descrip, int rID);
        int getAlertID() const;
        std::string getTimeStamp() const; 
        std::string getSourceIP() const;
        std::string getDestIP() const;
        std::string getProtocol() const;
        std::string getSeverity() const; 
        std::string getDescription() const; 
        int getRuleID() const;
        void display() const;
        std::string toString() const;

};

#endif