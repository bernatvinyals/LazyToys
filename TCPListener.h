#pragma once

#include "TCPClient.h"

class TCPListener
{
	//Estroctura amb la IP i el Port
	void* Address;
	//Socket de conexio
	void* Socket;
public:
	// - Creaccio del socket
	// - Aassignacio del port a fer servir
	TCPListener(short _port);
	~TCPListener();
	
	//Escoltar al port asignat amb una reserva de X
	void Listen(int _backlog);
	
	//Acceptar el paquet i retorna un TCPClient
	// - Fer Recv del client per veure el request
	// - Fer Send del client per enviar resposta
	TCPClient* Accept();
	
	//Per tancar la conexio
	void Close();
};

