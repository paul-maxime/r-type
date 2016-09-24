#ifndef RTYPE_NETWORK_PACKETFACTORY_HPP_
#define RTYPE_NETWORK_PACKETFACTORY_HPP_

#include <cstdint>
#include <unordered_map>

#include "RType/Network/Packets/APacket.hpp"

namespace rtype
{
	namespace network
	{
		class PacketFactory
		{
		private:
			typedef packets::APacket* (*PacketCtor)(uint32_t);

			static std::unordered_map<uint16_t, PacketCtor> _packets;

		public:
			static void init();
			static packets::APacket* instantiate(uint16_t packetId, uint32_t gameId);

		private:
			PacketFactory();

			template <class T>
			static packets::APacket* instantiate_packet(uint32_t gameId)
			{
				return new T(gameId);
			}

			template <class T>
			static void register_packet()
			{
				_packets[T::protocolId] = &instantiate_packet<T>;
			}
		};
	} // namespace network
} // namespace rtype

#endif // RTYPE_NETWORK_PACKETFACTORY_HPP_
