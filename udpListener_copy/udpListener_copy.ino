#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

// Network settings
byte mac[] = {0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 }; // MAC address of your Arduino
IPAddress localIP(192, 168, 1, 20);  // IP address of your Arduino
unsigned int localPort = 8888;  // Local port number for receiving UDP packets

// UDP object
EthernetUDP udp;
//IPAddress client_ip(192,168,1,50);

void setup() {
  Ethernet.begin(mac, localIP);
  udp.begin(localPort);

  Serial.begin(57600);
  Serial.println("UDP Packets Sender and Receiver");
}

void loop() {
  // Check if a UDP packet has been received
  int packetSize = udp.parsePacket();
  
  if (packetSize) {
    Serial.println("Packet received!");

    // Read the packet data
    char packetData[packetSize + 1];
    udp.read(packetData, packetSize);
    packetData[packetSize] = '\0';

    Serial.print("Received data: ");
    Serial.println(packetData);

    // Respond to the received packet
    udp.beginPacket(IPAddress(192, 168, 1, 50), 8888);
    udp.write("We received the packet");
    udp.endPacket();
  }

  // Send a UDP packet
  udp.beginPacket(IPAddress(192, 168, 1, 50), 8888);  // Destination IP address and port
  udp.write("Hello, UDP Server!");
  udp.endPacket();

  delay(1000);
}
