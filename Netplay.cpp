#include "Netplay.hpp"
#include <HeroesLib/Player.hpp>



// Function Definitions //
void DoIt()
{
	bool running = true;
	bool error = false;
	bool isHost = false;
	char lastError = 0;
	short timeOutCount = 0;

	ConnectionManager* manager = new ConnectionManager;

	if (isHost)
	{
		if (!manager->listen(53000))
		{
			//error
			//break;
		}

		while (running)
		{
			

			if (!manager->accept())
			{
				//no new client, or an error accepting
				//continue;
			}


			sf::Packet pack;
			manager->connection->socket->receive(pack);
			sf::Uint8 header;

			//if (manager->receive(&header, 1) != sf::Socket::Done)
			{
				//continue;
				//error
			}

			pack >> header;

			switch (header)
			{
				case MID_Pos:
				{

					float posx;
					float posy;
					float posz;

					pack >> posx;
					pack >> posy;
					pack >> posz;
					//RwV3d pos;

					//if (manager->receive(&pos, 12) == sf::Socket::Done)
					{
						if (playerTOp[0])
						{
							//playerTOp[0]->position = pos;
							playerTOp[0]->position.x = posx;
							playerTOp[0]->position.y = posy;
							playerTOp[0]->position.z = posz;

						}
						//error
					}

				break;
				}
				
				case MID_OtherStuff:
				{
					//short motion;
					//short mode;
					//char rotation[12];
					//char speed[12];

					sf::Uint16 motion;
					sf::Uint16 mode;
					float angx;
					float angy;
					float angz;
					float spdx; 
					float spdy; 
					float spdz; 
					

					

					pack >> motion;

					pack >> mode;
					
					pack >> angx;
					pack >> angy;
					pack >> angz;
					pack >> spdx;
					pack >> spdy;
					pack >> spdz;



					//pack >> rotation;

					//pack >> speed;

					/*if (manager->receive((char*)&motion, 2) != sf::Socket::Done)
					{
						//error
						break;
					}

					if (manager->receive((char*)&mode, 2) != sf::Socket::Done)
					{
						//error
						break;
					}

					if (manager->receive((char*)&rotation, 12) != sf::Socket::Done)
					{
						//error
						break;
					}

					if (manager->receive((char*)&speed, 12) != sf::Socket::Done)
					{
						//error
						break;
					}*/

					if (playerTOp[0])
					{
						playerTOp[0]->animation = motion;
						playerTOp[0]->mode = mode;

						playerTOp[0]->rotation.x = angx;
						playerTOp[0]->rotation.y = angy;
						playerTOp[0]->rotation.z = angz;
						playerTOp[0]->spd.x = spdx;
						playerTOp[0]->spd.y = spdy;
						playerTOp[0]->spd.z = spdz;
					}
				break;
				}
			}
			//Sleep(10);
		}
	}

	else
	{
		while (!manager->connect("47.27.117.46", 53000))
		{
			Sleep(20);
			continue;
		}

		char frame = 0;
		while (running)
		{
			if (frame % 15)
			{
				if (playerTOp[0])
				{

					sf::Packet pack;

					sf::Uint8 header = MID_OtherStuff;
					sf::Uint16 motion = playerTOp[0]->animation;
					sf::Uint16 mode = playerTOp[0]->mode;
					float angx = playerTOp[0]->rotation.x;
					float angy = playerTOp[0]->rotation.y;
					float angz = playerTOp[0]->rotation.z;
					float spdx = playerTOp[0]->spd.x;
					float spdy = playerTOp[0]->spd.y;
					float spdz = playerTOp[0]->spd.z;

					pack << header;
					pack << motion;
					pack << mode;
					pack << angx;
					pack << angy;
					pack << angz;
					pack << spdx;
					pack << spdy;
					pack << spdz;

					manager->connection->socket->send(pack);
				}
			}

			if (frame % 5000)
			{
				if (playerTOp[0])
				{
					sf::Packet pack;

					sf::Uint8 header = MID_Pos;

					float posx = playerTOp[0]->position.x;
					float posy = playerTOp[0]->position.y;
					float posz = playerTOp[0]->position.z;

					pack << header;
					pack << posx;
					pack << posy;
					pack << posz;

					manager->connection->socket->send(pack);
				}
			}
			++frame;
			if (frame > 5000)
			{
				frame = 0;
			}
			//connected
			Sleep(5);
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
	isConnected = false;
}


Connection::~Connection()
{
	delete socket;
}
