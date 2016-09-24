#include <sstream>

#include "RType/System/BinaryWriter.hpp"
#include "RType/Network/PacketSender.hpp"

namespace rtype
{
	namespace network
	{
		std::string PacketSender::pack(const packets::APacket& packet)
		{
			std::string data = packData(packet);

			std::ostringstream oss;
			system::BinaryWriter writer(oss);

			writer << packet.id() << packet.gameId() << data;

			return oss.str();
		}

		std::string PacketSender::packData(const packets::APacket& packet)
		{
			std::ostringstream oss;
			system::BinaryWriter writer(oss);

			packet.serialize(writer);

			return oss.str();
		}
	} // namespace network
} // namespace rtype
