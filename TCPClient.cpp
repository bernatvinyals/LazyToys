#include "TCPClient.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment (lib,"Ws2_32.lib")
TCPClient::TCPClient(short _port)
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
	Socket = (void*)lSocket;
	Address = (void*)address;
}

TCPClient::~TCPClient()
{
}

void TCPClient::Connect(char* _ip)
{
	SOCKET psock = (SOCKET)Socket;
	sockaddr_in* pAddress = (sockaddr_in*)Address;
	inet_pton(AF_INET, _ip, &pAddress->sin_addr);

	int iResult = connect(psock, (SOCKADDR*)pAddress, sizeof(sockaddr_in));
	if (iResult == SOCKET_ERROR)
	{
		printf("Error: %d\n", WSAGetLastError());
		closesocket(psock);
		WSACleanup();
		return;
	}
}

int TCPClient::Recv(char* _buffer, int _size)
{
	SOCKET psock = (SOCKET)Socket;
	return recv(psock, _buffer, _size, NULL);
}

int TCPClient::Send(char* _buffer, int _size)
{
	SOCKET psock = (SOCKET)Socket;
	return send(psock, _buffer, _size, NULL);
}

void TCPClient::Close()
{
	SOCKET psock = (SOCKET)Socket;
	closesocket(psock);
	Socket = 0;
	free(Address);
}
bool bWinSock = false;
void Init_WinSock()
{
	if (!bWinSock)
	{
		WSADATA wsa;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsa);
		if (iResult != 0)
		{
			printf("WSADATA Error: %d\n", WSAGetLastError());
			WSACleanup();
			return;
		}
		else
		{
			bWinSock = true;
		}
	}
}
