#include <SPI.h>
#include <Ethernet.h>

int led = 7;
int vrecebido = -2;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(31,220,104,115);  // numeric IP for Google (no DNS)
char server[] = "minhaautomacao.hol.es";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,1,100);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  
  pinMode(led, OUTPUT);
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /controller/estado.php HTTP/1.1");
    client.println("User-Agent: Arduino"); // nome do agente
    client.println("Accept: text/html");
    client.println("Host: minhaautomacao.hol.es/");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  // String DatEth;
   client.println("GET /controller/estado.php HTTP/1.1");
   client.println();

  if (client.available()) {
    char c = client.read();
    Serial.println(c);
    vrecebido=c;
    //DatEth.concat(c);
    //if(DatEth.endsWith("/controle.php?valor=1")) {vrecebido = 1; Serial.println(vrecebido);}
    //if(DatEth.endsWith("/controle.php?valor=0")) {vrecebido = 0; Serial.println(vrecebido);}
    }
    
   
  
 if(vrecebido>0){
    if(vrecebido== '1'){
    digitalWrite(led,HIGH);
    Serial.print(HIGH);
    delay(300);
}else if(vrecebido== '0'){
    digitalWrite(led, LOW);
    Serial.print(LOW);
    delay(300);
}
vrecebido=-2;
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}}

