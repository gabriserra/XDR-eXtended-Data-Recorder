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

#define PORT_TO_RECEIVE			8000
#define NETWORK_INTERFACE 		"en0"

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------

static address	myAddress, carAddress;	// Informations about peers

static int 		sockRecv, sockSend;		// Sockets to send and receive

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// GET MY IP: Return the IP of the server
//------------------------------------------------------------------------------

char*  	getMyIP() {
struct 	ifreq ifr;
	
		ifr.ifr_addr.sa_family = AF_INET;
	
		strncpy(ifr.ifr_name, NETWORK_INTERFACE, IFNAMSIZ-1);
	
		ioctl(sockRecv, SIOCGIFADDR, &ifr);
	
		return inet_ntoa(((address*) &ifr.ifr_addr)->sin_addr);
}

//------------------------------------------------------------------------------
// UDP BIND: Initialization of the structure and execution of the bind operation
//------------------------------------------------------------------------------

static int 	UDPbind(void) {
			// Initialization of the structure with board network's info
			bzero((char *) &myAddress, sizeof(address));
			myAddress.sin_len = (u_char) sizeof(address);
			myAddress.sin_family = AF_INET;
			myAddress.sin_port = htons(PORT_TO_RECEIVE);
			myAddress.sin_addr.s_addr = htonl(INADDR_ANY);
			
			return bind(sockRecv, (sockaddr *) &myAddress, sizeof(address)); 
}

//------------------------------------------------------------------------------
// CREATE CAR ADDRESS: Creation of the structure of the car
//------------------------------------------------------------------------------

static int 	createCarAddress(char * ip, int port) {
			// Initialization of the struct with network's info of Unreal Engine
			bzero((char *) &carAddress, sizeof(address));
			carAddress.sin_len = (u_char) sizeof(address);
			carAddress.sin_family = AF_INET;
			carAddress.sin_port = htons(port);
			carAddress.sin_addr.s_addr = inet_addr(ip);
			return 0;
}

//------------------------------------------------------------------------------
// UDP SEND INIT: Creation of the connection to send
//------------------------------------------------------------------------------

int 		UDPsend_init(char * ip, int port) {
const int 	REUSE_ADDR = 1;			// Constant required to create a connection
	
			if ((sockSend = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
				return -1;
	
			if (setsockopt(sockSend, SOL_SOCKET, SO_REUSEADDR, &REUSE_ADDR, sizeof(int)) < 0)
				return -1;
	
			if (createCarAddress(ip, port) < 0)
				return -1;
	
			return 0;
}

//------------------------------------------------------------------------------
// UDP RECV INIT: Creation of the connection to receive
//------------------------------------------------------------------------------

int 		UDPrecv_init(void) {
const int 	REUSE_ADDR = 1;			// Constant required to create a connection
	
			if ((sockRecv = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
				return -1;
			
			if (setsockopt(sockRecv, SOL_SOCKET, SO_REUSEADDR, &REUSE_ADDR, sizeof(int)) < 0)
				return -1;
			
			if (UDPbind() < 0)
				return -1;
	
			return 0;
}

//------------------------------------------------------------------------------
// UDP SEND: 	Send the server IP to the car
//------------------------------------------------------------------------------

void 	UDPsend(char * ip) {
    	sendto(sockSend, ip, strlen(ip), 0, (sockaddr *) &carAddress, sizeof(address));
}

//------------------------------------------------------------------------------
// UDP RECV: 	Receive sensor's data from the car
//------------------------------------------------------------------------------

int			UDPrecv(sensor_data_g_t * all_d, address * addr) {
socklen_t 	sockAddrSize = sizeof(address);
			return recvfrom(sockRecv, all_d, sizeof(sensor_data_g_t), MSG_WAITALL, (sockaddr *) addr, &sockAddrSize);
}
