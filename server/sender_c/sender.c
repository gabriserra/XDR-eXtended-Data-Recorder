//------------------------------------------------------------------------------
// SERVER: 	Server to receive data from the car
//
// COMPILE COMMAND: clear && gcc server.c udp.c -o server && ./server
//------------------------------------------------------------------------------

#include 	<arpa/inet.h>
#include 	<errno.h>
#include 	<inttypes.h>
#include 	<json-c/json.h>
#include 	<netinet/in.h>
#include 	<signal.h>
#include 	<stdio.h>
#include 	<string.h>
#include 	<sys/select.h>
#include 	<sys/socket.h>
#include 	<time.h>
#include 	<unistd.h>
#include 	"udp_tcp.h"

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define 	MY_PORT			7000
//#define 	SERVER_IP		"gabripr0.altervista.org"
#define 	SERVER_IP		"104.28.23.117"
#define 	SERVER_PORT		80

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
char *HEADER_HTTP = "POST /XDR/insertdata/insertdata.php HTTP/1.1\n\
Host: www.gabripr0.altervista.org\n\
Content-Type: application/x-www-form-urlencoded\n\
Connection: close\n\
Content-Length: ";

char *FOOTER_HTTP = "\n\n";

ssize_t recvBytes;
fd_set 	master, read_fds;

//------------------------------------------------------------------------------
// CALL MATLAB SCRIPT: Call Matlab script to process data
//------------------------------------------------------------------------------

void callMatlabScript(char * filename) {
	char path[1024];
	char cmd[1024];
	char sd[1024];
	
	printf("PROCESSING DATA IN MATLAB\n\n");
	
	if (getcwd(path, sizeof(path)) == NULL) {
		printf("PROCESSING DATA FAILED: RETRIEVING CURRENT PATH FAILED\n");
		return;
	}
	
	char *matlab = "/Applications/MATLAB_R2016b.app/bin/matlab";
	char *run_script = "\"; \"../matlab_c/prova\"";
	char *options = " -nodisplay -nosplash -noFigureWindows";
	int pid = getpid();
	sprintf(sd, "%s%s%s%s%s", " -r \"cd('", path, "'); cd('../matlab_c'); computeLossPackets('",filename,"'); quit\" > /dev/null");
	sprintf(cmd, "%s%s%s", matlab, options, sd);
	system(cmd);
}

//------------------------------------------------------------------------------
// PARSE HTTP REPLY:
//------------------------------------------------------------------------------

void parseHttpReply(char * reply) {
	char * start;
	int token_found;
	if((start = strstr(reply, "\" }")) != NULL) {
		*start = '\0';
	}
	
	if((start = strstr(reply, "{ \"error\" : true")) != NULL) {
		start = strstr(reply, "\"message\" : \"") + 8;
		printf("ERROR WHILE INSERTING DATA IN DATABSE: %s\n\n", start);
	}
	else if((start = strstr(reply, "{ \"error\" : false")) != NULL) {
		printf("UPLOAD ON THE WEB SERVER SUCCESFULLY\n\n");
	}
}

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
	FILE* fp;
	char json_content[1024];
	
	if ((sockt_TCP = init_TCPclient(SERVER_IP, SERVER_PORT)) < 0) {
		perror("ERROR IN TCP INIT: ERROR\n");
		fflush(stdout);
		return 0;
	}
	
	printf("CONNECTION ESTABLISHED\n\n");

	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	FD_SET(sockt_TCP, &master);
	if (fdmax < sockt_TCP)
		fdmax = sockt_TCP;
	
	callMatlabScript("../log/log_2018-01-15_10-57-23.csv");
	
	fp = fopen("../matlab_c/tmp.txt", "r");
	fgets(json_content, 1024, fp);
	fclose(fp);

	char buffer[1024];
	sprintf(buffer, "%s%lu%s%s%s", HEADER_HTTP, strlen(json_content),"\n\n", json_content, FOOTER_HTTP);
	TCPsend(buffer);
	
	read_fds = master;
	if(select(fdmax+1, &read_fds, NULL, NULL, NULL) < 0) {
		printf("ERROR IN TCP SELECT\n");
		fflush(stdout);
		return 0;
	}
	
	char buffer_2[1024];
	
	for(i = 0; i <= fdmax; i++){
		if(FD_ISSET(i, &read_fds)){
			switch(i) {
				default:
					recvBytes = TCPrecv_string(buffer_2);
			}
		}
	}
	
	parseHttpReply(buffer_2);
}
