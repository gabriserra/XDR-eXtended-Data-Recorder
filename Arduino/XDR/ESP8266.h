#ifndef __ESP8266_H__
#define __ESP8266_H__

#include "SoftwareSerial.h"

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define MAX_BUFFER_SIZE 	300
#define DEF_BAUDRATE     	9600
#define	DEF_TIMEOUT			1000

//------------------------------------------------------------------------------
// CLASS DEFINITION
//------------------------------------------------------------------------------

class ESP8266 {
	//--------------------------------------------------------------------------
	// PRIVATE MEMBERS AND FUNCTIONS
	//--------------------------------------------------------------------------
	private:
		//----------------------------------------------------------------------
		// PRIVATE MEMBERS
		//----------------------------------------------------------------------
	
		SoftwareSerial * m_puart;
		uint8_t m_responseBuffer[MAX_BUFFER_SIZE] = {0};
	
		//----------------------------------------------------------------------
		// PRIVATE FUNCTIONS
		//----------------------------------------------------------------------
	
		//----------------------------------------------------------------------
		// RX EMPTY: Empty the buffer or UART RX
		//----------------------------------------------------------------------
	
		void rx_empty(void);
	
		//----------------------------------------------------------------------
		// RECV STRING: 	Recvive data from uart. Return all received data
		//----------------------------------------------------------------------

    bool   recvString(uint32_t timeout);
		String recvString(String target, uint32_t timeout = DEF_TIMEOUT);
		String recvString(String target1, String target2, uint32_t timeout = DEF_TIMEOUT);
		String recvString(String target, String target2, String target3, uint32_t timeout = DEF_TIMEOUT);
    String recvString(String target1, String target2, String target3, String target4, String target5, String target6, uint32_t timeout);
	
		//----------------------------------------------------------------------
		// RECV FIND: 	Recvive data from uart and search first target. Return
		//				true if target found, false for timeout.
		//----------------------------------------------------------------------
	
		bool recvFind(String target, uint32_t timeout = DEF_TIMEOUT);
	
		//----------------------------------------------------------------------
		// RECV FIND AND FILTER: 	Recvive data from uart and search first
		//							target and cut out the substring between
		//							begin and end(excluding begin and end self).
		//							Return true if target found, false for
		//							timeout
		//----------------------------------------------------------------------

		bool recvFindAndFilter(String target, String begin, String end, String &data, uint32_t timeout = DEF_TIMEOUT);
	
		//----------------------------------------------------------------------
		// RECV PKG: 	Receive a package from uart
		//----------------------------------------------------------------------
	
		uint32_t recvPkg(uint8_t *buffer, uint32_t buffer_size, uint32_t *data_len, uint32_t timeout, uint8_t *coming_mux_id);
	
		//----------------------------------------------------------------------
		// AT COMMANDS
		//----------------------------------------------------------------------
	
		bool AT(void);
		bool AT_RST(void);
		bool AT_GMR(String &version);
		bool AT_CWMODE(uint8_t mode);
		bool AT_CWMODE(uint8_t *mode);
		bool AT_CWJAP(String ssid, String pwd);
		bool AT_CWLAP(String &list);
		bool AT_CWQAP(void);
		bool AT_CWSAP(String ssid, String pwd, uint8_t chl, uint8_t ecn);
		bool AT_CWLIF(String &list);
	
		bool AT_CIPSTATUS(String &list);
		bool AT_CIPSTART_SINGLE(String type, String addr, uint32_t port);
    bool AT_CIPSTART_SINGLE(String type, String addr, uint32_t port, uint32_t local_port, uint8_t mode);
		bool AT_CIPSTART_MULTIPLE(uint8_t mux_id, String type, String addr, uint32_t port);
    bool AT_CIPSTART_MULTIPLE(uint8_t mux_id, String type, String addr, uint32_t port, uint32_t local_port, uint8_t mode);
		bool AT_CIPSEND_SINGLE( const uint8_t *buffer, uint32_t len);
		bool AT_CIPSEND_MULTIPLE(uint8_t mux_id, const uint8_t *buffer, uint32_t len);
		bool AT_CIPCLOSE_SINGLE(void);
		bool AT_CIPCLOSE_MULTIPLE(uint8_t mux_id);
		bool AT_CIFSR(String &list);
		bool AT_CIPMUX(uint8_t mode);
		bool AT_CIPSERVER(uint8_t mode, uint32_t port = 333);
		bool AT_CIPSTO(uint32_t timeout);
	
	//--------------------------------------------------------------------------
	// PUBLIC MEMBERS AND FUNCTIONS
	//--------------------------------------------------------------------------
	
