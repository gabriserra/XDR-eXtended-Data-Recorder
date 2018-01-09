//------------------------------------------------------------------------------
// ESP8266: Contains the library useful to manage the Wi-Fi module.
//------------------------------------------------------------------------------

#include <Arduino.h>
#include "ESP8266.h"

//------------------------------------------------------------------------------
// ESP8266: Constructors of the class
//------------------------------------------------------------------------------

ESP8266::ESP8266(SoftwareSerial &uart, uint32_t baud) : m_puart(&uart) {}

//------------------------------------------------------------------------------
// RX EMPTY: Empty the buffer or UART RX
//------------------------------------------------------------------------------

void ESP8266::rx_empty(void) {
	while (m_puart->available() > 0)
		m_puart->read();
}

//------------------------------------------------------------------------------
// RECV STRING: Recvive data from uart. Return all received data
//------------------------------------------------------------------------------

String ESP8266::recvString(String target, uint32_t timeout) {
	String data;
	char a;
	unsigned long start = millis();
	while (millis() - start < timeout) {
		while (m_puart->available() > 0) {
			a = m_puart->read();
			if (a == '\0') continue;
			data += a;
		}
		if (data.indexOf(target) != -1)
			break;
	}
	return data;
}

String ESP8266::recvString(String target1, String target2, uint32_t timeout) {
	String data;
	char a;
	unsigned long start = millis();
	while (millis() - start < timeout) {
		while (m_puart->available() > 0) {
				a = m_puart->read();
				if (a == '\0') continue;
				data += a;
		}
		if (data.indexOf(target1) != -1)
			break;
		else if (data.indexOf(target2) != -1)
			break;
	}
	return data;
}

String ESP8266::recvString(String target1, String target2, String target3, uint32_t timeout) {
	String data;
	char a;
	unsigned long start = millis();
	while (millis() - start < timeout) {
		while (m_puart->available() > 0) {
			a = m_puart->read();
			if (a == '\0') continue;
				data += a;
		}
		if (data.indexOf(target1) != -1)
				break;
		else {
			if (data.indexOf(target2) != -1)
				break;
			else if (data.indexOf(target3) != -1)
				break;
		}
	}
	return data;
}

//------------------------------------------------------------------------------
// RECV FIND: 	Recvive data from uart and search first target. Return
//				true if target found, false for timeout.
//------------------------------------------------------------------------------

bool ESP8266::recvFind(String target, uint32_t timeout) {
	String data_tmp;
	data_tmp = recvString(target, timeout);
	if (data_tmp.indexOf(target) != -1)
		return true;
	return false;
}

//------------------------------------------------------------------------------
// RECV FIND AND FILTER: 	Recvive data from uart and search first
//							target and cut out the substring between
//							begin and end(excluding begin and end self).
//							Return true if target found, false for
//							timeout
//------------------------------------------------------------------------------

bool ESP8266::recvFindAndFilter(String target, String begin, String end, String & data, uint32_t timeout) {
	String data_tmp;
	data_tmp = recvString(target, timeout);
	if (data_tmp.indexOf(target) != -1) {
		int32_t index1 = data_tmp.indexOf(begin);
		int32_t index2 = data_tmp.indexOf(end);
		if (index1 != -1 && index2 != -1) {
			index1 += begin.length();
			data = data_tmp.substring(index1, index2);
			return true;
		}
	}
	data = "";
	return false;
}

//------------------------------------------------------------------------------
// RECV PKG: Receive a package from uart
//------------------------------------------------------------------------------

