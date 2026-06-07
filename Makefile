CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LIBS = -lpcap -lncurses

SRCS = src/main.cpp src/Packet.cpp src/TCPPacket.cpp \
       src/UDPPacket.cpp src/ICMPPacket.cpp \
       src/Rule.cpp src/Alert.cpp \
       src/RuleEngine.cpp src/AlertManager.cpp \
       src/Logger.cpp src/Scanner.cpp src/UI.cpp

TARGET = nids

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)