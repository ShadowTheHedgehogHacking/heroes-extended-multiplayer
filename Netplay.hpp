#pragma once

#include "includes/SFML/Network.hpp"



//
enum MID
{
	MID_Pos = 1, MID_OtherStuff
};
//



//
class Connection
{
public:
	Connection(bool isTCP = true, bool isBlocking = false);
	~Connection();


	sf::TcpSocket* socket;
	bool isConnected;
};


class Listener
{
public:
	sf::TcpListener* socket;
};


class ConnectionManager
{
public:
	bool listen(unsigned short port, const char* const& ip = "", bool isBlocking = false);
	bool accept();
	bool connect(const char* const& remoteAddress, unsigned short remotePort);
	bool send(const void* data, size_t size);
	bool receive(void* data, size_t size);

	ConnectionManager();
	~ConnectionManager();

	Connection* connection;

private:
	Listener* listener;
};
//



//
void DoIt();
//