uint32_t ESP8266::recvPkg(uint8_t *buffer, uint32_t buffer_size, uint32_t *data_len, uint32_t timeout, uint8_t *coming_mux_id) {
	String data;
	char a;
	int32_t index_PIPDcomma = -1;
	int32_t index_colon = -1;
	int32_t index_comma = -1;
	int32_t len = -1;
	int8_t id = -1;
	bool has_data = false;
	uint32_t ret;
	unsigned long start;
	uint32_t i;

	if (buffer == NULL)
		return 0;

	start = millis();

	while (millis() - start < timeout) {
		if (m_puart->available() > 0) {
			a = m_puart->read();
			data += a;
		}

		index_PIPDcomma = data.indexOf("+IPD,");
		if (index_PIPDcomma != -1) {
			index_colon = data.indexOf(':', index_PIPDcomma + 5);

			if (index_colon != -1) {
				index_comma = data.indexOf(',', index_PIPDcomma + 5);

				if (index_comma != -1 && index_comma < index_colon) {
					id = data.substring(index_PIPDcomma + 5, index_comma).toInt();
					if (id < 0 || id > 4)
						return 0;

					len = data.substring(index_comma + 1, index_colon).toInt();
					if (len <= 0)
						return 0;
				}
				else {
					len = data.substring(index_PIPDcomma + 5, index_colon).toInt();
					if (len <= 0)
						return 0;
				}

				has_data = true;
				break;
			}
		}
	}

	if (has_data) {
		i = 0;
		ret = len > buffer_size ? buffer_size : len;
		start = millis();

		while (millis() - start < 3000) {
			while (m_puart->available() > 0 && i < ret) {
				a = m_puart->read();
				buffer[i++] = a;
			}

			if (i == ret) {
				rx_empty();

				if (data_len)
					*data_len = len;

				if (index_comma != -1 && coming_mux_id)
					*coming_mux_id = id;

				return ret;
			}
		}
	}

	return 0;
}

//------------------------------------------------------------------------------
// AT COMMANDS
//------------------------------------------------------------------------------

bool ESP8266::AT(void) {
	rx_empty();
	m_puart->println(F("AT"));
	return recvFind("OK");
}

bool ESP8266::AT_RST(void) {
	rx_empty();
	m_puart->println(F("AT+RST"));
	return recvFind("OK");
}

bool ESP8266::AT_GMR(String & version) {
	rx_empty();
	m_puart->println(F("AT+GMR"));
	return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", version);
}

bool ESP8266::AT_CWMODE(uint8_t mode) {
	String data;
	rx_empty();
	m_puart->print(F("AT+CWMODE="));
	m_puart->println(mode);

	data = recvString("OK", "no change");
	if (data.indexOf("O") != -1 || data.indexOf("no change") != -1)
		return true;
	return false;
}

bool ESP8266::AT_CWMODE(uint8_t *mode) {
	String str_mode;
	bool ret;
	if (!mode)
		return false;

	rx_empty();
	m_puart->println(F("AT+CWMODE?"));
	ret = recvFindAndFilter("OK", "+CWMODE:", "\r\n\r\nOK", str_mode);

	if (ret) {
		*mode = (uint8_t)str_mode.toInt();
		return true;
	}
	else
		return false;
}

bool ESP8266::AT_CWJAP(String ssid, String pwd) {
	String data;
	rx_empty();
	m_puart->print(F("AT+CWJAP=\""));
	m_puart->print(ssid);
	m_puart->print(F("\",\""));
	m_puart->print(pwd);
	m_puart->println(F("\""));

	data = recvString("OK", 10000);
	if (data.indexOf("OK") != -1)
		return true;
	return false;
}

bool ESP8266::AT_CWLAP(String & list) {
	String data;
	rx_empty();
	m_puart->println(F("AT+CWLAP"));
	return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", list, 10000);
}

bool ESP8266::AT_CWQAP(void) {
	String data;
	rx_empty();
	m_puart->println(F("AT+CWQAP"));
	return recvFind("OK");
}

bool ESP8266::AT_CWSAP(String ssid, String pwd, uint8_t chl, uint8_t ecn) {
	String data;
	rx_empty();
	m_puart->print(F("AT+CWSAP=\""));
	m_puart->print(ssid);
	m_puart->print(F("\",\""));
	m_puart->print(pwd);
	m_puart->print(F("\","));
	m_puart->print(chl);
	m_puart->print(F(","));
	m_puart->println(ecn);

	data = recvString("OK", "ERROR", 5000);
	if (data.indexOf("OK") != -1)
		return true;
	return false;
}