	public:
	
		//----------------------------------------------------------------------
		// PUBLIC FUNCTIONS
		//----------------------------------------------------------------------
	
		//----------------------------------------------------------------------
		// ESP8266: Constructor of the class
		//----------------------------------------------------------------------

		ESP8266(SoftwareSerial &uart, uint32_t baud = DEF_BAUDRATE);
	
		//------------------------------------------------------------------------------
    // INIT UDP:   Establish a successful UDP connection with network in STATION
    //            mode. 
    //------------------------------------------------------------------------------
    
    bool init_UDP(const String &ssid, const String &pwd);
    
    //------------------------------------------------------------------------------
    // INIT TCP:  Establish a successful TCP connection with network in STATION
    //            mode. 
    //------------------------------------------------------------------------------
    
    bool init_TCP(uint8_t recv_mux_id, uint8_t send_mux_id);
	
		//----------------------------------------------------------------------
		// AUTO SET BAUD: 	Detect ESP8266 baudrate and reset it to baudRateSet
		//----------------------------------------------------------------------
	
		bool autoSetBaud(uint32_t baudRateSet = DEF_BAUDRATE);
	
		//----------------------------------------------------------------------
		// KICK: 	Verify ESP8266 whether live or not. Actually, this method
		//			will send command "AT" to ESP8266 and waiting for "OK"
		//----------------------------------------------------------------------
	
		bool kick(void);

		//----------------------------------------------------------------------
		// RESTART: 	Restart ESP8266 by "AT+RST". This method will take 3
		//				seconds or more
		//----------------------------------------------------------------------
	
		bool restart(void);
	
		//----------------------------------------------------------------------
		// GET VERSION: 	Get the version of AT Command Set
		//----------------------------------------------------------------------

		String getVersion(void);
	
		//----------------------------------------------------------------------
		// SET OPR TO STATION: 	Set operation mode to staion
		//----------------------------------------------------------------------
	
		bool setOprToStation(void);
	
		//----------------------------------------------------------------------
		// SET OPR TO SOFT AP: 	Set operation mode to softap
		//----------------------------------------------------------------------
	
		bool setOprToSoftAP(void);
	
		//----------------------------------------------------------------------
		// SET OPR TO STATION SOFT AP: 	Set operation mode to station + softap
		//----------------------------------------------------------------------
	
		bool setOprToStationSoftAP(void);
	
		//----------------------------------------------------------------------
		// GET AP LIST: 	Search available AP list and return it
		//----------------------------------------------------------------------
	
		String getAPList(void);
	
		//----------------------------------------------------------------------
		// JOIN AP: 	Join in AP
		//----------------------------------------------------------------------
	
		bool joinAP(String ssid, String pwd);
	
		//----------------------------------------------------------------------
		// LEAVE AP: 	Leave AP joined before
		//----------------------------------------------------------------------
	
		bool leaveAP(void);
	
		//----------------------------------------------------------------------
		// SOFT AP: 	Set SoftAP parameters
		//----------------------------------------------------------------------
	
		bool setSoftAPParam(String ssid, String pwd, uint8_t chl = 7, uint8_t ecn = 4);
	
		//----------------------------------------------------------------------
		// GET JOINED DEVICE IP: Get the IP list of devices connected to SoftAP
		//----------------------------------------------------------------------
	
		String getJoinedDeviceIP(void);
	
		//----------------------------------------------------------------------
		// GET IP STATUS: Get the current status of connection(UDP and TCP)
		//----------------------------------------------------------------------
	
		String getIPStatus(void);
	
		//----------------------------------------------------------------------
		// GET LOCAL IP: Get the IP address of ESP8266
		//----------------------------------------------------------------------
	
		String getLocalIP(void);
	
		//----------------------------------------------------------------------
		// ENABLE MUX: Enable IP MUX (multiple connection mode)
		//----------------------------------------------------------------------
	
		bool enableMUX(void);
	
		//----------------------------------------------------------------------
		// DISABLE MUX: 	Disable IP MUX(single connection mode). In single
		//					connection mode, only one TCP or UDP communication
		//					can be builded.
		//----------------------------------------------------------------------
	
		bool disableMUX(void);
	
		//----------------------------------------------------------------------
		// CEATE TCP: 	Create TCP connection in single mode
		//----------------------------------------------------------------------
	
		bool createTCP(String addr, uint32_t port);
	
		//----------------------------------------------------------------------
		// CREATE TCP: 	Create TCP connection in multiple mode
		//----------------------------------------------------------------------
	
		bool createTCP(uint8_t mux_id, String addr, uint32_t port);
	
