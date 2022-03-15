// Ping a range of ip on a specific port
// Find if a server is available
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// IP address if DHCP failed
IPAddress ip(192, 168, 0, 177);

// Patern of an ip address except the fourth
IPAddress server(192, 168, 0, 0);
// Start ip to end ip
byte range[2] = {2, 50};

// Server port
unsigned int port = 10002;

EthernetClient client;

void setup() {
  Serial.begin(115200);
  Serial.println("\nInitialize ethernet shield");

  if (Ethernet.begin(mac) == 0) {
    Serial.println("DHCP failed");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("No shield");
      while (true) delay(1);
    }
    while(Ethernet.linkStatus() == LinkOFF) {
      Serial.println("No cable");
      delay(500);
    }
    Ethernet.begin(mac, ip);
  }

  delay(1000);
  Serial.print("Start ping on port: ");
  Serial.println(port);
  Serial.print("Range: ");
  server[3] = range[0];
  Serial.print(server);
  Serial.print(" to ");
  server[3] = range[1] - 1;
  Serial.println(server);
  for (byte i = range[0]; i < range[1]; i++) {
    // Change the last byte by the range
    server[3] = i;
    // Test the connection
    // Take 1sec per connection
    if (client.connect(server, port)) {
      client.stop();
      Serial.print("  Connect on ip: ");
      Serial.println(server);
    }
  }
  Serial.println("Ping ends");
}

void loop() {

}
