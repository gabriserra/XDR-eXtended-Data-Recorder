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
#include 	"udp_tcp.h"

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define 	MY_PORT			7000
//#define 	SERVER_IP		"gabripr0.altervista.org"
#define 	SERVER_IP		"104.28.23.117"
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
//char 	*query = "GET /XDR/insertdata/insertdata.php HTTP/1.1\nHost: www.gabripr0.altervista.org\nConnection: close\n\n";
char 	*query = "POST /XDR/insertdata/insertdata.php HTTP/1.1\n\
Host: www.gabripr0.altervista.org\n\
Content-Type: application/x-www-form-urlencoded\n\
Connection: close\n\
Content-Length: 408\n\n\
content={\
\"email\" :\
\"user@example.it\",\
\"trip\" : {\
\"meters\" : 50,\
\"starttime\" : \"2018-01-07 07:30:00\",\
\"secondslength\" : 120\
},\
\"stat\" : {\
\"numberacc\" : 2,\
\"worstacc\" : 5,\
\"numberbra\" : 1,\
\"worstbra\" : 3,\
\"numbercur\" : 8\
},\
\"evaluation\" : {\
\"pointstotal\" : 2,\
\"pointsacceleration\" : 5,\
\"pointsbraking\" : 1,\
\"pointssteering\" : 3,\
\"pointsspeed\" : 8\
},\
\"crash\" : {\
\"crashtime\" : \"2018-01-07 07:30:00\",\
\"intensity\" : 5,\
\"stationary\" : 0\
}\
}\n\n";

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
	if ((sockt_TCP = init_TCPclient(SERVER_IP, SERVER_PORT)) < 0) {
		perror("ERROR IN TCP INIT: ERROR\n");
		fflush(stdout);
		return 0;
	}
	
	printf("CONNECTION ESTABLISHED\n");

	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	FD_SET(sockt_TCP, &master);
	if (fdmax < sockt_TCP)
		fdmax = sockt_TCP;
	
	//printf("%s\n",query);
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
						recvBytes = TCPrecv_string(buffer);
						printf("%s\n",buffer);
						break;
				}
			}
		}
	}
	
	//callMatlabScript()
	
	TCPsend(query);
}
