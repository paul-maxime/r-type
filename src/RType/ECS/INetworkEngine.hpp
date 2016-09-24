#ifndef RTYPE_ECS_INETWORKENGINE_HPP_
#define RTYPE_ECS_INETWORKENGINE_HPP_

#include <cstdint>
#include <string>

namespace rtype
{
	namespace ecs
	{
		class INetworkEngine
		{
		public:
			virtual ~INetworkEngine() {}

			virtual void connect(const std::string& host, uint16_t port, uint32_t gameId) = 0;
			virtual void disconnect() = 0;
			virtual bool isConnected() const = 0;
			virtual bool isConnecting() const = 0;
		};
	} // namespace ecs
} // namespace rtype

#endif // RTYPE_ECS_INETWORKENGINE_HPP_
