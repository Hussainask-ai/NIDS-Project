# NIDS — Network Intrusion Detection System

A console-based Network Intrusion Detection System built in C++17 using libpcap. 
Developed as an OOP Final Project at Air University Karachi.

## Features
- Real-time packet capture using libpcap
- TCP, UDP and ICMP protocol parsing
- Rule-based detection engine
- Port scan detection
- Ping flood detection
- Alert generation with severity levels (LOW, MEDIUM, HIGH, CRITICAL)
- File logging system
- Rule management (add, remove, save)
- Blacklist manager
- Clean menu-driven console UI

## Requirements
- Linux (Ubuntu)
- g++ with C++17 support
- libpcap-dev
- libncurses-dev

## Installation
```bash
sudo apt install g++ make libpcap-dev libncurses-dev
git clone https://github.com/Hussainask-ai/NIDS-Project.git
cd NIDS-Project
make
```

## Usage
```bash
sudo ./nids
```

## Testing
```bash
# Simulate port scan
sudo nmap -sS YOUR_IP

# Simulate ping flood  
sudo hping3 -1 --flood YOUR_IP
```

## Project Structure
NIDS_Project/
├── src/          # Source files
├── include/      # Header files
├── rules/        # Detection rules
├── logs/         # Log files
└── Makefile

## Developers
- Hussain Askari, Aayan Asim and Abdul Rehman Ayaaz
- Air University Karachi — BS Cybersecurity
- OOP Final Project — 2026
