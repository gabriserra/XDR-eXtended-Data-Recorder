#ifndef TCP_H
#define TCP_H

#include 	<stdint.h>

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define		BUFFER_SIZE		1024

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
// INIT UDP SEND: Creation of the UDP connection to send
//------------------------------------------------------------------------------

void init_UDPsend(char * ip, int port);

//------------------------------------------------------------------------------
// INIT UDP RECV: Creation of the UDP connection to receive
//------------------------------------------------------------------------------

int init_UDPrecv(int port);

//------------------------------------------------------------------------------
// UDP SEND: 	Send the server IP to the car
//------------------------------------------------------------------------------

ssize_t UDPsend(char * ip);

//------------------------------------------------------------------------------
// UDP RECV: 	Receive port and ip from the car
//------------------------------------------------------------------------------

ssize_t	UDPrecv(char * port_ip, int size);

//------------------------------------------------------------------------------
// UDP RECV DATA: 	Receive data from the car
//------------------------------------------------------------------------------

ssize_t	UDPrecv_data(sensor_data_g_t * all_d);

//------------------------------------------------------------------------------
// INIT TCP SERVER: Creation of the TCP connection as server
//------------------------------------------------------------------------------

int init_TCPserver(int port);

//------------------------------------------------------------------------------
// INIT TCP CLIENT: Creation of the TCP connection as client
//------------------------------------------------------------------------------

int init_TCPclient(char * ip, int port);

//------------------------------------------------------------------------------
// UDP SEND: 	Send a message to the car eventually
//------------------------------------------------------------------------------

ssize_t TCPsend(char * mes);

//------------------------------------------------------------------------------
// UDP RECV: 	Receive sensor's data from the car
//------------------------------------------------------------------------------

ssize_t	TCPrecv(sensor_data_g_t * all_d);

#endif
