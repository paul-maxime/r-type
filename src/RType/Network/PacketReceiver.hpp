#ifndef RTYPE_NETWORK_PACKETRECEIVER_HPP_
#define RTYPE_NETWORK_PACKETRECEIVER_HPP_

#include "RType/Network/Packets/APacket.hpp"

namespace rtype
{
	namespace network
	{
		class PacketReceiver
		{
		public:
			static packets::APacket* unpack(const std::string& raw);

		private:
			PacketReceiver();

			static void unpack(packets::APacket* packet, const std::string& data);
		};
	} // namespace network
} // namespace rtype

#endif // RTYPE_NETWORK_PACKETRECEIVER_HPP_
