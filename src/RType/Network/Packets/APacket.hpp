#ifndef RTYPE_NETWORK_APACKET_HPP_
#define RTYPE_NETWORK_APACKET_HPP_

#include <cstdint>

#include "RType/System/BinaryWriter.hpp"
#include "RType/System/BinaryReader.hpp"

namespace rtype
{
	namespace network
	{
		namespace packets
		{
			class APacket
			{
			private:
				uint16_t _id;
				uint32_t _gameId;

			protected:
				APacket(uint16_t id, uint32_t gameId);

			public:
				virtual ~APacket();

				uint16_t id() const;
				uint32_t gameId() const;

				virtual void serialize(system::BinaryWriter&) const = 0;
				virtual void unserialize(system::BinaryReader&) = 0;
			};
		} // namespace packets
	} // namespace network
} // namespace rtype

#endif // RTYPE_NETWORK_APACKET_HPP_