bool ESP8266::AT_CWLIF(String & list) {
	String data;
	rx_empty();
	m_puart->println(F("AT+CWLIF"));
	return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", list);
}

bool ESP8266::AT_CIPSTATUS(String & list) {
	String data;
	delay(100);
	rx_empty();
	m_puart->println(F("AT+CIPSTATUS"));
	return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", list);
}

bool ESP8266::AT_CIPSTART_SINGLE(String type, String addr, uint32_t port) {
	String data;
	rx_empty();
	m_puart->print(F("AT+CIPSTART=\""));
	m_puart->print(type);
	m_puart->print(F("\",\""));
	m_puart->print(addr);
	m_puart->print(F("\","));
	m_puart->println(port);

	data = recvString("OK", "ERROR", "ALREADY CONNECT", 500);
	if (data.indexOf("OK") != -1 || data.indexOf("ALREADY CONNECT") != -1)
		return true;
	return false;
}

bool ESP8266::AT_CIPSTART_MULTIPLE(uint8_t mux_id, String type, String addr, uint32_t port) {
	String data;
	rx_empty();
	delay(50);
	m_puart->print(F("AT+CIPSTART="));
	m_puart->print(mux_id);
	m_puart->print(F(",\""));
	m_puart->print(type);
	m_puart->print(F("\",\""));
	m_puart->print(addr);
	m_puart->print(F("\","));
	m_puart->println(port);

	data = recvString("OK", "ERROR", "ALREADY CONNECT", 10000);
	if (data.indexOf("OK") != -1 || data.indexOf("ALREADY CONNECT") != -1)
		return true;
	return false;
}

bool ESP8266::AT_CIPSTART_MULTIPLE(uint8_t mux_id, String type, String addr, uint32_t port, uint32_t local_port, uint8_t mode) {
	String data;
	rx_empty();
	delay(50);
	m_puart->print(F("AT+CIPSTART="));
	m_puart->print(mux_id);
	m_puart->print(F(",\""));
	m_puart->print(type);
	m_puart->print(F("\",\""));
	m_puart->print(addr);
	m_puart->print(F("\","));
	m_puart->print(port);
	m_puart->print(F(","));
	m_puart->print(local_port);
	m_puart->print(F(","));
	m_puart->println(mode);

	data = recvString("OK", "ERROR", "ALREADY CONNECT", 10000);
	if (data.indexOf("OK") != -1 || data.indexOf("ALREADY CONNECT") != -1)
		return true;
	return false;
}

bool ESP8266::AT_CIPSEND_SINGLE(const uint8_t *buffer, uint32_t len) {
	rx_empty();
	m_puart->print(F("AT+CIPSEND="));
	m_puart->println(len);
	if (recvFind(">", 5000)) {
		rx_empty();
		for (uint32_t i = 0; i < len; i++)
			m_puart->write(buffer[i]);
		return recvFind("SEND OK", 10000);
	}
	return false;
}

bool ESP8266::AT_CIPSEND_MULTIPLE(uint8_t mux_id, const uint8_t *buffer, uint32_t len) {
	rx_empty();
	m_puart->print(F("AT+CIPSEND="));
	m_puart->print(mux_id);
	m_puart->print(F(","));
	m_puart->println(len);
	if (recvFind(">", 15)) {
		rx_empty();
		for (uint32_t i = 0; i < len; i++)
			m_puart->write(buffer[i]);
		return recvString("O","K","S", 50);
	}
	return false;
}

bool ESP8266::AT_CIPCLOSE_SINGLE(void) {
	rx_empty();
	m_puart->println(F("AT+CIPCLOSE"));
	return recvFind("OK", 5000);
}

