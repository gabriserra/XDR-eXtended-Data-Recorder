//------------------------------------------------------------------------------
// SERVER: 	Server to receive data from the car
//
// COMPILE COMMAND: clear && gcc server.c udp.c -o server && ./server
//------------------------------------------------------------------------------

#include 	<arpa/inet.h>
#include 	<errno.h>
#include 	<inttypes.h>
#include 	<netinet/in.h>
#include 	<stdio.h>
#include 	<string.h>
#include 	<sys/select.h>
#include 	<sys/socket.h>
#include 	<time.h>
#include 	"tcp.h"

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define 	MY_PORT			7000
//#define 	SERVER_IP		"gabripr0.altervista.org"
#define 	SERVER_IP		"104.28.22.117"
#define 	SERVER_PORT		80
#define		TRUE			1
#define		FALSE			0

//------------------------------------------------------------------------------
// GLOBAL STRUCTURES
//------------------------------------------------------------------------------

typedef struct tm* tm_t;

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------

int 	sockt_TCP, fdmax = 0, i;
char 	buffer[BUFFER_SIZE];
char 	*query = "GET /search?q=arduino HTTP/1.1\nHost: www.google.com\nConnection: close\n\n";
ssize_t recvBytes;
fd_set 	master, read_fds;

//------------------------------------------------------------------------------
// CLEAR BUFFER: Clear stdin
//------------------------------------------------------------------------------

void clearBuffer() {
	int c;
	while((c = getchar())!='\n' && c != '\0') {}
}

//------------------------------------------------------------------------------
// MAIN: Server body
//------------------------------------------------------------------------------

int main() {
	if ((sockt_TCP = TCP_init(MY_PORT, SERVER_IP, SERVER_PORT)) < 0) {
		perror("ERROR IN TCP INIT: ERROR\n");
		fflush(stdout);
		return 0;
	}

	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	FD_SET(sockt_TCP, &master);
	if (fdmax < sockt_TCP)
		fdmax = sockt_TCP;
	
	TCPsend(query);

	while(1) {
		read_fds = master;
		if(select(fdmax+1, &read_fds, NULL, NULL, NULL) < 0) {
			printf("ERROR IN TCP SELECT\n");
			fflush(stdout);
			return 0;
		}
		
		for(i = 0; i <= fdmax; i++){
			if(FD_ISSET(i, &read_fds)){
				switch(i) {
					default:
						recvBytes = TCPrecv(buffer);
						printf("%s\n",buffer);
						break;
				}
			}
		}
	}
	
	//callMatlabScript()
	
	TCPsend(query);
}
