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
#include 	"tcp.h"

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define 	NETWORK_INTERFACE 	"en0"

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------

static address	myAddress, serverAddress;	// Informations about peers

static int 		socket_TCP;		// Sockets to send and receive

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

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
// CREATE SERVER ADDRESS: Initialization of the structure serverAddress
//------------------------------------------------------------------------------

void createServerAddress(char * ip, int port) {
	bzero((char *) &serverAddress, sizeof(address));
	serverAddress.sin_len = (u_char) sizeof(address);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = inet_addr(ip);
}

//------------------------------------------------------------------------------
// TCP INIT: Creation of the connection with the web server
//------------------------------------------------------------------------------

int TCP_init(int myPort, char * ip, int serverPort) {
	const int REUSE_ADDR = 1;
	
	if ((socket_TCP = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("ERRORE 1\n");
		return -1;
	}
	
	if (setsockopt(socket_TCP, SOL_SOCKET, SO_REUSEADDR, &REUSE_ADDR, sizeof(int)) < 0){
		printf("ERRORE 2\n");
		return -1;
	}
	
	createMyAddress(myPort);
	
	createServerAddress(ip, serverPort);
	
	if (connect(socket_TCP,(sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){
		printf("ERRORE 3\n");
		return -1;
	}
		
	return socket_TCP;
}

//------------------------------------------------------------------------------
// UDP SEND: 	Send the server IP to the car
//------------------------------------------------------------------------------

ssize_t TCPsend(char * mes){
	return send(socket_TCP, mes, strlen(mes), 0);
}

//------------------------------------------------------------------------------
// UDP RECV: 	Receive sensor's data from the car
//------------------------------------------------------------------------------

ssize_t	TCPrecv(char * mes) {
	return recv(socket_TCP, mes, BUFFER_SIZE, MSG_WAITALL);
}
