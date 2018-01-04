#ifndef UDP_H
#define UDP_H

#include <stdint.h>

//------------------------------------------------------------------------------
// GLOBAL AND EXTERN STRUCTURES
//------------------------------------------------------------------------------

typedef struct sensor_data_g {
	uint32_t seq_num;
	float ax;
	float ay;
	//float az;
	//float v;
	//float gx;
	//float gy;
	float gz;
} sensor_data_g_t;

typedef struct sockaddr_in 	address;

typedef struct sockaddr		sockaddr;

typedef struct in_addr		addr;

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// GET MY IP: Return the IP of the server
//------------------------------------------------------------------------------

char*  	getMyIP();

//------------------------------------------------------------------------------
// UDP SEND INIT: Creation of the connection to send
//------------------------------------------------------------------------------

int UDPsend_init(char * ip, int port);

//------------------------------------------------------------------------------
// UDP RECV INIT: Creation of the connection to receive
//------------------------------------------------------------------------------

int UDPrecv_init(void);

//------------------------------------------------------------------------------
// UDP SEND: 	Send the server IP to the car
//------------------------------------------------------------------------------

void UDPsend(char * ip);

//------------------------------------------------------------------------------
// UDP RECV: 	Receive sensor's data from the car
//------------------------------------------------------------------------------

int	UDPrecv(sensor_data_g_t * all_d, address * addr);

#endif