bool ESP8266::AT_CIPCLOSE_MULTIPLE(uint8_t mux_id) {
	String data;
	rx_empty();
	m_puart->print(F("AT+CIPCLOSE="));
	m_puart->println(mux_id);

	data = recvString("OK", "link is not", 5000);
	if (data.indexOf("OK") != -1 || data.indexOf("link is not") != -1)
		return true;
	return false;
}

bool ESP8266::AT_CIFSR(String & list) {
	rx_empty();
	m_puart->println(F("AT+CIFSR"));
	return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", list);
}

bool ESP8266::AT_CIPMUX(uint8_t mode) {
	String data;

	rx_empty();
	delay(100);
	m_puart->print(F("AT+CIPMUX="));
	m_puart->println(mode);

	data = recvString("OK", "Link is builded");
	if (data.indexOf("OK") != -1) {
		delay(100);
		return true;
	}
	return false;
}

bool ESP8266::AT_CIPSERVER(uint8_t mode, uint32_t port) {
	String data;
	if (mode) {
		rx_empty();
		m_puart->print(F("AT+CIPSERVER=1,"));
		m_puart->println(port);

		data = recvString("OK", "no change");
		if (data.indexOf("OK") != -1 || data.indexOf("no change") != -1)
			return true;
		return false;
	}
	else {
		rx_empty();
		m_puart->println(F("AT+CIPSERVER=0"));
		return recvFind("\r\r\n");
	}
}

bool ESP8266::AT_CIPSTO(uint32_t timeout) {
	rx_empty();
	m_puart->print(F("AT+CIPSTO="));
	m_puart->println(timeout);
	return recvFind("OK");
}

//------------------------------------------------------------------------------
// INIT: 	Establish a successful connection with network in STATION
//			mode. This method will set the connection baud rate to be
//			9600
//------------------------------------------------------------------------------

bool ESP8266::init(const String &ssid, const String &pwd, uint32_t baudRateSet) {
	if (!autoSetBaud(baudRateSet)) {
		Serial.print(F("AUTO SET BAUDRATE: "));
		return false;
	}

	if (!setOprToStation()) {
		Serial.print(F("SET STATION OPTION: "));
		return false;
	}

	if (!joinAP(ssid, pwd)) {
		Serial.print(F("JOIN AP: "));
		return false;
	}

	if (!enableMUX()) {
		Serial.print(F("ENABLE MUX: "));
		return false;
	}

	return true;
}

//------------------------------------------------------------------------------
// AUTO SET BAUD: 	Detect ESP8266 baudrate and reset it to baudRateSet
//------------------------------------------------------------------------------

