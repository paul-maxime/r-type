#ifndef RTYPE_NETWORK_PACKETS_UPDATEENTITIES_HPP_
#define RTYPE_NETWORK_PACKETS_UPDATEENTITIES_HPP_

#include <vector>

#include "RType/Network/Packets/APacket.hpp"
#include "RType/Network/Types/Entity.hpp"

namespace rtype
{
	namespace network
	{
		namespace packets
		{
			class UpdateEntities : public APacket
			{
			public:
				static const uint16_t protocolId;

			private:
				std::vector<types::Entity> _entities;

			public:
				explicit UpdateEntities(uint32_t gameId);
				virtual ~UpdateEntities();

				std::vector<types::Entity>& entities();
				const std::vector<types::Entity>& entities() const;

				virtual void serialize(system::BinaryWriter&) const;
				virtual void unserialize(system::BinaryReader&);
			};
		} // namespace packets
	} // namespace network
} // namespace rtype

#endif // RTYPE_NETWORK_PACKETS_UPDATEENTITIES_HPP_
