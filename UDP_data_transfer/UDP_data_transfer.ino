#include <EtherCard.h>
#include <IPAddress.h>

#define STATIC 1  // set to 1 to disable DHCP (adjust myip/gwip values below)

#if STATIC
// Ethernet interface IP address
static byte myip[] = { 192,168,1,20 };
// Gateway IP address
static byte gwip[] = { 192,168,5,50 };
#endif

// Ethernet MAC address - must be unique on your network
static byte mymac[] = { 0x70,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[500]; // TCP/IP send and receive buffer

char data[] = "Hey There!";
const int dstPort PROGMEM = 1234;
const int srcPort PROGMEM = 1234;


//Sending data to destination address
void sendPacketToDest() {
 static byte destip[] = { 192,168,1,50 };
  ether.sendUdp(data, sizeof(data), srcPort, destip, dstPort );
  Serial.println("Packet sent");
 }

void setup(){
  Serial.begin(57600);
  

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
#if STATIC
  ether.staticSetup(myip, gwip);
  Serial.println(F("Connected to ENC28j60"));
#else
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));
#endif

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);
  
}


void loop(){
  // This must be called for ethercard functions to work.
  ether.packetLoop(ether.packetReceive());
  sendPacketToDest();
}
