#include "Netplay.hpp"
#include <HeroesLib/Player.hpp>
#include <thread>



// Function Definitions //
void DoIt()
{
	bool running = true;
	bool error = false;
	char lastError = 0;
	short timeOutCount = 0;

	ConnectionManager* manager = new ConnectionManager;
	manager->isHost = false;

	if (MessageBoxA(NULL, "Host?", "Sonic Heroes Extended Multiplayer", MB_YESNO) == IDYES)
	{
		manager->isHost = true;
	}

	if (manager->isHost)
	{
		if (!manager->listen())
		{
			MessageBoxA(NULL, "y u no listen", "Sonig He-rose", MB_ICONERROR);
			//error
			//break;
		}

		while (running)
		{
			manager->accept();
			if (manager->connection)
			{
				manager->receive();
				manager->send();
			}
			Sleep(15);
		}
	}

	else
	{
		while (running)
		{
			//manager->connect("47.27.117.46", 53000);
			manager->connect("localhost", 53000);
			if (manager->connection)
			{
				manager->receive();
				manager->send();
			}
			Sleep(20);
		}
	}
	delete manager;
}


bool ConnectionManager::listen()
{
	return _listen(53000);
}


bool ConnectionManager::_listen(unsigned short port, const char* const& ip, bool isBlocking)
{
	if (!listener)
	{
		listener = new Listener;
		listener->socket = new sf::TcpListener;
		listener->socket->setBlocking(false);
	}
	
	if (listener->socket->listen(port) != sf::Socket::Done)
	{
		return false;
	}

	return true;
}

bool ConnectionManager::_send(sf::Packet& packet)
{
	if (connection->socket->send(packet) == sf::Socket::Partial)
	{
		MessageBoxA(NULL, "shit, it happens", "Sonig Heroes Extended Multiplayer", MB_ICONERROR);
		return sf::Socket::Partial;
	}
}


bool ConnectionManager::accept()
{
	if (!connection)
	{
		Connection* newConnection = new Connection(true);
		if (listener->socket->accept(*(newConnection->socket)) != sf::Socket::Done)
		{
			delete newConnection;
			return false;
		}

		connection = newConnection;
		return true;

	}
	return false;
}


bool ConnectionManager::connect(const char* const& remoteAddress, unsigned short remotePort)
{

	if (!connection)
	{
		Connection* newConnection = new Connection(true, true);

		if (newConnection->socket->connect(remoteAddress, remotePort) != sf::Socket::Done)
		{
			delete newConnection;
			return false;
		}
		connection = newConnection;
		return true;
	}
	return true;
}

	static int frame = 0;
bool ConnectionManager::send()
{
	//if (!(frame % 3))
	{
		if (playerTOp[3 * isHost])
		{
			if (playerTOp[3 * isHost]->mode != 0)
			{
				sf::Packet sendClientPacket;

				sf::Uint8 header = MID_OtherStuff;
				sf::Uint8 pno = playerTOp[3 * isHost]->characterNo;
				sf::Uint16 motion = playerTOp[pno]->animation;
				sf::Uint16 mode = playerTOp[pno]->mode;
				short angx = playerTOp[pno]->rotation.x;
				short angy = playerTOp[pno]->rotation.y;
				short angz = playerTOp[pno]->rotation.z;
				short spdx = playerTOp[pno]->spd.x;
				short spdy = playerTOp[pno]->spd.y;
				short spdz = playerTOp[pno]->spd.z;

				sendClientPacket << header;
				sendClientPacket << motion;
				sendClientPacket << mode;
				sendClientPacket << pno;
				sendClientPacket << angx;
				sendClientPacket << angy;
				sendClientPacket << angz;
				sendClientPacket << spdx;
				sendClientPacket << spdy;
				sendClientPacket << spdz;

				if (connection->socket->send(sendClientPacket) == sf::Socket::Partial)
				{
					MessageBoxA(NULL, "shit, it happens", "Sonig Heroes Extended Multiplayer", MB_ICONERROR);
				}
			}
		}
	}


		if (!(frame % 5))
		{
			if (playerTOp[3 * isHost])
			{
				sf::Packet sendClientPacket;

				sf::Uint8 header = MID_Pos;

				sf::Uint8 pno = playerTOp[3 * isHost]->characterNo;
				short posx = playerTOp[pno]->position.x;
				short posy = playerTOp[pno]->position.y;
				short posz = playerTOp[pno]->position.z;

				sendClientPacket << header;
				sendClientPacket << pno;
				sendClientPacket << posx;
				sendClientPacket << posy;
				sendClientPacket << posz;

				if (_send(sendClientPacket) == sf::Socket::Partial)
				{
					MessageBoxA(NULL, "shit, it happens", "Sonig Heroes Extended Multiplayer", MB_ICONERROR);
				}
			}
		}

	if (frame > 10)
	{
		frame = 0;
	}
	++frame;
	return true;
}


void ConnectionManager::receive()
{
	sf::Packet recieveclientpacket;
	_receive(recieveclientpacket);
	sf::Uint8 header;

	recieveclientpacket >> header;

	switch (header)
	{
		case MID_Pos:
		{
			sf::Uint8 pno;
			short posx;
			short posy;
			short posz;

			recieveclientpacket >> pno;
			recieveclientpacket >> posx;
			recieveclientpacket >> posy;
			recieveclientpacket >> posz;
			if (playerTOp[pno])
			{
				playerTOp[pno]->position.x = posx;
				playerTOp[pno]->position.y = posy;
				playerTOp[pno]->position.z = posz;
			}
			break;
		}

		case MID_OtherStuff:
		{
			sf::Uint16 motion;
			sf::Uint16 mode;
			sf::Uint8 pno;
			short angx;
			short angy;
			short angz;
			short spdx;
			short spdy;
			short spdz;




			recieveclientpacket >> motion;

			recieveclientpacket >> mode;
			recieveclientpacket >> pno;

			recieveclientpacket >> angx;
			recieveclientpacket >> angy;
			recieveclientpacket >> angz;
			recieveclientpacket >> spdx;
			recieveclientpacket >> spdy;
			recieveclientpacket >> spdz;


			if (playerTOp[pno])
			{
				playerTOp[pno]->animation = motion;
				playerTOp[pno]->mode = mode;

				playerTOp[pno]->rotation.x = angx;
				playerTOp[pno]->rotation.y = angy;
				playerTOp[pno]->rotation.z = angz;
				playerTOp[pno]->spd.x = spdx;
				playerTOp[pno]->spd.y = spdy;
				playerTOp[pno]->spd.z = spdz;
			}
			break;
		}
	}
}


bool ConnectionManager::_receive(sf::Packet& packet)
{
	return connection->socket->receive(packet);
}


ConnectionManager::~ConnectionManager()
{
	if (listener)
	{
		delete listener;
	}

	if (connection)
	{
		delete connection;
	}
}


ConnectionManager::ConnectionManager()
{
	listener = NULL;
	connection = NULL;
}


Connection::Connection(bool isTCP, bool isBlocking)
{
	socket = new sf::TcpSocket;
	socket->setBlocking(isBlocking);
	isConnected = false;
}


Connection::~Connection()
{
	delete socket;
}
