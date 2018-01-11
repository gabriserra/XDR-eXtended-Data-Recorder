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
#include 	"udp.h"

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define 	NETWORK_INTERFACE 	"en0"

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------

static address	myAddress, carAddress;	// Informations about peers

static int 		socket_UDP;		// Sockets to send and receive

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
// CREATE MY ADDRESS: Initialization of the structure myAddress
//------------------------------------------------------------------------------

void createMyAddress(int port) {
	bzero((char *) &myAddress, sizeof(address));
	myAddress.sin_len = (u_char) sizeof(address);
	myAddress.sin_family = AF_INET;
	myAddress.sin_port = htons(port);
	myAddress.sin_addr.s_addr = htonl(INADDR_ANY);
}

//------------------------------------------------------------------------------
// CREATE CAR ADDRESS: Initialization of the structure carAddress
//------------------------------------------------------------------------------

void createCarAddress(char * ip, int port) {
	bzero((char *) &carAddress, sizeof(address));
	carAddress.sin_len = (u_char) sizeof(address);
	carAddress.sin_family = AF_INET;
	carAddress.sin_port = htons(port);
	carAddress.sin_addr.s_addr = inet_addr(ip);
}

//------------------------------------------------------------------------------
// UDP RECV INIT: Creation of the connection to receive
//------------------------------------------------------------------------------

int UDPrecv_init(int port) {
	const int REUSE_ADDR = 1;
	
	if ((socket_UDP = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		return -1;
	
	if (setsockopt(socket_UDP, SOL_SOCKET, SO_REUSEADDR, &REUSE_ADDR, sizeof(int)) < 0)
		return -1;
	
	createMyAddress(port);
	
	if (bind(socket_UDP, (sockaddr *) &myAddress, sizeof(myAddress)) < 0)
		return -1;
		
	return socket_UDP;
}

//------------------------------------------------------------------------------
// UDP SEND: 	Send the server IP to the car
//------------------------------------------------------------------------------

ssize_t UDPsend(char * ip){
	return sendto(socket_UDP, ip, strlen(ip), 0, (sockaddr *) &carAddress,sizeof(carAddress));
}

//------------------------------------------------------------------------------
// UDP RECV: 	Receive sensor's data from the car
//------------------------------------------------------------------------------

ssize_t	UDPrecv(sensor_data_g_t * all_d) {
	return recv(socket_UDP, all_d, sizeof(sensor_data_g_t), MSG_WAITALL);
}
