//------------------------------------------------------------------------------
// SERVER: 	Create server to receive data from the car
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// COMPILE COMMAND: clear && gcc server.c udp.c -o server && ./server
//------------------------------------------------------------------------------

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

#include "udp.h"

typedef struct tm* tm_t;

sensor_data_g_t all_d;

int 	main() {
int 	recvBytes;
char 	filename[34];
char* 	IP = 0;
time_t 	rawtime;
tm_t	tm;
FILE*	fp = fopen ("", "r");
address	carAddress;
	
		if (UDPrecv_init() < 0) {
			printf("ERROR IN UDP RECV INIT\n");
			if (fp != NULL)
				fclose(fp);
			return 0;
		}
	
		while(1) {
			recvBytes = UDPrecv(&all_d, &carAddress);
			
			if (recvBytes <= 0) {
				printf("ERROR IN UDP RECV\n");
				if (fp != NULL)
					fclose(fp);
				return 0;
			}
			
			if (recvBytes == 4) {
				printf("NEW CONNECTION\n");
				IP = inet_ntoa(carAddress.sin_addr);
				
				if (UDPsend_init(IP, all_d.seq_num) < 0) {
					printf("ERROR IN UDP SEND INIT\n");
					if (fp != NULL)
						fclose(fp);
					return 0;
				}
				
				IP = getMyIP();
				UDPsend(IP);
				
				time(&rawtime);
				tm = localtime(&rawtime);
				sprintf(filename, "./log/log_%04d-%02d-%02d_%02d-%02d-%02d.csv", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
				if (fp != NULL)
					fclose(fp);
				fp = fopen(filename,"a");
			}
			else{
				if (recvBytes == 32) {
					printf("DATA\n");
					fprintf(fp,"%d\t %f\t %f\t %f\t %f\t %f\t %f\t %f\n", all_d.seq_num, all_d.ax, all_d.ay, all_d.az, all_d.v, all_d.gx, all_d.gy, all_d.gz);
				}
				else
					printf("ERROR\n");
			}
		}
}
