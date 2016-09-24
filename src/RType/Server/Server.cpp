#include <iostream>
#include <stdexcept>
#include <functional>

#include "RType/Server/Server.hpp"
#include "RType/System/Random.hpp"
#include "RType/Network/PacketFactory.hpp"
#include "RType/Network/PacketReceiver.hpp"
#include "RType/Network/Packets/UpdateEntities.hpp"

namespace rtype
{
	namespace server
	{
		Server::Server(std::vector<std::string> const&)
			: _server(1),
			  _roomManager(_server)
		{
			system::random::init();
			network::PacketFactory::init();

			_server.bind(44321, std::bind(&Server::onReceivePacket, this,
										  std::placeholders::_1,
										  std::placeholders::_2,
										  std::placeholders::_3));

			std::cout << "Server v0.6 running on port 44321." << std::endl;

			_server.pool().join();
		}

		void Server::onReceivePacket(const std::string& ip,
									 uint16_t port,
									 const std::string& content)
		{
			auto packet = std::unique_ptr<network::packets::APacket>
				(network::PacketReceiver::unpack(content));
			if (packet && packet->id() == network::packets::UpdateEntities::protocolId)
			{
				network::packets::UpdateEntities* update =
					static_cast<network::packets::UpdateEntities*>(packet.get());

				_roomManager.getRoom(packet->gameId()).onPacketReceived(ip, port, update);
			}
		}
	} // namespace server
} // namespace rtype
