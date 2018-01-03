#include "ESP8266.h"
#include "GY521.h"

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define DEFUALT_LED_PIN    13  // Predefined board's led pin

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------

//const char *SSID     = "TIM-90340813_2.4Hz";
//const char *PASSWORD = "bJMzBlXdf10x3E8RfgTG98oE";

const char *SSID     = "Alice-73100401";
const char *PASSWORD = "u3b1kz4btdvt4gzokiik6eff";

//const char *SSID     = "XDR";
//const char *PASSWORD = "BSBXDRBSB";

uint32_t MY_PORT = 9000;
uint32_t SERVER_PORT = 8000;
char SERVER_ADDRESS[16];
char BROADCAST_ADDRESS[16];

SoftwareSerial mySerial(10, 11);
ESP8266 wifi(mySerial);

const int MPU = 0x68;
GY521 acc_gy(MPU);

sensor_data_g_t all_d;

uint32_t seq_num;

//------------------------------------------------------------------------------
// COMPUTE BROADCAST ADDRESS: 	Given the local IP compute the brodcast address
//								considering a network mask /24.
//------------------------------------------------------------------------------

void computeBroadcastAddress() {
	int n_dots = 0;
  String IP = wifi.getLocalIP();
  char myIP[IP.length()+1];
	IP.toCharArray(myIP, IP.length()+1);
	for(int i=0; n_dots < 3; i++) {
    BROADCAST_ADDRESS[i] = myIP[i];
		if (myIP[i] == '.') {
			n_dots++;
			if (n_dots == 3) {
				BROADCAST_ADDRESS[++i] = '2';
				BROADCAST_ADDRESS[++i] = '5';
				BROADCAST_ADDRESS[++i] = '5';
			}
		}
	}

}

//------------------------------------------------------------------------------
// SEND QUERY: Send a MySQL query to the server
//------------------------------------------------------------------------------

void sendQuery() {
  acc_gy.previous_t = millis();
	all_d = acc_gy.getAllDouble();
	String query = "INSERT INTO table_name (timestamp, acc_x, acc_y, acc_z, gy_x, gy_y, gy_z) VALUES (" + String(all_d.ax,DEC) + "," + String(all_d.ay,DEC) + "," + String(all_d.az,DEC) + "," + String(all_d.gx,DEC) + "," + String(all_d.gy,DEC) + "," + String(all_d.gz,DEC) + ")";
	Serial.println(query);
	char mes[query.length()+1];
	query.toCharArray(mes, query.length()+1);
	Serial.println(mes);
	wifi.send(0, mes, sizeof(mes));
}

//------------------------------------------------------------------------------
// SEND STRUCT: Send a struct to the server with acc/gy data
//------------------------------------------------------------------------------

void sendStruct() {
  acc_gy.previous_t = millis();
	all_d = acc_gy.getAllDouble();
	all_d.seq_num = seq_num;
	wifi.send(0, (char*)&all_d, sizeof(all_d));
}

//------------------------------------------------------------------------------
// CONNECT TO AP: Connect ESP8266 module to the access point
//------------------------------------------------------------------------------

void connectToAP(){
	if (!wifi.init(SSID, PASSWORD)) {
		Serial.println(F("WI-FI CONNECTION FAILED."));
    digitalWrite(DEFUALT_LED_PIN, LOW);
		while (true);
	}
    
	Serial.print(F("CONNECTION ESTABLISHED: "));
	Serial.println(wifi.getLocalIP().c_str());
}

//------------------------------------------------------------------------------
// CONNECT TO SERVER: Create UDP connection with the server
//------------------------------------------------------------------------------

void connectToServer(){
	if (!wifi.registerUDP(1,wifi.getLocalIP().c_str(), MY_PORT, MY_PORT, 2)) {
		Serial.println(F("UDP RECV CONNECTION ERROR"));
    digitalWrite(DEFUALT_LED_PIN, LOW);
		while (true);
	}
  else
  	Serial.println(F("UDP RECV CONNECTION OK"));
	
	computeBroadcastAddress();
  Serial.print(F("BROADCAST ADDRESS: "));
  Serial.println(BROADCAST_ADDRESS);

	if (!wifi.registerUDP(0,BROADCAST_ADDRESS, SERVER_PORT)) {
		Serial.println(F("UDP SEND BROADCAST CONNECTION ERROR"));
    digitalWrite(DEFUALT_LED_PIN, LOW);
		while (true);
	}
 	else
 		Serial.println(F("UDP SEND BROADCAST CONNECTION OK"));

	wifi.send(0, (char *)&MY_PORT, sizeof(MY_PORT));

	int recvBytes = wifi.recv(1, SERVER_ADDRESS, sizeof(SERVER_ADDRESS), 5000);
    SERVER_ADDRESS[recvBytes+1] = "\0";
    Serial.print(F("SERVER ADDRESS: "));
    Serial.println(SERVER_ADDRESS);

	if (!wifi.registerUDP(0,SERVER_ADDRESS, SERVER_PORT)) {
  
		Serial.println(F("UDP SEND TO SERVER CONNECTION ERROR"));
    digitalWrite(DEFUALT_LED_PIN, LOW);
		while (true);
	}
 	else
  		Serial.println(F("UDP SEND TO SERVER CONNECTION OK"));
}

//------------------------------------------------------------------------------
// SETUP: Initialize all the needed variables
//------------------------------------------------------------------------------

void setup(void) {
  delay(1000);
  digitalWrite(DEFUALT_LED_PIN, LOW);
	seq_num = 0;
	Serial.begin(9600);

  delay(1000);

  digitalWrite(DEFUALT_LED_PIN, HIGH);
	connectToAP();
  digitalWrite(DEFUALT_LED_PIN, LOW);

  delay(1000);

  digitalWrite(DEFUALT_LED_PIN, HIGH);
	connectToServer();
  digitalWrite(DEFUALT_LED_PIN, LOW);

  delay(1000);

  digitalWrite(DEFUALT_LED_PIN, HIGH);
	acc_gy.init();
	acc_gy.calibrate();
  digitalWrite(DEFUALT_LED_PIN, LOW);
}

//------------------------------------------------------------------------------
// LOOP:	
//------------------------------------------------------------------------------

void loop(void) {
	sendStruct();
	seq_num++;
}
