#include "Scanner.h"
#include "TCPPacket.h"
#include "UDPPacket.h"
#include "ICMPPacket.h"
#include <iostream>
#include <string>
#include <netinet/ip.h>  // struct iphdr
#include <netinet/tcp.h>  // struct tcphdr
#include <netinet/udp.h>  // struct udphdr
#include <netinet/ip_icmp.h>  // struct icmphdr
#include <net/ethernet.h>  // struct ethhdr
#include <arpa/inet.h>  // inet_ntop
#include <ctime>  // for getting current time

std::string getCurrentTime()
{
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buf);
}

Scanner::Scanner(std::string iface, RuleEngine* re, AlertManager* am, Logger* l)
{
    interface = iface;
    ruleEngine = re;
    alertManager = am;
    logger = l;
    isRunning = false;
    packetCount = 0;
    handle = nullptr;
}

Scanner::~Scanner()
{
    if(handle != nullptr)
        pcap_close(handle);
}

/*startCapture().
This function:

1. Opens the network interface using libpcap
2. Sets a filter for TCP, UDP and ICMP only
3. Starts the capture loop.*/

void Scanner::startCapture(int count)
{
    char errbuf[PCAP_ERRBUF_SIZE];

    // Opening the netwokr interface
    handle = pcap_open_live(
        interface.c_str(), // Interface name 
        65536, // Max bytes per packet
        1, // Promiscous Mode (1 = ON, 0 = OFF)
        1000, // Timeout in ms
        errbuf // Error buffer
    );

    if(handle == nullptr)
    {
        std::cout << "Error opening the interface: " << errbuf << std::endl;
        return;
    }

    struct bpf_program fp;
    pcap_compile(handle, &fp, "tcp or udp or icmp", 0, PCAP_NETMASK_UNKNOWN);
    pcap_setfilter(handle, &fp);

    isRunning = true;
    std::cout << "[+] Starting capture on interface: " << interface << std::endl;

    // Starting capture loop
    pcap_loop(handle, count, packetHandler, (u_char*)this);

    isRunning = false;
}

void Scanner::packetHandler(u_char* args, const struct pcap_pkthdr* header, const u_char* packet)
{
    Scanner* scanner = (Scanner*)args;
    scanner->packetCount++;

    const struct ethhdr* eth = (struct ethhdr*)packet;
    if(ntohs(eth->h_proto) != ETH_P_IP)
        return;

    const struct iphdr* ip = (struct iphdr*)(packet + sizeof(struct ethhdr));
    
    char srcIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ip->saddr, srcIP,  INET_ADDRSTRLEN);

    char destIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ip->daddr, destIP, INET_ADDRSTRLEN);

    std::string currentTime = getCurrentTime();
    int ipHeaderLen = ip->ihl * 4;

    const u_char* transportLayer = packet + sizeof(struct ethhdr) + ipHeaderLen;

    Packet* pkt = nullptr;

    if(ip->protocol == IPPROTO_TCP)
    {
        const struct tcphdr* tcp = (struct tcphdr*)transportLayer;
        
        int srcPort = ntohs(tcp->source);
        int destPort = ntohs(tcp->dest);
        bool syn = tcp->syn;
        bool ack = tcp->ack;
        bool fin = tcp->fin;
        int flags = tcp->th_flags;
        int window = ntohs(tcp->window);
        int tcpHeaderLen = tcp->doff * 4;
        const u_char* payloadPtr = transportLayer + tcpHeaderLen;
        int payloadlen = header->len - (payloadPtr - packet);
        std::string payload(payloadlen > 0 ? (char*)payloadPtr : "",
                            payloadlen > 0 ? payloadlen : 0);

        pkt = new TCPPacket(srcPort, destPort, destIP, srcIP, payload, currentTime, 
                     flags, syn, ack, fin, window);
    }

    else if(ip->protocol == IPPROTO_UDP)
    {
        const struct udphdr* udp = (struct udphdr*)transportLayer;

        int srcPort = ntohs(udp->source);
        int destPort = ntohs(udp->dest);
        int length = ntohs(udp->len);
        const u_char* payloadPtr = transportLayer + sizeof(struct udphdr);
        int payloadLen = header->len - (payloadPtr - packet);
        std::string payload(payloadLen > 0 ? (char*)payloadPtr : "",
                    payloadLen > 0 ? payloadLen : 0);

        pkt = new UDPPacket(srcPort, destPort, destIP, srcIP, payload, currentTime, length);
    } 

    else if(ip->protocol == IPPROTO_ICMP)
    {
        const struct icmphdr* icmp = (struct icmphdr*)transportLayer;
        int type = icmp->type;
        int code = icmp->code;
        const u_char* payloadPtr = transportLayer + sizeof(struct icmphdr);
        int payloadLen = header->len - (payloadPtr - packet);
        std::string payload(payloadLen > 0 ? (char*)payloadPtr : "",
                    payloadLen > 0 ? payloadLen : 0);
        
        pkt = new ICMPPacket(destIP, srcIP, payload, currentTime, type, code);
    }

    else 
    {
        return;
    }

    std::vector<Alert> triggered = scanner->ruleEngine->analyzePacket(pkt);
    for(size_t i = 0; i < triggered.size(); i++)
    {
        scanner->alertManager->addAlert(triggered[i]);
        scanner->logger->logAlerts(triggered[i]);
        scanner->logger->logPacket(pkt);
    }

    // Port scan detection
if(ip->protocol == IPPROTO_TCP)
{
    const struct tcphdr* tcp = (struct tcphdr*)transportLayer;
    int destPort = ntohs(tcp->dest);
    scanner->portScanTracker[srcIP].insert(destPort);
    
    if(scanner->portScanTracker[srcIP].size() > 15)
    {
        Alert a(
            scanner->alertManager->getTotalAlerts() + 1,
            currentTime,
            srcIP,
            destIP,
            "TCP",
            "CRITICAL",
            "Port Scan Detected",
            0
        );
        scanner->alertManager->addAlert(a);
        scanner->logger->logAlerts(a);
        scanner->portScanTracker[srcIP].clear();
    }
}

// Ping flood detection
if(ip->protocol == IPPROTO_ICMP)
{
    scanner->icmpCounter[srcIP]++;
    
    if(scanner->icmpCounter[srcIP] > 100)
    {
        Alert a(
            scanner->alertManager->getTotalAlerts() + 1,
            currentTime,
            srcIP,
            destIP,
            "ICMP",
            "HIGH",
            "Ping Flood Detected",
            0
        );
        scanner->alertManager->addAlert(a);
        scanner->logger->logAlerts(a);
        scanner->icmpCounter[srcIP] = 0;
    }
}

    delete pkt;
}

void Scanner::stopCapture()
{
    if(handle != nullptr)
    {
        pcap_breakloop(handle);
        pcap_close(handle);
        handle = nullptr;
    }
}

void Scanner::readFromFile(std::string pcapFile)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    handle = pcap_open_offline(pcapFile.c_str(), errbuf);
    if(handle == nullptr)
    {
        std::cout << "Error opening pcap file: " << errbuf << std::endl;
        return;
    }

    isRunning = true;
    std::cout << "[+] Reading packets from file: " << pcapFile << std::endl;

    pcap_loop(handle, 0, packetHandler, (u_char*)this);

    isRunning = false;
}

bool Scanner::getIsRunning() const { return isRunning; }

int Scanner::getPacketCount() const { return packetCount; }

