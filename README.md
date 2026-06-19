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

## Web Dashboard (Monitoring Interface)

A web-based monitoring dashboard is included for visualizing alerts, managing 
rules, and managing the blacklist through a browser interface.

### Architecture
The C++ NIDS engine handles all packet capture, detection logic, and OOP 
implementation. The web dashboard is a separate Flask-based monitoring layer 
that reads the alert logs and rule files produced by the C++ program — 
similar to how production tools separate detection engines (Suricata, Snort) 
from visualization layers (Kibana).

### Running the Web Dashboard

Terminal 1 — run the NIDS engine:
```bash
sudo ./nids
```

Terminal 2 — run the web dashboard:
```bash
cd web
python3 server.py
```

Open your browser to: http://localhost:5000

The dashboard auto-refreshes every 10 seconds to show new alerts.

## Developers
- Hussain Askari, Aayan Asim and Abdul Rehman Ayaaz
- Air University Karachi — BS Cybersecurity
- OOP Final Project — 2026
