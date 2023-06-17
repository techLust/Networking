// Present a "Will be back soon web page", as stand-in webserver.
// 2011-01-30 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php
 
#include <EtherCard.h>
#include <SPI.h>
//#include <Ethernet.h>
//#include <EthernetUdp.h>

#define STATIC 1  // set to 1 to disable DHCP (adjust myip/gwip values below)

#if STATIC
// ethernet interface ip address
static byte myip[] = { 192,168,1,20 };
// gateway ip address
static byte gwip[] = { 192,168,1,50 };
#endif

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[500]; // tcp/ip send and receive buffer

const char page[] PROGMEM =
"HTTP/1.0 503 Service Unavailable\r\n"
"Content-Type: text/html\r\n"
"Retry-After: 600\r\n"
"\r\n"
"<html>"
  "<head><title>"
    "ENC28j60 connected"
  "</title></head>"
  "<body>"
  "<center>"
    "<br>"
    "<h3>ENC28j60 connected with Arduno UNO</h3>"
    "<hr>"
    "<h4>Great success!</h4>"
    "<p><em>"
      "Server is pinging on 192.168.1.20 .<br />"
    "</em></p>"
    "</center>"
  "</body>"
"</html>"
;

void setup(){
  Serial.begin(57600);
  Serial.println("-------------- ECN28j60 connection with Arduino UNO -------------------");
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println( "Failed to access Ethernet controller");
#if STATIC
  Serial.println("Connected with the server");
  ether.staticSetup(myip, gwip);
#else
  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");
#endif

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  
}

void loop(){
  // wait for an incoming TCP packet, but ignore its contents
  if (ether.packetLoop(ether.packetReceive())) {
    memcpy_P(ether.tcpOffset(), page, sizeof page);
    ether.httpServerReply(sizeof page - 1);
  }
}
