#include "ESP8266.h"
#include "GY521.h"

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define	SERIAL_BAUDRATE		9600
#define ESP_BAUDRATE 		57600
#define	PERIOD				25

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------

const char *SSID     = "TIM-90340813_2.4Hz";
const char *PASSWORD = "bJMzBlXdf10x3E8RfgTG98oE";

//const char *SSID     = "Alice-73100401";
//const char *PASSWORD = "u3b1kz4btdvt4gzokiik6eff";

//const char *SSID     = "XDR";
//const char *PASSWORD = "BSBXDRBSB";

uint32_t MY_PORT = 9000;
uint32_t SERVER_PORT = 8000;
char SERVER_ADDRESS[16];
char BROADCAST_ADDRESS[16];

SoftwareSerial mySerial(10, 11);
ESP8266 wifi(mySerial, ESP_BAUDRATE);

const int MPU = 0x68;
GY521 acc_gy(MPU);

uint32_t seq_num;

data_t all_d;

//uint32_t t;
//int32_t d;

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
// SEND STRUCT: Send a struct to the server with acc/gy data
//------------------------------------------------------------------------------

void sendStruct() {
	all_d = acc_gy.getData(t, seq_num++);
	wifi.send(0, (char*)&all_d, sizeof(all_d));
}

//------------------------------------------------------------------------------
// CONNECT TO AP: Connect ESP8266 module to the access point
//------------------------------------------------------------------------------

bool connectToAP(){
	if (!wifi.init(SSID, PASSWORD, ESP_BAUDRATE)) {
		Serial.println(F("WI-FI CONNECTION FAILED."));
		return false;
	}
    
	Serial.print(F("CONNECTION ESTABLISHED: "));
	Serial.println(wifi.getLocalIP().c_str());
	return true;
}

//------------------------------------------------------------------------------
// CONNECT TO SERVER: Create UDP connection with the server
//------------------------------------------------------------------------------

bool connectToServer(){
	if (!wifi.registerUDP(1,wifi.getLocalIP().c_str(), MY_PORT, MY_PORT, 2)) {
		Serial.println(F("UDP RECV CONNECTION ERROR"));
		return false;
	}
	else
		Serial.println(F("UDP RECV CONNECTION OK"));

	computeBroadcastAddress();
	Serial.print(F("BROADCAST ADDRESS: "));
	Serial.println(BROADCAST_ADDRESS);

	if (!wifi.registerUDP(0,BROADCAST_ADDRESS, SERVER_PORT)) {
		Serial.println(F("UDP SEND BROADCAST CONNECTION ERROR"));
		return false;
	}
	else
		Serial.println(F("UDP SEND BROADCAST CONNECTION OK"));

	wifi.send(0, (char *)&MY_PORT, sizeof(MY_PORT));

	String IP = wifi.getLocalIP();
	char myIP[16];
	IP.toCharArray(myIP, IP.length()+1);

	wifi.send(0, myIP, 16);

	int recvBytes = wifi.recv(1, SERVER_ADDRESS, sizeof(SERVER_ADDRESS), 5000);
	SERVER_ADDRESS[recvBytes+1] = "\0";
	Serial.print(F("SERVER ADDRESS: "));
	Serial.println(SERVER_ADDRESS);

	if (!wifi.registerUDP(0,SERVER_ADDRESS, SERVER_PORT)) {
		Serial.println(F("UDP SEND TO SERVER CONNECTION ERROR"));
		return false;
	}
	else
		Serial.println(F("UDP SEND TO SERVER CONNECTION OK"));
	
	return true;
}

//------------------------------------------------------------------------------
// SETUP: Initialize all the needed variables
//------------------------------------------------------------------------------

void setup(void) {
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	Serial.begin(9600);
	delay(1000);
	Serial.println(F("STARTING APPLICATION"));
	seq_num = 0;
	while (!connectToAP()) {delay(1000);}
	delay(1000);
	while (!connectToServer()) {delay(1000);}
	acc_gy.init();
	//digitalWrite(LED_BUILTIN, HIGH);
	//acc_gy.calibrate();
	//digitalWrite(LED_BUILTIN, LOW);
}

//------------------------------------------------------------------------------
// LOOP: Body of the application running in the car
//------------------------------------------------------------------------------

void loop(void) {
	//t = millis();
	sendStruct();
  	//d = PERIOD - millis() + t;
  	//if (d > 0)
	//	delay(d);
}
