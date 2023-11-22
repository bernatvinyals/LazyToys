#include "TCPListener.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment (lib,"Ws2_32.lib")

#include <stdlib.h>
TCPListener::TCPListener(short _port)
{
	Address = nullptr;
	Socket = nullptr;
	Init_WinSock();
	SOCKET lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (lSocket == INVALID_SOCKET)
	{
		printf("Socket Error: %d\n", WSAGetLastError());
		WSACleanup();
		return;
	}

	sockaddr_in* address = (sockaddr_in*)malloc(sizeof(sockaddr_in));
	if (address == NULL)
	{
		return;
	}
	address->sin_family = AF_INET;
	address->sin_port = htons(_port);
	address->sin_addr.s_addr = htonl(INADDR_ANY);
	int iResult = bind(lSocket, (SOCKADDR*)address, sizeof(sockaddr_in));
	if (iResult == SOCKET_ERROR)
	{
		printf("Error: %d\n", WSAGetLastError());
		closesocket(lSocket);
		WSACleanup();
		return;
	}
	Socket = (void*)lSocket;
	Address = (void*)address;
}

TCPListener::~TCPListener()
{
	WSACleanup();
}

void TCPListener::Listen(int _backlog)
{
	SOCKET psock = (SOCKET)Socket;
	int iResult = listen(psock, _backlog); 
	if (iResult == SOCKET_ERROR)
	{
		printf("Error: %d\n", WSAGetLastError());
		closesocket(psock);
		WSACleanup();
		return;
	}

}

TCPClient* TCPListener::Accept()
{
	SOCKET psock = (SOCKET)Socket;
	sockaddr* addr = (sockaddr*)malloc(sizeof(sockaddr));
	if (addr == NULL)
	{
		return nullptr;
	}
	int size_addr = sizeof(sockaddr);
	SOCKET ClientSocket = accept(psock, addr, &size_addr);
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("Error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 0;
	}
	TCPClient* client = (TCPClient*)malloc(sizeof(TCPClient));
	if (client == NULL)
	{
		return nullptr;
	}
	client->Address = (void *)addr;
	client->Socket = (void*)ClientSocket;
	return client;
}

void TCPListener::Close()
{
	SOCKET psock = (SOCKET)Socket;
	closesocket(psock);
	Socket = 0;
	free(Address);

}