		//----------------------------------------------------------------------
		// RELEASE TCP: 	Create TCP connection in single mode
		//----------------------------------------------------------------------
	
		bool releaseTCP(void);
	
		//----------------------------------------------------------------------
		// RELEASE TCP: 	Create TCP connection in multiple mode
		//----------------------------------------------------------------------
	
		bool releaseTCP(uint8_t mux_id);
	
		//----------------------------------------------------------------------
		// REGISTER UDP: 	Register UDP port number in single mode
		//----------------------------------------------------------------------
	
		bool registerUDP(String addr, uint32_t port);
	
		//----------------------------------------------------------------------
		// REGISTER UDP: 	Register UDP port number in multiple mode
		//----------------------------------------------------------------------
	
		bool registerUDP(uint8_t mux_id, String addr, uint32_t port);

   //----------------------------------------------------------------------
   // REGISTER UDP:    Register UDP port number in single mode with local
    //          port
    //----------------------------------------------------------------------

    bool registerUDP(String addr, uint32_t port, uint32_t local_port, uint8_t mode);

		//----------------------------------------------------------------------
		// REGISTER UDP:  	Register UDP port number in multiple mode with local
		//					port
		//----------------------------------------------------------------------

		bool registerUDP(uint8_t mux_id, String addr, uint32_t port, uint32_t local_port, uint8_t mode);
	
		//----------------------------------------------------------------------
		// UNREGISTER UDP: 	Unregister UDP port number in single mode
		//----------------------------------------------------------------------
	
		bool unregisterUDP(void);
	
		//----------------------------------------------------------------------
		// UNREGISTER UDP: 	Unregister UDP port number in multiple mode
		//----------------------------------------------------------------------
	
		bool unregisterUDP(uint8_t mux_id);
	
		//----------------------------------------------------------------------
		// SET TCP SERVER TIMEOUT: 	Set the timeout of TCP Server
		//----------------------------------------------------------------------
	
		bool setTCPServerTimeout(uint32_t timeout = 180);
	
		//----------------------------------------------------------------------
		// START TCP SERVER: 	Start TCP Server (only in multiple mode). After
		//						started, user should call method: getIPStatus to
		//						know the status of TCP connections. The methods
		//						of receiving data can be called for user's any
		//						purpose. After communication, release the TCP
		//						connection is needed by calling method:
		//						releaseTCP with mux_id.
		//----------------------------------------------------------------------
	
		bool startTCPServer(uint32_t port = 333);
	
		//----------------------------------------------------------------------
		// STOP TCP SERVER: 	Stop TCP Server (only in multiple mode)
		//----------------------------------------------------------------------
	
		bool stopTCPServer(void);
	
		//----------------------------------------------------------------------
		// START SERVER: 	Start Server (only in multiple mode)
		//----------------------------------------------------------------------
	
		bool startServer(uint32_t port = 333);
	
		//----------------------------------------------------------------------
		// STOP SERVER: 	Stop Server (only in multiple mode)
		//----------------------------------------------------------------------
	
		bool stopServer(void);
	
		//----------------------------------------------------------------------
		// SEND: 	Send data based on one of TCP or UDP builded already in
		//			single mode
		//----------------------------------------------------------------------
	
		bool send(const uint8_t *buffer, uint32_t len);
	
		//----------------------------------------------------------------------
		// SEND: 	Send data based on one of TCP or UDP builded already in
		//			multiple mode
		//----------------------------------------------------------------------
	
		bool send(uint8_t mux_id, const uint8_t *buffer, uint32_t len);
	
		//----------------------------------------------------------------------
		// RECV: 	Receive data from TCP or UDP builded already in single mode
		//----------------------------------------------------------------------
	
		uint32_t recv(uint8_t *buffer, uint32_t buffer_size, uint32_t timeout = DEF_TIMEOUT);
	
		//----------------------------------------------------------------------
		// RECV: 	Receive data from one of TCP or UDP builded already in
		//			multiple mode
		//----------------------------------------------------------------------
	
		uint32_t recv(uint8_t mux_id, uint8_t *buffer, uint32_t buffer_size, uint32_t timeout = DEF_TIMEOUT);
	
		//----------------------------------------------------------------------
		// RECV: 	Receive data from TCP or UDP builded already in multple mode
		//			After return, coming_mux_id store the id of TCP or UDP
		//			from which data coming
		//----------------------------------------------------------------------
	
		uint32_t recv(uint8_t *coming_mux_id, uint8_t *buffer, uint32_t buffer_size, uint32_t timeout = DEF_TIMEOUT);
};

#endif
