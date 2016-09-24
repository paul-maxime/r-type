#ifndef RTYPE_CLIENT_CLIENT_HPP_
#define RTYPE_CLIENT_CLIENT_HPP_

#include <string>
#include <set>
#include <memory>
#include <vector>

#include "RType/System/Random.hpp"
#include "RType/System/NonCopyable.hpp"
#include "RType/ECS/GameEngine.hpp"
#include "RType/Network/UdpSocket.hpp"
#include "RType/Client/NetworkEngine.hpp"

namespace rtype
{
	namespace client
	{
		class Client : public system::NonCopyable
		{
		private:
			network::UdpSocket _udp;
			std::unique_ptr<ecs::GameEngine> _engine;
			std::shared_ptr<NetworkEngine> _network;
			std::list< ecs::GameObject* > _serializableEntities;
			int _inactivity;

		public:
			Client(std::vector<std::string> const & argumentValues);

		private:
			void handleNetwork();
			void receivePacket();
			void sendInputs();
		};

	} // namespace client
} // namespace rtype

#endif // !RTYPE_CLIENT_CLIENT_HPP_
