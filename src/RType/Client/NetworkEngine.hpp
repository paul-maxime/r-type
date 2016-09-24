#ifndef RTYPE_CLIENT_NETWORKENGINE_HPP_
#define RTYPE_CLIENT_NETWORKENGINE_HPP_

#include "RType/ECS/INetworkEngine.hpp"

namespace rtype
{
	namespace client
	{
		class NetworkEngine : public ecs::INetworkEngine
		{
		private:
			bool _isConnected;
			bool _isConnecting;
			std::string _host;
			uint16_t _port;
			uint32_t _gameId;

		public:
			NetworkEngine();
			virtual ~NetworkEngine() {}

			virtual void connect(const std::string& host, uint16_t port, uint32_t gameId);
			virtual void disconnect();
			virtual bool isConnected() const;
			virtual bool isConnecting() const;

			void setConnected();
			const std::string& host() const;
			uint16_t port() const;
			uint32_t gameId() const;
		};
	} // namespace client
} // namespace rtype


#endif // RTYPE_CLIENT_NETWORKENGINE_HPP_
