#ifndef UDP_H
#define UDP_H

#include <stdint.h>

//------------------------------------------------------------------------------
// GLOBAL STRUCTURES
//------------------------------------------------------------------------------

typedef struct sensor_data_g {
	uint32_t m;
	uint32_t seq_num;
	float ax;
	float ay;
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
// CREATE CAR ADDRESS: Initialization of the structure carAddress
//------------------------------------------------------------------------------

void createCarAddress(char * ip, int port);

//------------------------------------------------------------------------------
// UDP RECV INIT: Creation of the connection to receive
//------------------------------------------------------------------------------

int UDPrecv_init(int port);

//------------------------------------------------------------------------------
// UDP SEND: 	Send the server IP to the car
//------------------------------------------------------------------------------

ssize_t UDPsend(char * ip);

//------------------------------------------------------------------------------
// UDP RECV: 	Receive sensor's data from the car
//------------------------------------------------------------------------------

ssize_t	UDPrecv(sensor_data_g_t * all_d);

#endif
