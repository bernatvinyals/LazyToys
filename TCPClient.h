#pragma once

void Init_WinSock();

class TCPClient
{
public:
	//Estroctura amb la IP i el Port
	void* Address;
	//Socket de conexio
	void* Socket;
	
	// - Creaccio del socket
	// - Aassignacio del port a fer servir
	TCPClient(short _port);
	~TCPClient();
	
	//Conexio al Servidor fent us del port ja asignat i la ip demanada
	void Connect(char* _ip);
	
	//Per enviar el contingut del Buffer
	int Send(char* _buffer, int _size);
	
	//Per rebre les dades, guardarles en un buffer digentli el tamany d'aquest
	//Returns
	// <0  ERROR
	// 0   No he rebur re pero conexio continua
	// 1   He rebut dades
	int Recv(char* _buffer, int _size);
	
	//Per tancar la conexio
	void Close();
};

