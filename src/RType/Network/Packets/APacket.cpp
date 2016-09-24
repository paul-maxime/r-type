#include "RType/Network/Packets/APacket.hpp"

namespace rtype
{
	namespace network
	{
		namespace packets
		{
			APacket::APacket(uint16_t id, uint32_t gameId)
				: _id(id),
				  _gameId(gameId)
			{
			}

			APacket::~APacket()
			{
			}

			uint16_t APacket::id() const
			{
				return _id;
			}

			uint32_t APacket::gameId() const
			{
				return _gameId;
			}
		} // namespace packets
	} // namespace network
} // namespace rtype
