#include <iostream>
#include <sstream>
#include <cstdint>

#include "RType/Network/UdpSocket.hpp"
#include "RType/Network/PacketSender.hpp"
#include "RType/Network/Packets/UpdateEntities.hpp"

static void send_hello(rtype::network::UdpSocket& socket)
{
	std::cout << "sending hello world" << std::endl;
	socket.send("127.0.0.1", 44321, "Hello, world. This is a test.");
}

static void send_big(rtype::network::UdpSocket& socket)
{
	std::ostringstream big;

	for (int i = 0; i < 50000; ++i)
		big << 'A';

	std::cout << "sending big packet" << std::endl;
	socket.send("127.0.0.1", 44321, big.str());
}

static void send_update_entities(rtype::network::UdpSocket& socket)
{
	using namespace rtype::network;
	using namespace rtype::network::packets;

	UpdateEntities entities(1012);

	std::string packet = PacketSender::pack(entities);

	std::cout << "sending update entities" << std::endl;
	socket.send("127.0.0.1", 44321, packet);
}

int	main()
{
	rtype::network::UdpSocket socket;
	socket.bind(44322);

	send_hello(socket);
	send_big(socket);
	send_update_entities(socket);

	return 0;
}
