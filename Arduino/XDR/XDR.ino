#include "ESP8266.h"
#include "GY521.h"

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define	SERIAL_BAUDRATE		2000000
#define ESP_BAUDRATE 		57600
#define PERIOD         		20
#define UDP

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------

//const char *SSID     = "TIM-90340813_2.4Hz";
//const char *PASSWORD = "bJMzBlXdf10x3E8RfgTG98oE";

//const char *SSID     = "Alice-73100401";
//const char *PASSWORD = "u3b1kz4btdvt4gzokiik6eff";

//const char *SSID     = "XDR";
//const char *PASSWORD = "BSBXDRBSB";

//const char *SSID     = "iPhone di Silvio";
//const char *PASSWORD = "12345678";

const char *SSID     = "Mi Phone";
const char *PASSWORD = "";

uint32_t MY_UDP_PORT = 9000;
uint32_t MY_TCP_PORT = 9001;

uint32_t SERVER_UDP_PORT = 8000;
uint32_t SERVER_TCP_PORT = 8001;

uint8_t recv_mux_id = 1; 
uint8_t send_mux_id = 0;

char SERVER_ADDRESS[16];
char BROADCAST_ADDRESS[16];

SoftwareSerial mySerial(10, 11);
ESP8266 wifi(mySerial, ESP_BAUDRATE);

const int MPU = 0x68;
GY521 acc_gy(MPU);

uint32_t seq_num;

data_t all_d;

uint32_t t;
int32_t d;

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
	all_d = acc_gy.getData(millis(), seq_num++);
	#ifdef UDP
		if (!wifi.send(send_mux_id, (char*)&all_d, sizeof(all_d)))
			Serial.println(F("SEND STRUCT FAILED"));
	#else
		if (!wifi.send((char*)&all_d, sizeof(all_d)))
			Serial.println(F("SEND STRUCT FAILED"));
	#endif
}


//------------------------------------------------------------------------------
// CONNECT TO AP: Connect to the access point and prepare the UDP connection
//------------------------------------------------------------------------------

bool connectToAP(){
	if (!wifi.init_UDP(SSID, PASSWORD)) {
		Serial.println(F("UDP INIT FAILED"));
		digitalWrite(LED_BUILTIN, HIGH);
		return false;
	}

	Serial.print(F("UDP INIT COMPLETE"));
	Serial.print(F("CONNECTION ESTABLISHED: "));
	Serial.println(wifi.getLocalIP().c_str());
	return true;
}

//------------------------------------------------------------------------------
// INIT UDP: Initialize UDP connection
//------------------------------------------------------------------------------

bool init_UDP(){
	if (!wifi.registerUDP(recv_mux_id,wifi.getLocalIP().c_str(), MY_UDP_PORT, MY_UDP_PORT, 2)) {
		Serial.println(F("UDP RECV CONNECTION ERROR"));
		digitalWrite(LED_BUILTIN, HIGH);
		return false;
	}
	else
		Serial.println(F("UDP RECV CONNECTION OK"));

	computeBroadcastAddress();
	Serial.print(F("BROADCAST ADDRESS: "));
	Serial.println(BROADCAST_ADDRESS);

	if (!wifi.registerUDP(send_mux_id,BROADCAST_ADDRESS, SERVER_UDP_PORT)) {
		Serial.println(F("UDP SEND BROADCAST CONNECTION ERROR"));
		digitalWrite(LED_BUILTIN, HIGH);
		return false;
	}
	else
		Serial.println(F("UDP SEND BROADCAST CONNECTION OK"));

	String PORT_IP = String(MY_UDP_PORT) + wifi.getLocalIP();
	char myPORT_IP[20];
	PORT_IP.toCharArray(myPORT_IP, PORT_IP.length()+1);

	if (!wifi.send(send_mux_id, myPORT_IP, 20)) {
		Serial.println(F("SENT MY PORT AND IP FAILED"));
		digitalWrite(LED_BUILTIN, HIGH);
		return false;
	}
	else
		Serial.println(F("SENT MY PORT AND IP OK"));

	if(int recvBytes = wifi.recv(recv_mux_id, SERVER_ADDRESS, sizeof(SERVER_ADDRESS), 5000) < 7) {
		Serial.println(F("SERVER NOT RECEIVED"));
		return false;
	}

	Serial.print(F("SERVER ADDRESS: "));
	Serial.println(SERVER_ADDRESS);

	#ifdef UDP
		send_mux_id = 2;
		if (!wifi.registerUDP(send_mux_id,SERVER_ADDRESS, SERVER_UDP_PORT)) {
			Serial.println(F("UDP SEND SERVER CONNECTION ERROR"));
			return false;
		}
	#endif

	return true;
}

//------------------------------------------------------------------------------
// INIT TCP: Initialize TCP connection
//------------------------------------------------------------------------------

bool init_TCP(){
	if (!wifi.init_TCP(recv_mux_id, send_mux_id)) {
		Serial.println(F("TCP INIT FAILED"));
		digitalWrite(LED_BUILTIN, HIGH);
		return false;
	}
	
	Serial.println(F("TCP INIT COMPLETE"));

	if (!wifi.createTCP(SERVER_ADDRESS, SERVER_TCP_PORT)) {
		Serial.println(F("TCP CONNECTION ERROR"));
		digitalWrite(LED_BUILTIN, HIGH);
		return false;
	}
	else
		Serial.println(F("TCP CONNECTION OK"));
	
	return true;
}

//------------------------------------------------------------------------------
// SETUP: Initialize all the needed variables
//------------------------------------------------------------------------------

void setup(void) {
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	Serial.begin(SERIAL_BAUDRATE);
	delay(1000);
	Serial.println(F("STARTING APPLICATION"));
	seq_num = 0;
	while (!wifi.autoSetBaud(ESP_BAUDRATE)) {delay(1000); Serial.println(F("AUTO SET BAUDRATE FAILED")); delay(1000);}
	while (!connectToAP()) {delay(1000); digitalWrite(LED_BUILTIN, LOW); delay(1000);}
	delay(1000);

	#ifdef UDP
		while (!init_UDP()) {delay(1000); digitalWrite(LED_BUILTIN, LOW); delay(1000);}
	#else
		while (!init_UDP() || !init_TCP()) {delay(1000); digitalWrite(LED_BUILTIN, LOW); delay(1000);}
	#endif

	acc_gy.init();
	digitalWrite(LED_BUILTIN, HIGH);
	acc_gy.calibrate();
	digitalWrite(LED_BUILTIN, LOW);
}

//------------------------------------------------------------------------------
// LOOP: Body of the application running in the car
//------------------------------------------------------------------------------

void loop(void) {
	t = millis();
	sendStruct();
	d = PERIOD - millis() + t;
	if(d > 0)
		delay(d);
}
