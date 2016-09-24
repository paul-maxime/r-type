#ifndef RTYPE_NETWORK_PACKETSENDER_HPP_
#define RTYPE_NETWORK_PACKETSENDER_HPP_

#include "RType/Network/Packets/APacket.hpp"

namespace rtype
{
	namespace network
	{
		class PacketSender
		{
		public:
			static std::string pack(const packets::APacket& packet);

		private:
			static std::string packData(const packets::APacket& packet);

			PacketSender();
		};
	}
}

#endif // RTYPE_NETWORK_PACKETSENDER_HPP_
