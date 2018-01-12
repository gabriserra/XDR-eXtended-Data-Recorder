//------------------------------------------------------------------------------
// UDP: 	Creation and utilization of the structures for UDP communication
//------------------------------------------------------------------------------

#include 	<arpa/inet.h>
#include 	<net/if.h>
#include 	<netinet/in.h>
#include 	<stdio.h>
#include 	<string.h>
#include 	<sys/ioctl.h>
#include 	<sys/socket.h>
#include 	"udp_tcp.h"

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define 	NETWORK_INTERFACE 	"en0"

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------

// Informations about peers
static address	myAddressUDP, myAddressTCP, carAddressUDP, carAddressTCP;

// Sockets UDP and TCP to send and receive
static int 		socket_UDP, socket_TCP;

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// GET MY IP: Return the IP of the server
//------------------------------------------------------------------------------

char* getMyIP() {
	struct 	ifreq ifr;
	
	ifr.ifr_addr.sa_family = AF_INET;
	
	strncpy(ifr.ifr_name, NETWORK_INTERFACE, IFNAMSIZ-1);
	
	ioctl(socket_UDP, SIOCGIFADDR, &ifr);
	
	return inet_ntoa(((address*) &ifr.ifr_addr)->sin_addr);
}

//------------------------------------------------------------------------------
// CREATE MY ADDRESS UDP: Initialization of the structure myAddressUDP
//------------------------------------------------------------------------------

void createMyAddressUDP(int port) {
	bzero((char *) &myAddressUDP, sizeof(address));
	myAddressUDP.sin_len = (u_char) sizeof(address);
	myAddressUDP.sin_family = AF_INET;
	myAddressUDP.sin_port = htons(port);
	myAddressUDP.sin_addr.s_addr = htonl(INADDR_ANY);
}

//------------------------------------------------------------------------------
// INIT UDP SEND: Creation of the UDP connection to send
//------------------------------------------------------------------------------

void init_UDPsend(char * ip, int port) {
	bzero((char *) &carAddressUDP, sizeof(address));
	carAddressUDP.sin_len = (u_char) sizeof(address);
	carAddressUDP.sin_family = AF_INET;
	carAddressUDP.sin_port = htons(port);
	carAddressUDP.sin_addr.s_addr = inet_addr(ip);
}

//------------------------------------------------------------------------------
// UDP RECV INIT: Creation of the UDP connection to receive
//------------------------------------------------------------------------------

int init_UDPrecv(int port) {
	const int REUSE_ADDR = 1;
	
	if ((socket_UDP = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		return -1;
	
	if (setsockopt(socket_UDP, SOL_SOCKET, SO_REUSEADDR, &REUSE_ADDR, sizeof(int)) < 0)
		return -1;
	
	createMyAddressUDP(port);
	
	if (bind(socket_UDP, (sockaddr *) &myAddressUDP, sizeof(myAddressUDP)) < 0)
		return -1;
	
	return socket_UDP;
}

//------------------------------------------------------------------------------
// UDP SEND: 	Send the server IP to the car
//------------------------------------------------------------------------------

ssize_t UDPsend(char * ip){
	return sendto(socket_UDP, ip, strlen(ip), 0, (sockaddr *) &carAddressUDP,sizeof(carAddressUDP));
}

//------------------------------------------------------------------------------
// UDP RECV: 	Receive port and ip from the car
//------------------------------------------------------------------------------

ssize_t	UDPrecv(char * port_ip, int size) {
	return recv(socket_UDP, port_ip, size, MSG_WAITALL);
}

//------------------------------------------------------------------------------
// CREATE MY ADDRESS TCP: Initialization of the structure myAddressTCP
//------------------------------------------------------------------------------

void createMyAddressTCP(int port) {
	bzero((char *) &myAddressTCP, sizeof(address));
	myAddressTCP.sin_len = (u_char) sizeof(address);
	myAddressTCP.sin_family = AF_INET;
	myAddressTCP.sin_port = htons(port);
	myAddressTCP.sin_addr.s_addr = htonl(INADDR_ANY);
}

//------------------------------------------------------------------------------
// CREATE SERVER ADDRESS: Initialization of the structure carAddressTCP
//------------------------------------------------------------------------------

void createCarAddressTCP(char * ip, int port) {
	bzero((char *) &carAddressTCP, sizeof(address));
	carAddressTCP.sin_len = (u_char) sizeof(address);
	carAddressTCP.sin_family = AF_INET;
	carAddressTCP.sin_port = htons(port);
	carAddressTCP.sin_addr.s_addr = inet_addr(ip);
}

//------------------------------------------------------------------------------
// INIT TCP SERVER: Creation of the TCP connection as server
//------------------------------------------------------------------------------

int init_TCPserver(int port) {
	int listener;
	const int REUSE_ADDR = 1;
	socklen_t address_size = sizeof(carAddressTCP);
	
	if ((socket_TCP = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return -1;
	
	if (setsockopt(socket_TCP, SOL_SOCKET, SO_REUSEADDR, &REUSE_ADDR, sizeof(int)) < 0)
		return -1;
	
	createMyAddressTCP(port);
	
	if (bind(socket_TCP,(sockaddr *) &myAddressTCP, sizeof(myAddressTCP)) < 0)
		return -1;
	
	if (listen(socket_TCP, 1) < 0)
		return -1;
	
	if ((socket_TCP = accept(socket_TCP, (sockaddr *) &carAddressTCP, &address_size)) < 0)
		return -1;
		
	return socket_TCP;
}

//------------------------------------------------------------------------------
// INIT TCP CLIENT: Creation of the TCP connection as client
//------------------------------------------------------------------------------

int init_TCPclient(char * ip, int port) {
	if ((socket_TCP = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return -1;
	
	createCarAddressTCP(ip, port);
	
	if (connect(socket_TCP,(sockaddr *) &carAddressTCP, sizeof(carAddressTCP)) < 0)
		return -1;
	
	return socket_TCP;
}

//------------------------------------------------------------------------------
// UDP SEND: 	Send a message to the car eventually
//------------------------------------------------------------------------------

ssize_t TCPsend(char * mes){
	return send(socket_TCP, mes, strlen(mes), 0);
}

//------------------------------------------------------------------------------
// UDP RECV: 	Receive sensor's data from the car
//------------------------------------------------------------------------------

ssize_t	TCPrecv(sensor_data_g_t * all_d) {
	return recv(socket_TCP, all_d, sizeof(sensor_data_g_t), MSG_WAITALL);
}

//------------------------------------------------------------------------------
// UDP RECV: 	Receive string from the server
//------------------------------------------------------------------------------

ssize_t	TCPrecv_string(char * mes) {
	return recv(socket_TCP, mes, BUFFER_SIZE, MSG_WAITALL);
}
