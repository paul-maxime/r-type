#include <iostream>
#include <cstdint>

#include "RType/Network/UdpSocket.hpp"
#include "RType/Network/PacketReceiver.hpp"
#include "RType/Network/PacketFactory.hpp"
#include "RType/Network/Packets/UpdateEntities.hpp"

static void recv_hello(rtype::network::UdpSocket& socket)
{
	std::string ip;
	uint16_t port;
	std::string content;
	socket.recv(ip, port, content);

	std::cout << "received `" << content << "'" << std::endl;
}

static void recv_big(rtype::network::UdpSocket& socket)
{
	std::string ip;
	uint16_t port;
	std::string content;
	socket.recv(ip, port, content);

	std::cout << "received " << content.size() << "-bytes packet" << std::endl;
}

static void recv_update_entities(rtype::network::UdpSocket& socket)
{
	using namespace rtype::network;
	using namespace rtype::network::packets;

	PacketFactory::init();

	std::string ip;
	uint16_t port;
	std::string content;

	socket.recv(ip, port, content);

	APacket* packet = PacketReceiver::unpack(content);
	if (packet)
	{
		if (packet->id() == UpdateEntities::protocolId)
		{
			UpdateEntities& update = *static_cast<UpdateEntities*>(packet);

			std::cout << "received UpdateEntities with "
					  << update.entities().size() << " entities."
					  << std::endl;
		}
		else
		{
			std::cerr << "received an invalid packet (id = " << packet->id() << ")!" << std::endl;
		}
		delete packet;
	}
	else
	{
		std::cerr << "could not unpack received packet!" << std::endl;
	}
}

int	main()
{
	rtype::network::UdpSocket socket;
	socket.bind(44321);
	socket.poll(-1);

	recv_hello(socket);
	recv_big(socket);
	recv_update_entities(socket);

	return 0;
}