bool ESP8266::autoSetBaud(uint32_t baudRateSet) {
	rx_empty();
	long time0 = millis();
	long baudRateArray[] = {9600, 19200, 57600, 115200};
	const int attempts = 5;
	bool baudFlag = 0;

	for (int j = 0 ; j < attempts ; j++) {
		for (int i = 0; i < sizeof(baudRateArray) ; i++) {
			m_puart->begin(baudRateArray[i]);

			m_puart->println("AT");
			delay(20);
			while (m_puart->available()) {
				String inData = m_puart->readStringUntil('\n');
				if (inData.indexOf("OK") != -1) {
					baudFlag = 1;
					delay(15);
					break;
				}

			}
			if (baudFlag)
				break;
		}

		if (baudFlag) {
			baudFlag = 0;
			for (int j = 0; j < attempts; j++) {
				m_puart->print("AT+CIOBAUD=");
				m_puart->println(baudRateSet);
				delay(20);
				while (m_puart->available()) {
					String inData = m_puart->readStringUntil('\n');
					if (inData.indexOf("OK") != -1 || inData.indexOf("AT") != -1) {
						baudFlag = 1;
						m_puart->begin(baudRateSet);
						delay(100);
						return 1;
					}
				}
				if (baudFlag)
					break;
			}
		}
		if (baudFlag)
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------
// KICK: 	Verify ESP8266 whether live or not. Actually, this method
//			will send command "AT" to ESP8266 and waiting for "OK"
//------------------------------------------------------------------------------

bool ESP8266::kick(void) {
	return AT();
}

//------------------------------------------------------------------------------
// RESTART: 	Restart ESP8266 by "AT+RST". This method will take 3
//				seconds or more
//------------------------------------------------------------------------------

bool ESP8266::restart(void) {
	unsigned long start;
	if (AT_RST()) {
		delay(2000);
		start = millis();
		while (millis() - start < 3000) {
			if (AT()) {
				delay(1500);
				return true;
			}
			delay(100);
		}
	}
	return false;
}

//------------------------------------------------------------------------------
// GET VERSION: 	Get the version of AT Command Set
//------------------------------------------------------------------------------

String ESP8266::getVersion(void) {
	rx_empty();

	String inData;
	m_puart->println(F("AT+GMR"));
	delay(50);
	while (m_puart->available() > 0) {
		inData = m_puart->readString();
		delay(50);
		if (inData.indexOf("version") != -1)
			return inData.substring(6);
	}
	return inData;

	String version;
	AT_GMR(version);
	return version;
}

//------------------------------------------------------------------------------
// SET OPR TO STATION: 	Set operation mode to staion
//------------------------------------------------------------------------------

bool ESP8266::setOprToStation(void) {
	uint8_t mode;
	if (!AT_CWMODE(&mode))
		return false;

	if (mode == 1)
		return true;
	else {
		if (AT_CWMODE(1) && restart())
			return true;
		else
			return false;
	}
}

//------------------------------------------------------------------------------
// SET OPR TO SOFT AP: 	Set operation mode to softap
//------------------------------------------------------------------------------

bool ESP8266::setOprToSoftAP(void) {
	uint8_t mode;
	if (!AT_CWMODE(&mode))
		return false;

	if (mode == 2)
		return true;
	else {
		if (AT_CWMODE(2) && restart())
			return true;
		else
			return false;
	}
}

//------------------------------------------------------------------------------
// SET OPR TO STATION SOFT AP: 	Set operation mode to station + softap
//------------------------------------------------------------------------------

bool ESP8266::setOprToStationSoftAP(void) {
	uint8_t mode;
	if (!AT_CWMODE(&mode))
		return false;

	if (mode == 3)
		return true;
	else {
		if (AT_CWMODE(3) && restart())
			return true;
		else
			return false;
	}
}

//------------------------------------------------------------------------------
// GET AP LIST: 	Search available AP list and return it
//------------------------------------------------------------------------------

String ESP8266::getAPList(void) {
	String list;
	AT_CWLAP(list);
	return list;
}

//------------------------------------------------------------------------------
// JOIN AP: 	Join in AP
//------------------------------------------------------------------------------

bool ESP8266::joinAP(String ssid, String pwd) {
	return AT_CWJAP(ssid, pwd);
}

//------------------------------------------------------------------------------
// LEAVE AP: 	Leave AP joined before
//------------------------------------------------------------------------------

bool ESP8266::leaveAP(void) {
	return AT_CWQAP();
}

//------------------------------------------------------------------------------
// SOFT AP: 	Set SoftAP parameters
//------------------------------------------------------------------------------

bool ESP8266::setSoftAPParam(String ssid, String pwd, uint8_t chl, uint8_t ecn) {
	return AT_CWSAP(ssid, pwd, chl, ecn);
}

//------------------------------------------------------------------------------
// GET JOINED DEVICE IP: Get the IP list of devices connected to SoftAP
//------------------------------------------------------------------------------

String ESP8266::getJoinedDeviceIP(void) {
	String list;
	AT_CWLIF(list);
	return list;
}

//------------------------------------------------------------------------------
// GET IP STATUS: Get the current status of connection(UDP and TCP)
//------------------------------------------------------------------------------

String ESP8266::getIPStatus(void) {
	String list;
	AT_CIPSTATUS(list);
	return list;
}

//------------------------------------------------------------------------------
// GET LOCAL IP: Get the IP address of ESP8266
//------------------------------------------------------------------------------

String ESP8266::getLocalIP(void) {
	String inData;

	rx_empty();
	m_puart->println(F("AT+CIFSR"));
	delay(50);
	while (m_puart->available() > 0) {
		inData = m_puart->readStringUntil('\n');
		if (inData.indexOf("IP") != -1) {
			delay(100);
			return (inData.substring( inData.indexOf("IP") + 4, inData.length() - 2 ));
		}
	}
	return "Couldn't get IP adress";
}

//------------------------------------------------------------------------------
// ENABLE MUX: Enable IP MUX(multiple connection mode)
//------------------------------------------------------------------------------

bool ESP8266::enableMUX(void) {
	return AT_CIPMUX(1);
}

//------------------------------------------------------------------------------
// DISABLE MUX: 	Disable IP MUX(single connection mode). In single
//					connection mode, only one TCP or UDP communication
//					can be builded.
//------------------------------------------------------------------------------

bool ESP8266::disableMUX(void) {
	String inData;

	rx_empty();
	m_puart->println(F("AT+CIPMUX=0"));
	delay(50);
	while (m_puart->available() > 0) {
		inData = m_puart->readStringUntil('\n');
		if (inData.indexOf("OK") != -1) {
			delay(100);
			return true;
		}
	}
	return false;
}

//------------------------------------------------------------------------------
// CEATE TCP: 	Create TCP connection in single mode
//------------------------------------------------------------------------------

bool ESP8266::createTCP(String addr, uint32_t port) {
	return AT_CIPSTART_SINGLE("TCP", addr, port);
}

//------------------------------------------------------------------------------
// CEATE TCP: 	Create TCP connection in multiple mode
//------------------------------------------------------------------------------

bool ESP8266::createTCP(uint8_t mux_id, String addr, uint32_t port) {
	return AT_CIPSTART_MULTIPLE(mux_id, "TCP", addr, port);
}

//------------------------------------------------------------------------------
// RELEASE TCP: 	Create TCP connection in signle mode
//------------------------------------------------------------------------------

bool ESP8266::releaseTCP(void) {
	String inData;
	rx_empty();
	m_puart->println(F("AT+CIPCLOSE"));
	delay(50);
	while (m_puart->available() > 0) {
		inData = m_puart->readString();
		if (inData.indexOf("OK") != -1) {
			delay(100);
			return 1;
		}
	}
	return 0;
}

//------------------------------------------------------------------------------
// RELEASE TCP: 	Create TCP connection in multiple mode
//------------------------------------------------------------------------------

bool ESP8266::releaseTCP(uint8_t mux_id) {
	return AT_CIPCLOSE_MULTIPLE(mux_id);
}

//------------------------------------------------------------------------------
// REGISTER UDP: 	Register UDP port number in single mode
//------------------------------------------------------------------------------

bool ESP8266::registerUDP(String addr, uint32_t port) {
	return AT_CIPSTART_SINGLE("UDP", addr, port);
}

//------------------------------------------------------------------------------
// REGISTER UDP: 	Register UDP port number in multiple mode
//------------------------------------------------------------------------------

bool ESP8266::registerUDP(uint8_t mux_id, String addr, uint32_t port) {
	return AT_CIPSTART_MULTIPLE(mux_id, "UDP", addr, port);
}

//------------------------------------------------------------------------------
// REGISTER UDP:   Register UDP port number in multiple mode with local port
//------------------------------------------------------------------------------

bool ESP8266::registerUDP(uint8_t mux_id, String addr, uint32_t port, uint32_t local_port, uint8_t mode) {
	return AT_CIPSTART_MULTIPLE(mux_id, "UDP", addr, port, local_port, mode);
}

//------------------------------------------------------------------------------
// UNREGISTER UDP: 	Unregister UDP port number in single mode
//------------------------------------------------------------------------------

bool ESP8266::unregisterUDP(void) {
	return AT_CIPCLOSE_SINGLE();
}

//------------------------------------------------------------------------------
// UNREGISTER UDP: 	Unregister UDP port number in multiple mode
//------------------------------------------------------------------------------

bool ESP8266::unregisterUDP(uint8_t mux_id) {
	return AT_CIPCLOSE_MULTIPLE(mux_id);
}

//------------------------------------------------------------------------------
// SET TCP SERVER TIMEOUT: 	Set the timeout of TCP Server
//------------------------------------------------------------------------------

bool ESP8266::setTCPServerTimeout(uint32_t timeout) {
	return AT_CIPSTO(timeout);
}

//------------------------------------------------------------------------------
// START TCP SERVER: 	Start TCP Server (only in multiple mode). After
//						started, user should call method: getIPStatus to
//						know the status of TCP connections. The methods
//						of receiving data can be called for user's any
//						purpose. After communication, release the TCP
//						connection is needed by calling method:
//						releaseTCP with mux_id.
//------------------------------------------------------------------------------

bool ESP8266::startTCPServer(uint32_t port) {
	if (AT_CIPSERVER(1, port))
		return true;
	return false;
}

//------------------------------------------------------------------------------
// STOP TCP SERVER: 	Stop TCP Server (only in multiple mode)
//------------------------------------------------------------------------------

bool ESP8266::stopTCPServer(void) {
	AT_CIPSERVER(0);
	restart();
	return false;
}

//------------------------------------------------------------------------------
// START SERVER: 	Start Server (only in multiple mode)
//------------------------------------------------------------------------------

bool ESP8266::startServer(uint32_t port) {
	return startTCPServer(port);
}

//------------------------------------------------------------------------------
// STOP SERVER: 	Stop Server (only in multiple mode)
//------------------------------------------------------------------------------

bool ESP8266::stopServer(void) {
	return stopTCPServer();
}

//------------------------------------------------------------------------------
// SEND: 	Send data based on one of TCP or UDP builded already in
//			single mode
//------------------------------------------------------------------------------

bool ESP8266::send(const uint8_t *buffer, uint32_t len) {
	return AT_CIPSEND_SINGLE(buffer, len);
}

//------------------------------------------------------------------------------
// SEND: 	Send data based on one of TCP or UDP builded already in
//			multiple mode
//------------------------------------------------------------------------------

bool ESP8266::send(uint8_t mux_id, const uint8_t *buffer, uint32_t len) {
	return AT_CIPSEND_MULTIPLE(mux_id, buffer, len);
}

//------------------------------------------------------------------------------
// RECV: 	Receive data from TCP or UDP builded already in single mode
//------------------------------------------------------------------------------

uint32_t ESP8266::recv(uint8_t *buffer, uint32_t buffer_size, uint32_t timeout) {
	return recvPkg(buffer, buffer_size, NULL, timeout, NULL);
}

//------------------------------------------------------------------------------
// RECV: 	Receive data from one of TCP or UDP builded already in
//			multiple mode
//------------------------------------------------------------------------------

uint32_t ESP8266::recv(uint8_t mux_id, uint8_t *buffer, uint32_t buffer_size, uint32_t timeout) {
	uint8_t id;
	uint32_t ret;
	ret = recvPkg(buffer, buffer_size, NULL, timeout, &id);
	if (ret > 0)
		return ret;
	return 0;
}

//------------------------------------------------------------------------------
// RECV: 	Receive data from TCP or UDP builded already in multple mode
//			After return, coming_mux_id store the id of TCP or UDP
//			from which data coming
//------------------------------------------------------------------------------

uint32_t ESP8266::recv(uint8_t *coming_mux_id, uint8_t *buffer, uint32_t buffer_size, uint32_t timeout) {
	return recvPkg(buffer, buffer_size, NULL, timeout, coming_mux_id);
}
