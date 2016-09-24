#include <utility>

#include "RType/Network/Packets/UpdateEntities.hpp"

namespace rtype
{
	namespace network
	{
		namespace packets
		{
			const uint16_t UpdateEntities::protocolId = 110;

			UpdateEntities::UpdateEntities(uint32_t gameId)
				: APacket(protocolId, gameId)
			{
			}

			UpdateEntities::~UpdateEntities()
			{
			}

			std::vector<types::Entity>& UpdateEntities::entities()
			{
				return _entities;
			}

			const std::vector<types::Entity>& UpdateEntities::entities() const
			{
				return _entities;
			}

			void UpdateEntities::serialize(system::BinaryWriter& writer) const
			{
				writer << static_cast<uint16_t>(_entities.size());
				for (auto& entity : _entities)
					entity.serialize(writer);
			}

			void UpdateEntities::unserialize(system::BinaryReader& reader)
			{
				uint16_t size;
				reader >> size;
				for (uint16_t i = 0; i < size; ++i)
				{
					types::Entity entity;
					entity.unserialize(reader);
					_entities.push_back(std::move(entity));
				}
			}
		} // namespace packets
	} // namespace network
} // namespace rtype
