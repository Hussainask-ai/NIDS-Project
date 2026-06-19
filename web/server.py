from flask import Flask, render_template, jsonify, request
import subprocess
import os
import json
from datetime import datetime

app = Flask(__name__)

ALERTS_FILE = "../logs/alerts.txt"
RULES_FILE = "../rules/default.rules"
BLACKLIST_FILE = "../blacklist.txt"
NIDS_PATH = "../nids"

# Parse alerts from log file
def parse_alerts():
    alerts = []
    if not os.path.exists(ALERTS_FILE):
        return alerts
    
    with open(ALERTS_FILE, 'r', errors='ignore') as f:
        content = f.read()
    
    blocks = content.split("NEW SESSION STARTED:")
    for block in blocks:
        lines = block.strip().split('\n')
        alert = {}
        for line in lines:
            line = line.strip()
            if line.startswith("Alert ID:"):
                alert['id'] = line.replace("Alert ID:", "").strip()
            elif line.startswith("Timestamp:"):
                alert['timestamp'] = line.replace("Timestamp:", "").strip()
            elif line.startswith("Source IP:"):
                alert['source_ip'] = line.replace("Source IP:", "").strip()
            elif line.startswith("Destination IP:"):
                alert['dest_ip'] = line.replace("Destination IP:", "").strip()
            elif line.startswith("Protocol:"):
                alert['protocol'] = line.replace("Protocol:", "").strip()
            elif line.startswith("Severity:"):
                alert['severity'] = line.replace("Severity:", "").strip()
            elif line.startswith("Description:"):
                alert['description'] = line.replace("Description:", "").strip()
            elif line.startswith("Rule ID:"):
                alert['rule_id'] = line.replace("Rule ID:", "").strip()
                if all(k in alert for k in ['id','timestamp','source_ip','dest_ip','protocol','severity','description']):
                    alerts.append(dict(alert))
                    alert = {}
    return alerts

# Parse rules from rules file
def parse_rules():
    rules = []
    if not os.path.exists(RULES_FILE):
        return rules
    with open(RULES_FILE, 'r') as f:
        for line in f:
            line = line.strip()
            if line and not line.startswith('#'):
                parts = line.split('|')
                if len(parts) == 8:
                    rules.append({
                        'id': parts[0],
                        'protocol': parts[1],
                        'src_ip': parts[2],
                        'dest_ip': parts[3],
                        'dest_port': parts[4],
                        'action': parts[5],
                        'description': parts[6],
                        'severity': parts[7]
                    })
    return rules

# Parse blacklist
def parse_blacklist():
    ips = []
    if not os.path.exists(BLACKLIST_FILE):
        return ips
    with open(BLACKLIST_FILE, 'r') as f:
        for line in f:
            line = line.strip()
            if line:
                ips.append(line)
    return ips

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/alerts')
def get_alerts():
    alerts = parse_alerts()
    return jsonify(alerts)

@app.route('/api/stats')
def get_stats():
    alerts = parse_alerts()
    stats = {
        'total': len(alerts),
        'critical': sum(1 for a in alerts if a.get('severity') == 'CRITICAL'),
        'high': sum(1 for a in alerts if a.get('severity') == 'HIGH'),
        'medium': sum(1 for a in alerts if a.get('severity') == 'MEDIUM'),
        'low': sum(1 for a in alerts if a.get('severity') == 'LOW'),
    }
    return jsonify(stats)

@app.route('/api/rules')
def get_rules():
    return jsonify(parse_rules())

@app.route('/api/rules/add', methods=['POST'])
def add_rule():
    data = request.json
    required = ['id','protocol','src_ip','dest_ip','dest_port','action','description','severity']
    if not all(k in data for k in required):
        return jsonify({'error': 'Missing fields'}), 400
    
    valid_protocols = ['TCP', 'UDP', 'ICMP', 'ANY']
    valid_severities = ['LOW', 'MEDIUM', 'HIGH', 'CRITICAL']
    
    if data['protocol'] not in valid_protocols:
        return jsonify({'error': 'Invalid protocol'}), 400
    if data['severity'] not in valid_severities:
        return jsonify({'error': 'Invalid severity'}), 400
    try:
        port = int(data['dest_port'])
        if port < 0 or port > 65535:
            return jsonify({'error': 'Invalid port'}), 400
    except:
        return jsonify({'error': 'Port must be a number'}), 400
    
    rule_line = f"{data['id']}|{data['protocol']}|{data['src_ip']}|{data['dest_ip']}|{data['dest_port']}|{data['action']}|{data['description']}|{data['severity']}\n"
    with open(RULES_FILE, 'a') as f:
        f.write(rule_line)
    return jsonify({'success': True})

@app.route('/api/rules/remove', methods=['POST'])
def remove_rule():
    data = request.json
    rule_id = str(data.get('id'))
    rules = []
    with open(RULES_FILE, 'r') as f:
        for line in f:
            if line.startswith('#') or not line.strip():
                rules.append(line)
            elif not line.startswith(rule_id + '|'):
                rules.append(line)
    with open(RULES_FILE, 'w') as f:
        f.writelines(rules)
    return jsonify({'success': True})

@app.route('/api/blacklist')
def get_blacklist():
    return jsonify(parse_blacklist())

@app.route('/api/blacklist/add', methods=['POST'])
def add_blacklist():
    data = request.json
    ip = data.get('ip', '').strip()
    if ip.count('.') != 3:
        return jsonify({'error': 'Invalid IP address'}), 400
    with open(BLACKLIST_FILE, 'a') as f:
        f.write(ip + '\n')
    return jsonify({'success': True})

@app.route('/api/blacklist/remove', methods=['POST'])
def remove_blacklist():
    data = request.json
    ip = data.get('ip', '').strip()
    ips = parse_blacklist()
    ips = [i for i in ips if i != ip]
    with open(BLACKLIST_FILE, 'w') as f:
        for i in ips:
            f.write(i + '\n')
    return jsonify({'success': True})

@app.route('/api/capture/start', methods=['POST'])
def start_capture():
    return jsonify({'success': True, 'message': 'Run sudo ./nids in a separate terminal to start capturing. This dashboard displays live results.'})

@app.route('/api/clear', methods=['POST'])
def clear_alerts():
    with open(ALERTS_FILE, 'w') as f:
        f.write('')
    return jsonify({'success': True})

if __name__ == '__main__':
    app.run(debug=True, port=5000)

