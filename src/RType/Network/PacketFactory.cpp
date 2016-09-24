#include "RType/Network/PacketFactory.hpp"
#include "RType/Network/Packets/UpdateEntities.hpp"

namespace rtype
{
	namespace network
	{
		std::unordered_map<uint16_t, PacketFactory::PacketCtor> PacketFactory::_packets;

		packets::APacket* PacketFactory::instantiate(uint16_t packetId, uint32_t gameId)
		{
			auto it = _packets.find(packetId);
			if (it != _packets.end())
				return it->second(gameId);
			return 0;
		}

		void PacketFactory::init()
		{
			register_packet<packets::UpdateEntities>();
		}
	} // namespace network
} // namespace rtype
