#include "Netplay.hpp"
#include <HeroesLib/Player.hpp>
#include <thread>
#include <iostream>



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
			Sleep(5);
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
				if (manager->connection->udpSocket)
				{
					//std::cout << "connection udpSocket is set" << '\n';
					//manager->receiveUDP();
				}
				manager->send();
				manager->receive();
			}
			Sleep(5);
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

		std::cout << "accepted" << '\n';
		connection = newConnection;
		connection->udpSocket = new sf::UdpSocket;
		connection->ipAddress = _strdup(connection->socket->getRemoteAddress().toString().c_str());
		connection->port = 53000;
		connection->udpPort = connection->udpSocket->getLocalPort();
		connection->udpSocket->bind(53001);

		sf::Packet punchRet;

		punchRet << MID_UDPSuccess;
		connection->udpSocket->send(punchRet, connection->ipAddress, connection->udpPort);
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
		connection->port = 53000;
		connection->udpSocket = new sf::UdpSocket;
		connection->ipAddress = _strdup(connection->socket->getRemoteAddress().toString().c_str());
		connection->udpSocket->bind(53001);
		//connection->udpSocket->bind(sf::Socket::AnyPort);
		connection->udpPort = connection->udpSocket->getLocalPort();

		sf::Packet punchRet;

		punchRet << MID_UDPSuccess;
		std::cout << "successfully connected to IP: " << remoteAddress << ":" << remotePort << '\n';
		std::cout << "tried to send UDP packet to IP: " << connection->ipAddress << ":" << connection->udpPort << '\n';
		connection->udpSocket->send(punchRet, connection->ipAddress, connection->udpPort);
		std::cout << "finished sending UDP packet to IP: " << connection->ipAddress << ":" << connection->udpPort << '\n';
		return true;
	}
	return true;
}

	static int frame = 0;
bool ConnectionManager::send()
{
	// std::cout << "send() called" << '\n';

	//if (!(frame % 3))
	{
		if (playerTOp[3 * isHost])
		{
			if (playerTOp[3 * isHost]->mode != 0)
			{
				std::cout << "firstFrame constructed packet" << '\n';
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

				// TODO check why socket->send instead of _send() like line 234
				if (connection->socket->send(sendClientPacket) == sf::Socket::Partial)
				{
					std::cout << "partial packet sent" << '\n';
					MessageBoxA(NULL, "shit, it happens", "Sonig Heroes Extended Multiplayer", MB_ICONERROR);
				}
			}
		}
	}


		if (!(frame % 5))
		{
			std::cout << "frame % 5 code" << '\n';

			if (playerTOp[3 * isHost])
			{
				std::cout << "inner if" << '\n';
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

				std::cout << "preparing to send packet @ frame % 5" << '\n';
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
	// std::cout << "receive() called" << '\n';

	switch (header)
	{
		case MID_Pos:
		{
			std::cout << "and it was POS" << '\n';
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
			std::cout << "and it was OtherStuff" << '\n';
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

		case MID_InitUDP:
		{
			std::cout << "and it was UDP!!!" << '\n';
			connection->udpSocket = new sf::UdpSocket;
			connection->ipAddress = _strdup(connection->socket->getRemoteAddress().toString().c_str());
			connection->udpSocket->bind(sf::Socket::AnyPort);
			connection->udpPort = connection->udpSocket->getLocalPort();

			sf::Packet punchRet;

			punchRet << MID_UDPSuccess;
			connection->udpSocket->send(punchRet, connection->ipAddress, connection->udpPort);
			break;
		}

		default:
		{
			//std::cout << "and it was: " << header << std::endl;
		}
	}
}


void ConnectionManager::receiveUDP()
{
	sf::Packet udpRecv;
	sf::IpAddress test = connection->ipAddress;
	connection->udpSocket->receive(udpRecv, test, connection->udpPort);
	sf::Uint8 testHeader;
	udpRecv >> testHeader;

	switch (testHeader)
	{
		case MID_UDPSuccess:
		{
			MessageBoxA(NULL, "nice job hacker!", "Sonik He-Rose Multilayer", MB_OK);
		}
	}
}


bool ConnectionManager::_receive(sf::Packet& packet)
{
	// std::cout << "Waiting for an actual receive from: " << connection->ipAddress << ":" <<  connection->port << '\n';
	sf::Socket::Status statusCode = connection->socket->receive(packet);
	// std::cout << "Received! Status: " << statusCode << '\n';
	switch (statusCode)
	{
	case sf::Socket::Status::NotReady:
		std::cout << "_receieve: The socket is not ready to send / receive data yet" << std::endl;
		break;
	case sf::Socket::Status::Partial:
		std::cout << "_receieve: The socket sent a part of the data" << std::endl;
		break;
	case sf::Socket::Status::Disconnected:
		std::cout << "_receieve: The TCP socket has been disconnected" << std::endl;
		break;
	case sf::Socket::Status::Error:
		std::cout << "_receieve: An unexpected error happened" << std::endl;
		break;
	}

	return statusCode;
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
