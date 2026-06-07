#ifndef PACKET_H
#define PACKET_H
#include <string>

class Packet
{
    private:

        int sourcePort;
        int destPort;
        std::string timestamp;
        std::string payload;
        std::string sourceIP;
        std::string destIP;

    public:
        Packet();
        Packet(int sPort, int dPort, std::string dIP, std::string sIP, std::string pl, std::string time);
        int getSourcePort() const;
        int getDestinationPort() const;
        std::string getSourceIP() const;
        std::string getDestinationIP() const;
        std::string getPayload() const;
        std::string getTimeStamp() const;
        void setPayload(std::string p);

        virtual std::string getProtocol() const = 0;
        virtual void analyze() = 0;
        virtual void display() const = 0;

        virtual ~Packet(){}
};

#endif