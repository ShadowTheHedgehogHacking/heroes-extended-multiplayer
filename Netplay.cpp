#include "Netplay.hpp"
#include <HeroesLib/Player.hpp>
#include <thread>



// Function Definitions //
void SendLoop(ConnectionManager* manager, bool isHost)
{
	bool running = true;
	char frame = 0;
	while (running)
	{
		{
			if (playerTOp[3 * isHost])
			{
				sf::Packet sendClientPacket;

				sf::Uint8 header = MID_OtherStuff;
				sf::Uint8 pno = playerTOp[3 * isHost]->characterNo;
				sf::Uint16 motion = playerTOp[pno]->animation;
				sf::Uint16 mode = playerTOp[pno]->mode;
				float angx = playerTOp[pno]->rotation.x;
				float angy = playerTOp[pno]->rotation.y;
				float angz = playerTOp[pno]->rotation.z;
				float spdx = playerTOp[pno]->spd.x;
				float spdy = playerTOp[pno]->spd.y;
				float spdz = playerTOp[pno]->spd.z;

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

				manager->connection->socket->send(sendClientPacket);
			}
		}

		if (frame % 5000)
		{
			if (playerTOp[3 * isHost])
			{
				sf::Packet sendClientPacket;

				sf::Uint8 header = MID_Pos;

				sf::Uint8 pno = playerTOp[3 * isHost]->characterNo;
				float posx = playerTOp[pno]->position.x;
				float posy = playerTOp[pno]->position.y;
				float posz = playerTOp[pno]->position.z;

				sendClientPacket << header;
				sendClientPacket << pno;
				sendClientPacket << posx;
				sendClientPacket << posy;
				sendClientPacket << posz;

				manager->connection->socket->send(sendClientPacket);
			}
		}
		++frame;
		if (frame > 5000)
		{
			frame = 0;	
		}
		Sleep(200);
	}
}


void DoIt()
{
	bool running = true;
	bool error = false;
	bool isHost = false;
	char lastError = 0;
	short timeOutCount = 0;

	ConnectionManager* manager = new ConnectionManager;

	if (MessageBoxA(NULL, "Host?", "Sonic Heroes Extended Multiplayer", MB_YESNO) == IDYES)
	{
		isHost = true;
	}

	if (isHost)
	{
		if (!manager->listen(53000))
		{
			//error
			//break;
		}

		if (!manager->accept())
		{
			//no new client, or an error accepting
			//continue;
		}
		std::thread sendThread(SendLoop, manager, 1);
		sendThread.detach();
		while (running)
		{
			sf::Packet recieveclientpacket;
			manager->connection->socket->receive(recieveclientpacket);
			sf::Uint8 header;

			recieveclientpacket >> header;

			switch (header)
			{
				case MID_Pos:
				{
					sf::Uint8 pno;
					float posx;
					float posy;
					float posz;

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
					float angx;
					float angy;
					float angz;
					float spdx;
					float spdy;
					float spdz;




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
			Sleep(500);
		}
	}

	else
	{
		while (!manager->connect("47.27.117.46", 53000))
		{
			Sleep(20);
			continue;
		}
		
		std::thread sendThread(SendLoop, manager, 0);
		sendThread.detach();
		while (running)
		{
			sf::Packet recieveclientpacket;
			manager->connection->socket->receive(recieveclientpacket);
			sf::Uint8 header;

			recieveclientpacket >> header;

			switch (header)
			{
				case MID_Pos:
				{
					sf::Uint8 pno;
					float posx;
					float posy;
					float posz;

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
					float angx;
					float angy;
					float angz;
					float spdx;
					float spdy;
					float spdz;


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
			Sleep(50);
		}
	}
	delete manager;
}


bool ConnectionManager::listen(unsigned short port, const char* const& ip, bool isBlocking)
{
	if (!listener)
	{
		listener = new Listener;
		listener->socket = new sf::TcpListener;
	}
	
	if (listener->socket->listen(port) != sf::Socket::Done)
	{
		return false;
	}

	return true;
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
		Connection* newConnection = new Connection(true);

		if (newConnection->socket->connect(remoteAddress, remotePort) != sf::Socket::Done)
		{
			delete newConnection;
			return false;
		}
		connection = newConnection;
		return true;
	}
	return false;
}


bool ConnectionManager::send(const void* data, size_t size)
{
	return connection->socket->send(data, size);
}


bool ConnectionManager::receive(void* data, size_t size)
{
	size_t temp;
	return connection->socket->receive(data, size, temp);
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
	//socket->setBlocking(false);
	isConnected = false;
}


Connection::~Connection()
{
	delete socket;
}
