//------------------------------------------------------------------------------
// SERVER: 	Server to receive data from the car
//
// COMPILE COMMAND: clear && gcc server.c udp.c -o server && ./server
//------------------------------------------------------------------------------

#include 	<arpa/inet.h>
#include 	<errno.h>
#include 	<inttypes.h>
#include 	<netinet/in.h>
#include	<pthread.h>
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#include 	<sys/select.h>
#include 	<sys/socket.h>
#include 	<time.h>
#include 	<unistd.h>
#include 	"udp_tcp.h"

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define		KEYBOARD		0
#define 	MY_UDP_PORT		8000
#define 	MY_TCP_PORT		8001
#define		IP_SIZE			16
#define		PORT_SIZE		4
#define		PORT_IP_SIZE	IP_SIZE + PORT_SIZE
#define		TRUE			1
#define		FALSE			0

//------------------------------------------------------------------------------
// GLOBAL STRUCTURES
//------------------------------------------------------------------------------

typedef struct tm* tm_t;

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------

int 	socket_UDP, socket_TCP, fdmax = 0, i, CAR_PORT, STARTED = TRUE, CONN_CREATED = FALSE, counter, ERROR;
char 	PORT_IP[PORT_IP_SIZE];
char 	buf[1024], filename[35], carIP[IP_SIZE], myIP[IP_SIZE], *IP = 0;
ssize_t recvBytes;
time_t 	rawtime;
tm_t	tm;
FILE*	fp;
fd_set 	master, read_fds;
sensor_data_g_t all_d;

//------------------------------------------------------------------------------
// MATLAB: Function simulating matlab operations
//------------------------------------------------------------------------------

void processData(void) {
	char path[1024];
	char cmd[1024];
	char *matlab_script = "sender";
	if (getcwd(path, sizeof(path)) == NULL) {
		printf("PROCESSING DATA FAILED: RETRIEVING CURRENT PATH FAILED\n");
		return;
	}
	
	sprintf(cmd,"osascript -e 'tell app \"Terminal\"\ndo script \"cd %s && cd ../sender_c &&./%s\"\nend tell' > /dev/null", path, matlab_script);

	system(cmd);
	
	printf("PROCESSING DATA STARTED IN THE NEW TERMINAL\n");
}

//------------------------------------------------------------------------------
// CLEAR BUFFER: Clear stdin
//------------------------------------------------------------------------------

void clearBuffer() {
	int c;
	while((c = getchar())!='\n' && c != '\0') {}
}

//------------------------------------------------------------------------------
// END: Check if user inserted "END" in the terminal
//------------------------------------------------------------------------------

int end() {
	fgets(buf,sizeof(buf),stdin);
	buf[(int)strlen(buf)-1]='\0';
	
	if(strcmp(buf,"END") == 0)
		return 1;
	return 0;
}

//------------------------------------------------------------------------------
// CREATE NEW FILE: Create new file to save data from car
//------------------------------------------------------------------------------

void createNewFile() {
	printf("\nNEW CONNECTION ESTABLISHED WITH CAR (PORT: %d) (IP: %s)\n", CAR_PORT, carIP);
	fflush(stdout);
	counter = 0;
	time(&rawtime);
	tm = localtime(&rawtime);
	sprintf(filename, "../log/log_%04d-%02d-%02d_%02d-%02d-%02d.csv", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
	if (fp != NULL)
		fclose(fp);
	fp = fopen(filename,"a");
}

//------------------------------------------------------------------------------
// RECV FROM CAR: Manages the communication with the car
//------------------------------------------------------------------------------

int recvFromCar() {
	recvBytes = UDPrecv_data(&all_d);
	
	if (recvBytes <= 0) {
		printf("ERROR IN UDP RECV\n");
		fflush(stdout);
		return -1;
	}
	
	switch(recvBytes) {
		case sizeof(sensor_data_g_t):
			if (counter++ == 0) {
				printf("START RECEIVING DATA ");
				fflush(stdout);
			}
			else if (counter++ % 100 == 0){
				printf(".");
				fflush(stdout);
			}
			fprintf(fp,"%" PRIu32 "\t %" PRIu32 "\t %f\t %f\t %f\t\n", all_d.m, all_d.seq_num, all_d.ax, all_d.ay, all_d.gz);
			break;
		default:
			printf("ERROR\n");
			fflush(stdout);
			break;
	}
	
	return 0;
}

//------------------------------------------------------------------------------
// INIT: Initialize connection with the car
//------------------------------------------------------------------------------

int initConnection() {
	recvBytes = UDPrecv(PORT_IP, PORT_IP_SIZE);
	char port_str[5];

	if (recvBytes <= 0) {
		printf("ERROR IN UDP RECV\n");
		fflush(stdout);
		return -1;
	}
	
	switch(recvBytes) {
		case sizeof(sensor_data_g_t):
			memcpy(port_str, PORT_IP, 4);
			port_str[4] = '\0';
			CAR_PORT = atoi(port_str);
			IP = PORT_IP+4;
			memcpy(carIP, IP, strlen(IP)+1);
			
			init_UDPsend(carIP, CAR_PORT);
			UDPsend(myIP);
			
			createNewFile();
			CONN_CREATED = TRUE;
			break;
		default:
			printf("ERROR\n");
			fflush(stdout);
			break;
	}
	
	return 0;
}

//------------------------------------------------------------------------------
// MAIN: Server body
//------------------------------------------------------------------------------

int main() {
	fp = fopen ("", "r");
	
	if ((socket_UDP = init_UDPrecv(MY_UDP_PORT)) < 0) {
		printf("ERROR IN UDP RECV INIT\n");
		fflush(stdout);
		if (fp != NULL)
			fclose(fp);
		return 0;
	}
	
	IP = getMyIP();
	memcpy(myIP, IP, strlen(IP)+1);
	printf("START SERVER (PORT: %d) (IP: %s)\n",MY_UDP_PORT, myIP);
	fflush(stdout);

	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	FD_SET(KEYBOARD, &master);
	fdmax = KEYBOARD;
	FD_SET(socket_UDP, &master);
	if (fdmax < socket_UDP)
		fdmax = socket_UDP;

	while(1) {
		read_fds = master;
		if(select(fdmax+1, &read_fds, NULL, NULL, NULL) < 0) {
			printf("ERROR IN UDP SELECT\n");
			fflush(stdout);
			if (fp != NULL)
				fclose(fp);
			return 0;
		}
		
		for(i = 0; i <= fdmax; i++){
			if(FD_ISSET(i, &read_fds)){
				if (i == KEYBOARD) {
					if (STARTED) {
						STARTED = FALSE;
						if (fp != NULL)
							fclose(fp);
						//processData();
						if (end())
							return 0;
						FD_CLR(socket_UDP, &master);
						fdmax = KEYBOARD;
					}
					else {
						STARTED = TRUE;
						clearBuffer();
						FD_SET(socket_UDP, &master);
						if (fdmax < socket_UDP)
							fdmax = socket_UDP;
						if (CONN_CREATED)
							createNewFile();
					}
				}
				else {
					if (STARTED == TRUE && CONN_CREATED == FALSE && initConnection() < 0) {
						if (fp != NULL)
							fclose(fp);
						return 0;
					}
					else if (STARTED == TRUE && CONN_CREATED == TRUE && recvFromCar() < 0) {
						if (fp != NULL)
							fclose(fp);
						return 0;
					}
				}
			}
		}
	}
}
