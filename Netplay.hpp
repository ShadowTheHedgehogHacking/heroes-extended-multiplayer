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
	bool listen();
	bool accept();
	bool connect(const char* const& remoteAddress, unsigned short remotePort);
	bool send();
	void receive();

	ConnectionManager();
	~ConnectionManager();

	bool isHost;
	Connection* connection;

private:
	Listener* listener;

	bool _listen(unsigned short port, const char* const& ip = "", bool isBlocking = false);
	bool _send(sf::Packet& packet);
	bool _receive(sf::Packet& packet);
};
//



//
void DoIt();
//



