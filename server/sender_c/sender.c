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
Content-Length: 408\n\n\
content=";

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
	
	if (getcwd(path, sizeof(path)) == NULL) {
		printf("PROCESSING DATA FAILED: RETRIEVING CURRENT PATH FAILED\n");
		return;
	}
	
	char *matlab = "/Applications/MATLAB_R2016b.app/bin/matlab";
	//char *run_script = " -r \"../matlab_c/computeLossPackets.m\"";
	char *run_script = "\"; \"../matlab_c/prova\"";
	char *options = " -nodisplay -nosplash -noFigureWindows";
	//sprintf(sd, "%s%s%s", " -r \"cd ", path, "; run ../matlab_c/prova.m\"");
	//sprintf(sd, "%s%s%s", " -r \"cd ", path, "; cd ../matlab_c\"");
	//sprintf(sd, "%s%s%s", " -r \"cd ", path, "; cd ../matlab_c; run computeLossPackets(../log/log_2018-01-14_10-30-45.csv)\"");
	sprintf(sd, "%s%s%s%s%s", " -r \"cd('", path, "'); cd('../matlab_c'); computeLossPackets('",filename,"')\"");
	
	sprintf(cmd, "%s%s%s", matlab, options, sd);
	printf("%s\n",cmd);
	system(cmd);
}

//------------------------------------------------------------------------------
// CLEAR BUFFER: Clear stdin
//------------------------------------------------------------------------------

void clearBuffer() {
	int c;
	while((c = getchar())!='\n' && c != '\0') {}
}

//------------------------------------------------------------------------------
// CREATE EXAMPLE DATA
//------------------------------------------------------------------------------

json_object * createExampleData() {
	json_object *content = json_object_new_object();
	json_object *trip = json_object_new_object();
	json_object *stats = json_object_new_object();
	json_object *evaluation = json_object_new_object();
	json_object *crash = json_object_new_object();
	
	json_object *email = json_object_new_string("user@example.it");
	json_object_object_add(content,"email", email);
	
	json_object *meters = json_object_new_double(50);
	json_object_object_add(trip,"meters", meters);
	json_object *starttime = json_object_new_string("2018-01-07 07:30:00");
	json_object_object_add(trip,"starttime", starttime);
	json_object *secondslength = json_object_new_double(120);
	json_object_object_add(trip,"secondslength", secondslength);
	json_object_object_add(content,"trip", trip);
	
	json_object *numberacc = json_object_new_double(2);
	json_object_object_add(stats,"numberacc", numberacc);
	json_object *worstacc = json_object_new_double(5);
	json_object_object_add(stats,"worstacc", worstacc);
	json_object *numberbra = json_object_new_double(1);
	json_object_object_add(stats,"numberbra", numberbra);
	json_object *worstbra = json_object_new_double(3);
	json_object_object_add(stats,"worstbra", worstbra);
	json_object *numbercur = json_object_new_double(8);
	json_object_object_add(stats,"numbercur", numbercur);
	json_object_object_add(content,"stats", stats);
	
	json_object *pointstotal = json_object_new_double(2);
	json_object_object_add(evaluation,"pointstotal", pointstotal);
	json_object *pointsacceleration = json_object_new_double(5);
	json_object_object_add(evaluation,"pointsacceleration", pointsacceleration);
	json_object *pointsbraking = json_object_new_double(1);
	json_object_object_add(evaluation,"pointsbraking", pointsbraking);
	json_object *pointssteering = json_object_new_double(3);
	json_object_object_add(evaluation,"pointssteering", pointssteering);
	json_object *pointsspeed = json_object_new_double(8);
	json_object_object_add(evaluation,"pointsspeed", pointsspeed);
	json_object_object_add(content,"evaluation", evaluation);
	
	json_object *crashtime = json_object_new_string("2018-01-07 07:30:00");
	json_object_object_add(crash,"crashtime", crashtime);
	json_object *intensity = json_object_new_double(5);
	json_object_object_add(crash,"intensity", intensity);
	json_object *stationary = json_object_new_double(0);
	json_object_object_add(crash,"stationary", stationary);
	json_object_object_add(content,"crash", crash);
	
	return content;
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
	
	callMatlabScript("../log/log_2018-01-14_10-30-45.csv");
	
	//json_object * content = createExampleData();
	
	//printf ("The json object created: %s\n",json_object_to_json_string(content));
	//char buffer[1024];
	//sprintf(buffer, "%s%s%s", HEADER_HTTP, json_object_to_json_string(content), FOOTER_HTTP);
	//printf("%s\n",buffer);
	//TCPsend(buffer);

	/*
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
	 */
}
