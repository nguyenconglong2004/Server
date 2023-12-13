#pragma once
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib,"WS2_32")

class Socket {
public:
	Socket();
	~Socket();
	bool recieve();
	int init_and_connect();
	void break_up();
	int data[3] = { 0 };
private:
	WSADATA wsaData;
	sockaddr_in address;
	SOCKET listenSocket;
	SOCKET clientSocket;
	
};
