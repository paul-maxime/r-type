#include <sstream>

#include "RType/System/BinaryReader.hpp"
#include "RType/Network/PacketReceiver.hpp"
#include "RType/Network/PacketFactory.hpp"

namespace rtype
{
	namespace network
	{
		packets::APacket* PacketReceiver::unpack(const std::string& raw)
		{
			std::istringstream iss(raw);
			system::BinaryReader reader(iss);

			uint16_t packetId;
			uint32_t gameId;
			std::string data;

			reader >> packetId >> gameId >> data;

			packets::APacket* packet = PacketFactory::instantiate(packetId, gameId);
			unpack(packet, data);

			return packet;
		}

		void PacketReceiver::unpack(packets::APacket* packet, const std::string& data)
		{
			if (packet)
			{
				std::istringstream iss(data);
				system::BinaryReader reader(iss);
				packet->unserialize(reader);
			}
		}
	} // namespace network
} // namespace rtype
